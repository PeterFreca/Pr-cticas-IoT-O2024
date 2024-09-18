//Práctica #2 – 1. Prender y apagar el led interno del ESP32

#include <WiFi.h>
#define LED_BUILTIN 2
void setup() 
{
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Led Prendido");
  delay(2500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Led Apagado");
  delay(2500);

}