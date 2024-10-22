//Codigo Prueba sensor distancia
const int trigPin = 5;   // Pin conectado al Trigger del sensor ultrasónico
const int echoPin = 18;  // Pin conectado al Echo del sensor ultrasónico

// Definiciones
#define SOUND_SPEED 0.034  // Velocidad del sonido en cm/us
long duration;           //Variable de Tiempo de retorno
float distanceCm;        //Variable de conversion a cm

void setup() {
  //Inicio Comunicacion serial
  Serial.begin(115200);   
  //Setup de Sensor distancia
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 
}

void loop() {
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
  
  // Mostrar la distancia en el Monitor Serial
  Serial.print("Distancia (cm): ");
  Serial.println(distanceCm);
  delay(500);
}