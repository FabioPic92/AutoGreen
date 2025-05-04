#include <AccelStepper.h>


const int stepPin = 3;  // Pin STEP
const int dirPin = 2;   // Pin DIR

void setup() {
  // Imposta i pin come uscita
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // Imposta la direzione del motore
  digitalWrite(dirPin, HIGH); // Direzione in avanti (cambia in LOW per invertire la direzione)
}

void loop() {
  // Fai muovere il motore di un passo
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(50);  // Pausa tra i passi (regola la velocità del motore)
  digitalWrite(stepPin, LOW);
  delayMicroseconds(50);  // Pausa tra i passi (regola la velocità del motore)
}