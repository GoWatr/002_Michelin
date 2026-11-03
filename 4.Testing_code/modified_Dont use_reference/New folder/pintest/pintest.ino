#define valve1 8
#define valve2 7
#define valve3 6
#define valve4 9
#define valve5 10
#define valve6 11
#define valve7 14
#define valve8 2
#define valve9 3
#define valve10 4
#define valve11 5
#define valve12 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("michelin valve control");
  pinMode(valve1, OUTPUT);
  digitalWrite(valve1, LOW);
  pinMode(valve2, OUTPUT);
  digitalWrite(valve2, LOW);
  pinMode(valve3, OUTPUT);
  digitalWrite(valve3, LOW);
  pinMode(valve4, OUTPUT);
  digitalWrite(valve4, LOW);
  pinMode(valve5, OUTPUT);
  digitalWrite(valve5, LOW);
  pinMode(valve6, OUTPUT);
  digitalWrite(valve6, LOW);
  pinMode(valve7, OUTPUT);
  digitalWrite(valve7, LOW);
  pinMode(valve8, OUTPUT);
  digitalWrite(valve8, LOW);
  pinMode(valve9, OUTPUT);
  digitalWrite(valve9, LOW);
  pinMode(valve10, OUTPUT);
  digitalWrite(valve10, LOW);
  pinMode(valve11, OUTPUT);
  digitalWrite(valve11, LOW);
  pinMode(valve12, OUTPUT);
  digitalWrite(valve12, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //   Serial.println("valve1");
  //   digitalWrite(valve1, HIGH);
  //   delay(10000);
  //   digitalWrite(valve1, LOW);
  //   delay(5000);
  // Serial.println("valve2");
  //   digitalWrite(valve2, HIGH);
  //   delay(10000);
  //   digitalWrite(valve2, LOW);
  //   delay(5000);
  // Serial.println("valve3");
  //   digitalWrite(valve3, HIGH);
  //   delay(10000);
  //   digitalWrite(valve3, LOW);
  //   delay(5000);
  // Serial.println("valve4");
  //   digitalWrite(valve4, HIGH);
  //   delay(10000);
  //   digitalWrite(valve4, LOW);
  //   delay(5000);
  // Serial.println("valve5");
  //   digitalWrite(valve5, HIGH);
  //   delay(10000);
  //   digitalWrite(valve5, LOW);
  //   delay(5000);
  // Serial.println("valve6");
  //   digitalWrite(valve6, HIGH);
  //   delay(10000);
  //   digitalWrite(valve6, LOW);
  //   delay(5000);
  // Serial.println("valve7");
  //   digitalWrite(valve7, HIGH);
  //   delay(10000);
  //   digitalWrite(valve7, LOW);
  //   delay(5000);
  // Serial.println("valve8");
  //   digitalWrite(valve8, HIGH);
  //   delay(10000);
  //   digitalWrite(valve8, LOW);
  //   delay(5000);
  // Serial.println("valve9");
  //   digitalWrite(valve9, HIGH);
  //   delay(10000);
  //   digitalWrite(valve9, LOW);
  //   delay(5000);
  // Serial.println("valve10");
  //   digitalWrite(valve10, HIGH);
  //   delay(10000);
  //   digitalWrite(valve10, LOW);
  //   delay(5000);
  // Serial.println("valve11");
  //   digitalWrite(valve11, HIGH);
  //   delay(10000);
  //   digitalWrite(valve11, LOW);
  //   delay(5000);
  // Serial.println("valve12");
  //   digitalWrite(valve12, HIGH);
  //   delay(10000);
  //   digitalWrite(valve12, LOW);
  //   delay(5000);
  // Serial.println("valve11");
    digitalWrite(valve11, HIGH);
    delay(5000);
    digitalWrite(valve11, LOW);
    delay(5000);
}
