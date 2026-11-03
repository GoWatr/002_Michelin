import serial                                                   #Serial imported
import RPi.GPIO as GPIO                                         #GPIO imported
import requests                                                 #request imported
import json                                                     #json imported
from time import sleep                                          #sleep imported                     

GPIO.setwarnings(False)                                         # to avoid warnings setwarning added
GPIO.setmode(GPIO.BOARD)                                        # Setting board mode
RS485_EnablePin = 7                                             # enable pin initializing 
GPIO.setup(RS485_EnablePin,GPIO.OUT,initial = GPIO.LOW)         # assigning enable pin as low 

send = serial.Serial(                                          # setting the port ,baudrate
    port='/dev/serial0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

status_type = ["update","action"]                                 #assigning values to status type array variable
gostatus_old = ""                                                 # assigning gostatus_old and goaction_old as null
goaction_old = ""
dic_valve_status = {"1":"on","0":"off","on":"N","off":"F"}         # SEtting values as N & F for on and off and "1" is "on" "0" is "off"
count = 0                                                          #count value is zero

dic_ack_key = {1 : "success",0 : "failure"}                       #assigning dic_act_key value 1 means success 0 means failure

def data_receive(value):                                          # function is to receive serial data  from heltec lora 
    t = 0                                                         
    count = 0
    print("")
    print("data_to_be_transmitted : ",value)                      #inside value variable api data with some values added are there so when we get any changes in api this is the first print in rpi
    GPIO.setup(RS485_EnablePin,GPIO.OUT,initial = GPIO.LOW)       #Pin has to be low when we are waiting for the serial data from heltec lora 
    while(t == 0):
        received_DT = send.readline()
        print("received data : ",received_DT)
        read = str(received_DT.decode('utf-8'))               #reading the serial data
        if(len(read)>0):            
            if(value in read):                                     #if it is same expected data then value_ack variable is 1
                print("String matched")                          
                value_ack = 1
                t = 1
            else:
                print("inside else ")# this else is added because when we wait for on/off/mode change acknowledgement the raw data will come inbetween so we have to push that data also to api
                data_match_process(read)                          # data_match_process function called 
        count = count + 1
        if(count == 40):                                          # wait for count 15 to get serial data if it is not received value_ack value will be zero
            value_ack = 0                                         #Count value can be increased if we want to wait more than 15 sec to receive data from heltec lora
            t = 1
        sleep(1)
    return value_ack                                             #returning the value

def data_match_process(read):                                    #After data received matching the data and sending the //////ACKNOWLEDGEMENT////// via api
    count = 0
    received_t = read                                         
##    if('"TOT":"NA' in received_t):
##        print("data present")
##        received_t.replace('"TOT":" NA','call')
##        print("received_t : ",received_t)
    print("inside Data_match_process")
    received_id =  received_t.index("{")                         #first checking the data received with"{"
    received = received_t[received_id:]
    print("received : ",received)
    print("received  keys: ",json.loads(received))              # again changing to json format
    dic_value = json.loads(received)                      
    print(dic_value.keys())                                     # For example data is {"ID1":"GOWATRONE","CT1":"62","v1":"0"} Splitting based on kay and value
    fetch_key_values = dic_value.keys()                         #here "ct1","v1" are keys "62","0" are values
    for key_id in fetch_key_values:                             # matching the data if there is "ct"then we have to find numbers from(1 to 9 which is cooling tower number)   
        if("CT" in key_id):                                     #That numbers stored in ct_id
            ct_id = key_id.replace("CT","")
            ct_value = dic_value[key_id]                        #value for example 62 is stored in ct_value
            count = 1
        if("v" in key_id):        
            valve_id = key_id.replace("v","")                  #like mentioned above checking "v"in data and doing same process
            valve_status = dic_value[key_id]
            count = 2
        if("TOT" in key_id):                                   #same for "tot" which is flowmeter value ///////acknowledgement/////pushed to different api
            tot_id = key_id.replace("v","")
            tot_status = dic_value[key_id]
            count = 3
        if(count == 2):                                          #If count is 2 means sending the acknowledgement the raw value,valvestatus data to one api
            print(ct_id,ct_value,valve_id,valve_status)
            
            data ="http://localhost/michelin/water.php?tower={}&data=CT{}:{},vstatus:{}".format(valve_id,ct_id,ct_value,dic_valve_status[valve_status])                       
            update_api = requests.get(data)
            print(data)
            print(update_api.status_code)
            count = 0
        if(count == 3):                                        #if count is 3 sending the flowmeter data ///////////acknowledgement////////// to api 
            print(ct_id,ct_value,tot_id,tot_status)
            data ="http://localhost/michelin/flowmeter.php?fmid=CTFM01&flow={}&tot={}".format(ct_value,tot_status)                       
            update_api = requests.get(data)
            print(data)
            print(update_api.status_code)
            count = 0
while(1):
    try:
        for i in range(len(status_type)):                    #program starts here
            
            gostatus = ""                                   
            goaction = ""
            read_t = (send.readline())
            print("Read_t : ",read_t)  
            read = str(read_t.decode('utf-8'))             #decoding the data
            if(len(read)>0):
                try:
                    print(" ")
                    print("interrupt read : ",read)
                    data_match_process(read)              #when we are waiting for serial data from heltec lora particularly for on/off/mode inbetween arduino raw value came this function will be called
                except KeyboardInterrupt as e:            #hardware interrupt handling
                    print("keyboard interrupt ")          
                except Exception as e:                   #exception handling
                    print("error : ",e)
                print(" ")
                
            response = requests.get("http://localhost/michelin/get.php?call="+status_type[i])     # reading data from api
            try:
                if(str(response.status_code) == "200"):       
                    status = response.json()
                    if(status["functionality type"] == "update"):                               #checking whether it is update if it is update then we are splitting from api and adding "A" AND "M" 
                        gostatus = "id:gostatus"                                               
                        auto = (status["Auto"]["Valve_id"])
                        auto_t = auto.split(",")
                        if(auto_t[0] != ""):
                            for j in auto_t:
                                gostatus = gostatus+";"+(j+":A")
                            
                        manual = (status["Manual"]["Valve_id"])
                        manual_t = manual.split(",")
                        if(manual_t[0] != ""):
                            for k in manual_t:
                                gostatus = gostatus+";"+(k+":M")

                        if(len(gostatus)>0 and gostatus_old != gostatus):                           #With the help of gostatus_old & goaction_old duplicate values are removed
                            print("data UPDATE : ")
                            gostatus_rt = gostatus+" \r\n"
                            gostatus_t =  str(gostatus_rt).encode()                                 #Encoding the data and storing in gostatus_t variable
    ##                        print(gostatus)
                            GPIO.setup(RS485_EnablePin,GPIO.OUT,initial = GPIO.HIGH)                #When transmitting the data pin has to be high
                            sleep(2)
                            send.write(gostatus_t)                                                 # sending that data to heltec lora via serial
                            gostatus_old =gostatus
                            return_ack = data_receive(gostatus)                                    # aftyer sending serial data waiting for the acknowledgement from heltec lora 
                            print("return_ack : ",dic_ack_key[return_ack])                        
                            if(dic_ack_key[return_ack] == "success"):                             #if data received fromn heltec individually we have to transmit 9 times calling the api and sending each one by one
                                status_update_split = gostatus.split(";")
                                status_update_split_t = status_update_split[1:]                     #Sending the ////////////acknowledgement//////// valve status as manual or automatic individually 
                                for i in status_update_split_t:
                                    valve_id,valve_status = i.split(":")
                                    update_value = "http://localhost/michelin/response.php?response=go&data=CT{}:{}".format(valve_id.replace("V",""),valve_status)
                                    print(update_value)
                                    valve_response = requests.get(update_value)
                                    print("valve_response.status_code : ",valve_response.status_code)
                            print(" ")
                        
                    elif(status["functionality type"] == "action"):                                     #checking whether it is update if it is update then we are splitting from api 
                        goaction = "id:govalve"
                                                                                                     
                        loading_state = (status["Manual"]["loading"])                    
                        loading_state_t = loading_state.split(",")
                        if(loading_state_t[0] != ""):
                            for m in loading_state_t:
                                goaction = goaction+";"+m         
                            
                        if(len(goaction)>0 and goaction_old != goaction and ("None" not in goaction)):
                            print("data transmit action : ")
                            goaction_rt = goaction+" \r\n"   
                            print(goaction)
                            goaction_t = str(goaction_rt).encode()
                            GPIO.setup(RS485_EnablePin,GPIO.OUT,initial = GPIO.HIGH) 
                            sleep(2)
                            send.write(goaction_t)                                                            #sending  serial data to heltec lora
                            goaction_old = goaction
                            return_ack = data_receive(goaction)                                               #waiting for serial data acknowledgement from heltec lora 
                            print("return_ack : ",dic_ack_key[return_ack])
                            if(dic_ack_key[return_ack] == "success"):                                         #If the data is success valve on /off status data /////acknowledgement///// pushed to api here
    ##                            id:govalve;v4_off;v5_off
                                valve_id_split = goaction.split(";")
                                for valve_spilt_process in valve_id_split[1:]:
                                    valve_id,valve_cnd = valve_spilt_process.split("_")
                                    print("vavle_id : ",valve_id)
                                    url_status = "http://localhost/michelin/response.php?response=go&data=CT{}:{}".format(valve_id.replace("v",""),dic_valve_status[valve_cnd])
                                    print(url_status)
                                    valve_response = requests.get(url_status)
                                    print("valve_response.status_code : ",valve_response.status_code)
                            print(" ")
               
            except Exception as e:                                                                                 
                    print("error server response first  : ",e)
            GPIO.setup(RS485_EnablePin,GPIO.OUT,initial = GPIO.LOW)
            sleep(2)
    except Exception as e:
        print("error server response second : ",e)
            


        
