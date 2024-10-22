//Prueba servo
#include <ESP32Servo.h>

Servo miServo;
const int pinServo = 19; // Pin GPIO al que está conectado el servo

void setup() 
{
  miServo.attach(pinServo);
  Serial.begin(115200);
}
void loop() 
{
  miServo.write(0);    // Mover el servo a 0 grados
  Serial.println("0 grados");
  delay(2000);         // Esperar 1 segundo
  miServo.write(90);   // Mover el servo a 90 grados
  Serial.println("90 grados");
  delay(2000);         // Esperar 1 segundo
  miServo.write(180);  // Mover el servo a 180 grados
  Serial.println("180 grados");
  delay(2000);         // Esperar 1 segundo
  miServo.write(90);   // Mover el servo a 90 grados
  Serial.println("90 grados");
  delay(2000);         // Esperar 1 segundo
}