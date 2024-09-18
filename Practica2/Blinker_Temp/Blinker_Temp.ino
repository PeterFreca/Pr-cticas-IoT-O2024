//ESP32S3 Dev Module
/*#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();*/


#include <WiFi.h>
#define LED_BUILTIN 2
void setup() 
{
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() 
{
  float temp_celsius = temperatureRead();
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Led Prendido");
  delay(2500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Led Apagado");
  delay(2500);
  Serial.println("la temperatura interna del ESP32 es: ");
  Serial.println(temp_celsius);
  Serial.println("");
  delay(1000);
  //Serial.println((WiFi.localIP()));
}