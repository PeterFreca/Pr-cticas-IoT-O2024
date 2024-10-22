//CODIGO DE PROYECTO FINAL 
//Elaborado por Pedro Fregoso
//Version 1.1


//Para Sensor de Temperatura
#include <OneWire.h>                
#include <DallasTemperature.h>
//Para Servo
#include <ESP32Servo.h>

//Declaraciones
//Servomotor
Servo miServo;
const int pinServo = 19; // Pin GPIO al que está conectado el servo

//Sensor de Temperatura
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

//Sensor de distancia
const int trigPin = 5;   // Pin conectado al Trigger del sensor ultrasónico
const int echoPin = 18;  // Pin conectado al Echo del sensor ultrasónico

// Definiciones
#define SOUND_SPEED 0.034  // Velocidad del sonido en cm/us
long duration;           //Variable de Tiempo de retorno
float distanceCm;        //Variable de conversion a cm
int angulo_rotacion=0;


void setup() {
  //Setup Servo
  miServo.attach(pinServo);
  //Comunicacion Serial
  Serial.begin(115200);
  //Se inicia el sensor de Temperatura
  sensors.begin();   
  //Setup de Sensor distancia
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 
}

void loop() {
  //Etapa Medicion de Temperatura
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  //Etapa medicion de nivel
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);

  //Inicio medicion de distancia
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  
  //Tiempo de retorno y calculo de distancia
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  
  // Mostrar Variables en Monitor Serial y Movimiento Actuador
  Serial.print("Temperatura (⸰C)= ");
  Serial.println(temp);

  Serial.print("Distancia (cm)= ");
  Serial.println(distanceCm);

  //Actuador Servo
  miServo.write(angulo_rotacion);    // Mover el servo a 0 grados
  Serial.print("Angulo Rotacion (⸰) =");
  Serial.println(angulo_rotacion);

  angulo_rotacion+=90;
  if(angulo_rotacion==270){
    angulo_rotacion=0;
  }
  delay(2000);         // Esperar 1 segundo
}
