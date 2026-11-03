#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "driver/uart.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "board.h"
#include "transducer.h"
#include "spi.h"

#include "driver/i2c.h"
#include "i2c-lcd.h" // Ensure this file is available in your project

#define I2C_MASTER_SCL_IO           GPIO_NUM_22
#define I2C_MASTER_SDA_IO           GPIO_NUM_21
#define I2C_MASTER_NUM              0
#define I2C_MASTER_FREQ_HZ          350000
#define I2C_MASTER_TX_BUF_DISABLE   0
#define I2C_MASTER_RX_BUF_DISABLE   0
#define I2C_MASTER_TIMEOUT_MS       1000

static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

#define ECHO_TEST_TXD   (17)
#define ECHO_TEST_RXD   (16)
#define ECHO_TEST_RTS   (4)
#define ECHO_TEST_CTS   (UART_PIN_NO_CHANGE)

#define BUF_SIZE        (127)
#define BAUD_RATE       (9600)

// Read packet timeout
#define PACKET_READ_TICS        (100 / portTICK_PERIOD_MS)
#define ECHO_TASK_STACK_SIZE    (4096)
#define ECHO_TASK_PRIO          (10)
#define ECHO_UART_PORT          (2)
#define ECHO_READ_TOUT          (3)

#define FLOWMETER_ID 2
#define DEVICE_ADDRESS 2
#define FN_CODE1 0x03
#define FN_CODE2 0x03

#define WATCHDOG_TIMEOUT_S 10


//#define FLOWMETER_ID _NO 1

#define LED_GPIO 2
static int flash_counter = 0;
int32_t Totalizer = 0; //should be 7 digit + 2 decimal digit -> 9999999.99 -> x10 -> 999999999//Can send totalizer as whole number instead of decimal
double flowrate;
int32_t tot_in_flash = 0;
unsigned int status = 0b00000001; 
static int Duration_flash_write = (5*60);
int decimalValue;

char rcv_buffer[200];
char REQUEST[256];

#define CUBIC_METERS_TO_GALLONS 264.172
#define CUBIC_METERS_TO_LITERS 1000
#define TIMER_DIVIDER (16)                           //  Hardware timer clock divider
#define TIMER_SCALE (TIMER_BASE_CLK / TIMER_DIVIDER) // convert counter value to seconds

// Constants for unit conversion
const double LPM_TO_M3H = 0.06; // 1 LPM = 0.06 m³/h
const double L_TO_M3 = 0.001;   // 1 liter = 0.001 m³

typedef struct
{
    int timer_group;
    int timer_idx;
    int alarm_interval;
    bool auto_reload;
} example_timer_info_t;


typedef struct
{
    example_timer_info_t info;
    uint64_t timer_counter_value;
} example_timer_event_t;

static xQueueHandle gpio_evt_queue = NULL;
static xQueueHandle s_timer_queue;

uint32_t Counter;
//uint32_t http_get_timer;
//uint8_t get_request_data = 0;
// static uint8_t s_led_state = 0;
max3510x_tof_results_t s_tof_results;
static volatile uint32_t s_results_count;
static volatile uint32_t s_timeout_count;

uint8_t c = 0;
uint8_t enable_sampling = 0;
uint32_t ts, last_ts, ts_temp = 0;

uint8_t interrupt_sts = 0;
uint16_t IntrStatus = 0;
uint8_t n;
double_t last_flow = 0.0, sum_flow = 0, flow; 
//uint8_t projid[32] = "baashyaam", flowid[32] = "GWFMBH0001";


uint16_t CalcCRC(const uint8_t* const buffer, const uint8_t u8length)
{
    uint32_t temp;
    uint32_t temp2;
    uint32_t flag;
    temp = 0xFFFF;
    for (uint8_t i = 0; i < u8length; i++)
    {
        temp = temp ^ buffer[i];
        for (uint8_t j = 1; j <= 8; j++)
        {
            flag = temp & 0x0001;
            temp >>=1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    // Reverse byte order.
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;
    return (uint16_t)temp;
}

static void echo_send(const int port, const char* str, uint8_t length) //echo_send(const int port, const char* str, uint8_t length)
{
    if (uart_write_bytes(port, str, length) != length) {
        ESP_LOGE(TAG, "Send data critical failure.");
        abort();
    }
}

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void inline print_timer_counter(uint64_t counter_value)
{
    printf("Time   : %.8f s\r\n", (double)counter_value / TIMER_SCALE);
}

static void gpio_task_example(void *arg)
{
    uint32_t io_num;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
        {
            // printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
            if (enable_sampling == 1)
            {
                interrupt_sts = 1;
            }
        }
    }
}

static bool IRAM_ATTR timer_group_isr_callback(void *args)
{
    BaseType_t high_task_awoken = pdFALSE;
    example_timer_info_t *info = (example_timer_info_t *)args;

    uint64_t timer_counter_value = timer_group_get_counter_value_in_isr(info->timer_group, info->timer_idx);

    /* Prepare basic event data that will be then sent back to task */
    example_timer_event_t evt = {
        .info.timer_group = info->timer_group,
        .info.timer_idx = info->timer_idx,
        .info.auto_reload = info->auto_reload,
        .info.alarm_interval = info->alarm_interval,
        .timer_counter_value = timer_counter_value};

    if (!info->auto_reload)
    {
        timer_counter_value += info->alarm_interval * TIMER_SCALE;
        timer_group_set_alarm_value_in_isr(info->timer_group, info->timer_idx, timer_counter_value);
    }

    /* Now just send the event data back to the main program task */
    xQueueSendFromISR(s_timer_queue, &evt, &high_task_awoken);

    return high_task_awoken == pdTRUE; // return whether we need to yield at the end of ISR
}

static void timer_task_example(void *arg)
{
    example_timer_event_t evt;
    for (;;)
    {
        xQueueReceive(s_timer_queue, &evt, portMAX_DELAY);
        Counter++;
        ts_temp++;
        //http_get_timer++;
        if (ts_temp >= 50)
        {
            ts_temp = 0;
            ts++;
        }

    }
}


static void example_tg_timer_init(int group, int timer, bool auto_reload, int timer_interval_msec)
{
    /* Select and initialize basic parameters of the timer */
    timer_config_t config = {
        .divider = TIMER_DIVIDER,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = auto_reload,
    }; // default clock source is APB
    timer_init(group, timer, &config);

    timer_set_counter_value(group, timer, 0);

    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(group, timer, ((timer_interval_msec * TIMER_SCALE) / 1000));
    timer_enable_intr(group, timer);

    example_timer_info_t *timer_info = calloc(1, sizeof(example_timer_info_t));
    timer_info->timer_group = group;
    timer_info->timer_idx = timer;
    timer_info->auto_reload = auto_reload;
    timer_info->alarm_interval = (timer_interval_msec / 1000);
    timer_isr_callback_add(group, timer, timer_group_isr_callback, timer_info, 0);

    timer_start(group, timer);
}

static void echo_task(void *arg)
{
    const int uart_num = ECHO_UART_PORT;
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        //.source_clk = UART_SCLK_DEFAULT,
    };

    esp_log_level_set(TAG, ESP_LOG_INFO);
    ESP_LOGI(TAG, "Start RS485 application test and configure UART.");
    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_LOGI(TAG, "UART set pins, mode and install driver.");
    ESP_ERROR_CHECK(uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));
    ESP_ERROR_CHECK(uart_set_rx_timeout(uart_num, ECHO_READ_TOUT));

    //uint8_t* data = (uint8_t*) malloc(BUF_SIZE);
    ESP_LOGI(TAG, "UART start recieve loop.\r");
    echo_send(uart_num, "Start RS485 UART test.\r\n", 24);
    uint8_t rx_buffer[128];
    while (1) {
        //int len = uart_read_bytes(uart_num, rx_buffer, sizeof(rx_buffer), pdMS_TO_TICKS(100));
        int len = uart_read_bytes(uart_num, rx_buffer, BUF_SIZE, PACKET_READ_TICS);
        if (len > 0) {
                printf("DATA 1 is = %x\n", rx_buffer[0]);
                printf("DATA 2 is = %x\n", rx_buffer[1]);
                printf("DATA 5 is = %x\n", rx_buffer[5]);
                if ((rx_buffer[0] == DEVICE_ADDRESS) && (rx_buffer[1] == FN_CODE1)){
                    printf("RS485 Request received!!!\n");
                    printf("***************\n");
                    printf("Uart Loop Totalizer = %dL, Uart Loop Flow Rate =%.2fLPM\r\n", Totalizer, flowrate);
                    int32_t decimal_value = Totalizer;
                    double flow_r = flowrate;
                    double valueToSend =flowrate;
                    uint8_t byteArray[8];
                     memcpy(byteArray, &valueToSend, sizeof(valueToSend));
                    int intflow = (int)flow_r;
                    printf("Flowrate after conversion******** = %dL\n", intflow);
                   
                    // unsigned char byte0 = (decimal_value >> 40) & 0xFF;
                   // unsigned char byte0 = (decimal_value >> 32) & 0xFF;
                    unsigned char byte0 = (decimal_value >> 24) & 0xFF;
                    unsigned char byte1 = (decimal_value >> 16) & 0xFF;
                    unsigned char byte2 = (decimal_value >> 8) & 0xFF;
                    unsigned char byte3 = decimal_value & 0xFF;
                    unsigned char byte4 = (intflow >> 16) & 0xFF;
                    unsigned char byte5 = (intflow >> 8) & 0xFF;
                    unsigned char byte6 = intflow & 0xFF;
                    printf("byte0: %u\n", byte0);
                    printf("byte1: %u\n", byte1);
                    printf("byte2: %u\n", byte2);
                    printf("byte3: %u\n", byte3);
                    printf("byte4: %u\n", byteArray[0]);
                    printf("byte5: %u\n", byteArray[1]);
                    printf("byte6: %u\n", byteArray[2]);
                      printf("byte7: %u\n", byteArray[3]);
                    printf("byte8: %u\n", byteArray[4]);
                    printf("byte9: %u\n", byteArray[5]);
                      printf("byte10: %u\n", byteArray[6]);
                    printf("byte11: %u\n", byteArray[7]);
                    printf("byte12: %u\n", byteArray[8]);
                  //  printf("byte7: %u\n", byte7);
                    //printf("byte8: %u\n", byte8);

                    uint8_t tx_buffer[127] = {DEVICE_ADDRESS, FN_CODE1,(rx_buffer[5]*2), byte0, byte1, byte2, byte3,byteArray[0], byteArray[1], byteArray[2],byteArray[3], byteArray[4], byteArray[5],byteArray[6], byteArray[7], byteArray[8]};
                    uint8_t size=((rx_buffer[5]*2)+3);
                    uint16_t u16crc = CalcCRC(tx_buffer, size);
                    tx_buffer[size+1] = u16crc & 0xff;
	                tx_buffer[size] = (u16crc >> 8);
                    echo_send(uart_num, (const char*)&tx_buffer, 50);
                    //vTaskDelay(100/portTICK_PERIOD_MS);          
                }
        } else {
            //echo_send(uart_num, ".", 1);
            //ESP_ERROR_CHECK(uart_wait_tx_done(uart_num, 10));
        }
    }
    vTaskDelete(NULL);
}
void task(void *pvParameters) {
    while (1) {
        // Pet the watchdog timer to prevent it from resetting the system
       // esp_task_wdt_reset();

        // Simulate some task
        printf("Task running...\n");

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}
void app_main(void)
{
    char buffer[100]; // Adjust size as needed
    uint32_t counter = 0;
    bool led_state = false;
    esp_task_wdt_init(WATCHDOG_TIMEOUT_S, true);
     esp_task_wdt_add(NULL);
    xTaskCreate(task, "Task", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    printf("The flowmeter ID is:%d\n", FLOWMETER_ID);
    //printf("The json file link is:%s\n", UPDATE_JSON_URL);

    // I2C and LCD initialization
    ESP_ERROR_CHECK(i2c_master_init());
    lcd_init();
    lcd_put_cur(0, 0);
    lcd_send_string("     GOWATR     ");
    lcd_put_cur(1, 0);
    lcd_send_string("   ver: 1.0.0   ");
    vTaskDelay(pdMS_TO_TICKS(3000)); // Delay for 1 second
    lcd_clear();

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_INPUT_MAX35101READY, gpio_isr_handler, (void *)GPIO_INPUT_MAX35101READY);

    s_timer_queue = xQueueCreate(10, sizeof(example_timer_event_t));
    xTaskCreate(timer_task_example, "timer_task_example", 2048, NULL, 10, NULL);
    example_tg_timer_init(TIMER_GROUP_0, TIMER_0, true, 20); // 20 ms for sampling Interval
    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d", CONFIG_MISO_GPIO);
    ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d", CONFIG_MOSI_GPIO);
    ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d", CONFIG_SCLK_GPIO);
    ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d", CONFIG_CS_GPIO);

    printf("MAX Starting Up!\n");

    MAX35101_Init(CONFIG_MISO_GPIO, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO);
    board_init();
    counter = Counter;
    enable_sampling = 1;

    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    void flash_counter_task(void *pvParameter)
    {
        while (1)
        {
            esp_err_t ret = nvs_flash_init();
            if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
            {
                ESP_ERROR_CHECK(nvs_flash_erase());
                ret = nvs_flash_init();
            }
            ESP_ERROR_CHECK(ret);
            flash_counter++;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            //open
            nvs_handle_t my_handle;
            ret = nvs_open("storage", NVS_READWRITE, &my_handle);
        
            // Read
            ret = nvs_get_i32(my_handle, "Totalizer", &tot_in_flash);
            vTaskDelay(pdMS_TO_TICKS(100));
            Totalizer = tot_in_flash;
            Totalizer += sum_flow;
            printf("Totalizer + sumflow= %dL\n", Totalizer);
            vTaskDelay(pdMS_TO_TICKS(100));

            // Write

            if (flash_counter >= Duration_flash_write) //Time
            {
                flash_counter = 0;
                ret = nvs_set_i32(my_handle, "Totalizer", Totalizer);           
                vTaskDelay(pdMS_TO_TICKS(100));
                ret = nvs_commit(my_handle);
                printf("Last Value written in flash is = %dL\n", Totalizer);
                sum_flow = 0;
                vTaskDelay(pdMS_TO_TICKS(100));
            }
            nvs_close(my_handle);
        }
    }

    xTaskCreate(&flash_counter_task, "flash_counter_task", 2048, NULL, 5, NULL); //Counter to write into flash
    // xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, ECHO_TASK_PRIO, NULL);
    while (1)
    {   
        esp_task_wdt_reset();
        if (interrupt_sts == 1)
        {
            interrupt_sts = 0;
            IntrStatus = max3510x_interrupt_status(&g_max35103);

            if ((IntrStatus & (MAX3510X_REG_INTERRUPT_STATUS_TOF | MAX3510X_REG_INTERRUPT_STATUS_TO)) == MAX3510X_REG_INTERRUPT_STATUS_TOF)
            {
                max3510x_read_tof_results(&g_max35103, &s_tof_results);
                s_results_count++;
            }
            else if (IntrStatus)
            {
                s_timeout_count++;
            }
        }

        if (Counter != counter)
        {
            if ((!s_results_count) && (enable_sampling == 1))
                max3510x_tof_diff(&g_max35103);
            counter = Counter;
        }

        flow = 0;
        if (s_results_count)
        {
                if (max3510x_validate_measurement(&s_tof_results.up, transducer_hit_count()) &&
                    max3510x_validate_measurement(&s_tof_results.down, transducer_hit_count()))
                {
                    float_t t2_ideal = max3510x_ratio_to_float(s_tof_results.up.t2_ideal);
                    float_t t1_t2 = max3510x_ratio_to_float(s_tof_results.up.t1_t2);
                    if (t2_ideal >= 0.75f && t1_t2 > 0.40f)//0.95 & 0.50//0.85 & 0.40
                    {

                        double_t up = max3510x_fixed_to_double(&s_tof_results.up.average);
                        double_t down = max3510x_fixed_to_double(&s_tof_results.down.average);
                        flow = last_flow = transducer_flow(up, down);
                    }
                    else
                    {
                    }
                }

                if (!flow)
                {
                    flow = last_flow;
                }

                if (flowrate < 1) 
                {
                    flow = 0;
                }
                sum_flow += (flow * CUBIC_METERS_TO_LITERS / 50.0);
                s_results_count = 0;
                c++;            
        }

        if (ts != last_ts)
        {
            board_led(led_state);
            led_state = !led_state;
            flowrate = last_flow * CUBIC_METERS_TO_LITERS * 60.0;
            printf("F-ID = GFI00%d,D-ID = 0x%x, Total Flow = %.2fL, Flow Rate =%.2fLPM, Totalizer = %.2dL\r\n",FLOWMETER_ID, DEVICE_ADDRESS, sum_flow, flowrate, Totalizer); // gallons per minute
            //printf("Totalizer = %.2dL\n", Totalizer);
            //printf("DEVICE ADDRESS = 0x%x, FN_CODE1 = 0x%x, FN_CODE2 = 0x%x\r\n", DEVICE_ADDRESS, FN_CODE1, FN_CODE2);
            last_ts = ts;

            double flowrate_m3h = flowrate * LPM_TO_M3H;
            if (flowrate > (0.5 * LPM_TO_M3H)){
                sprintf(buffer, "F~: %.2f m3/h  ", flowrate_m3h);
                lcd_put_cur(0, 0);
                lcd_send_string(buffer);
            } else {
                double dummyflow_m3h = 0;
                sprintf(buffer, "F~: %.2f m3/h  ", dummyflow_m3h);
                lcd_put_cur(0, 0);
                lcd_send_string(buffer);                
            }
            double totalizer_m3 = Totalizer * L_TO_M3;
            sprintf(buffer, "T+: %.2f m3", totalizer_m3);
            lcd_put_cur(1, 0);
            lcd_send_string(buffer);
        }
    }
}