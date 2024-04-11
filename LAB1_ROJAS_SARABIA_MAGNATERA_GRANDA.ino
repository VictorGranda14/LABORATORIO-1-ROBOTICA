#include <Servo.h>
 
long duration;
int distance;
 
// pines sensor ultrasonido
const int trigPin = 12;
const int echoPin = 11;

Servo srv;

const int sensorPin = A0;   // pin entrada fotoresistencia
int ldrValue = 0;  // variable para guardar los valores leídos por la fotoresistencia
 
void setup() {
  pinMode(trigPin, OUTPUT); // trigPin como output
  pinMode(echoPin, INPUT); // echoPin como input
  Serial.begin(9600);
  srv.attach(9);
  srv.write(0);
}
 
void loop() {
  // leer valor fotoresistencia
  ldrValue = analogRead(sensorPin);
 
  // limpiar trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // trigPin en 1 por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // leer el echoPin, retorna el tiempo de viaje de la onda en microsegundos
  duration = pulseIn(echoPin, HIGH);
  // calculamos la distancia
  distance = duration * 0.034 / 2;
 
  if((distance > 80) && (ldrValue > 600))
  {
    // servo 180
    srv.write(180);
  }

  if((distance <= 30) && (ldrValue < 600) && (ldrValue > 200))
  {
    // servo 60
    srv.write(60);
  }

  if((distance < 10) && (ldrValue < 200))
  {
    srv.write(0);
  }

  //Serial.println("fotoresistencia: " + ldrValue);
  Serial.print("distancia: ");
  Serial.println(distance);
  Serial.print("fotoresistencia: ");
  Serial.println(ldrValue);
}