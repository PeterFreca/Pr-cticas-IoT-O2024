//ESP32S3 Dev Module

#define LED_BUILTIN 2
void setup() {
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  Serial.println("Hola mundo");
   Serial.println("10/09/24");
}