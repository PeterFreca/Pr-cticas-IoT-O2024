//CODIGO DE PROYECTO FINAL
//Elaborado por Pedro Fregoso y Rosina Flores
//Version 2.0

// Librerias
#include <WiFi.h> 
#include <PubSubClient.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>

// Defines
#define WIFISSID "IoT" //WIFI SSID 
#define PASSWORD "1t3s0IoT23" // WIFI password 
#define TOKEN "BBUS-n5isK7rLjYwmbwxRwMpjZ1swLWGCSB" // Ubidots TOKEN 
#define MQTT_CLIENT_NAME "ESP32Client123" // MQTT Client ID 
#define VARIABLE_LABEL_TEMP "temperature" // Variable label para temperature 
#define VARIABLE_LABEL_DIST "distance" // Variable label para distance 
#define DEVICE_LABEL "esp32s3-device" // Device label 

char mqttBroker[] = "industrial.api.ubidots.com"; 
char payload[200]; // Búfer para payload
char topic[150]; // Búfer para topic

// Espacio para almacenar los valores a enviar
char str_temp[10]; 
char str_dist[10]; 

// Configuración del sensor y el servo
OneWire ourWire(2);
DallasTemperature sensors(&ourWire);
Servo miServo;
const int pinServo = 19; 

// Pines del sensor ultrasónico
const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034  // Speed of sound en cm/us
long duration;
float distanceCm;
int angulo_rotacion = 0;

WiFiClient ubidots; 
PubSubClient client(ubidots); 


// Funciones de Callback y Reconexión
void callback(char* topic, byte* payload, unsigned int length) { 
// Procesar mensajes entrantes si es necesario
  char p[length + 1]; 
  memcpy(p, payload, length); 
  p[length] = NULL; 
  String message(p); 
  Serial.write(payload, length); 
  Serial.println(topic); 
} 
 
void reconnect() { 
// Loop hasta que estemos reconectados
  while (!client.connected()) { 
    Serial.println("Attempting MQTT connection..."); 
     
    // Attempt to connect 
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) { 
      Serial.println("Connected"); 
    } else { 
      Serial.print("Failed, rc="); 
      Serial.print(client.state()); 
      Serial.println(" try again in 2 seconds"); 
      delay(2000); 
    } 
  } 
} 
 

// Funciones Principales
void setup() { 
  Serial.begin(115200); 
  WiFi.begin(WIFISSID, PASSWORD); 
 
  Serial.print("Wait for WiFi..."); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
   
  Serial.println("\nWiFi Connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP()); 
  client.setServer(mqttBroker, 1883); 
  client.setCallback(callback);   
 
// Inicializar el sensor de temperatura y el servo
  sensors.begin(); 
  miServo.attach(pinServo);
  
// Configurar los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
} 
 
void loop() { 
  if (!client.connected()) { 
    reconnect(); 
  } 
  
  client.loop();


// Medir temperatura 
  sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0);
  Serial.print("Measured Temperature (°C): ");
  Serial.println(temp); 
  dtostrf(temp, 4, 2, str_temp); 


// Medir distancia 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  Serial.print("Measured Distance (cm): ");
  Serial.println(distanceCm);
  dtostrf(distanceCm, 4, 2, str_dist);


// Publicar temperatura 
  sprintf(topic, "/v1.6/devices/%s", DEVICE_LABEL); 
  sprintf(payload, "{\"%s\": {\"value\": %s}}", VARIABLE_LABEL_TEMP, str_temp); 
  Serial.println("Sending Temperature to Ubidots...");
  client.publish(topic, payload);

// Línea separadora en el Monitor Serial
  Serial.println();

// Publicar distancia 
  sprintf(payload, "{\"%s\": {\"value\": %s}}", VARIABLE_LABEL_DIST, str_dist); 
  Serial.println("Sending Distance to Ubidots...");
  client.publish(topic, payload);

// Movimiento de Servo  
  miServo.write(angulo_rotacion);
  Serial.print("Servo rotation: ");
  Serial.print(angulo_rotacion);
  Serial.println(" degrees");
  angulo_rotacion += 90;
  if (angulo_rotacion == 180) {
    angulo_rotacion = 0;
  }

  // Esperar 2 segundos para leer
  Serial.println("Waiting 2 seconds before next reading...");
  delay(2000);
}
