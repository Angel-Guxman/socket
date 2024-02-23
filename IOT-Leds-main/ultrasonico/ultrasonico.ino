#include <Ultrasonic.h>

Ultrasonic ultrasonic(12, 13); // (Trig pin, Echo pin)
int ledR = 9; // LED Rojo
int ledA = 10; // LED Amarillo
int ledV = 11; // LED Verde

int inputPin = 8;               
int pirState = LOW;             
int val = 0;
int ledPir = 6;   


void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(ledPir, OUTPUT);
}

void loop() {
  val = digitalRead(inputPin); 
  if (val == HIGH) {            
    digitalWrite(ledPir, HIGH);
    
    if (pirState == LOW) {
      Serial.println("M:true"); 
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPir, LOW); 
    
    if (pirState == HIGH){
      Serial.println("M:false"); 
      pirState = LOW;
    }
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    controlLEDs(command);                                       
  }

  long distance = ultrasonic.distanceRead(CM);
  Serial.print("D:");
  Serial.println(distance);
  delay(1000);
}

void controlLEDs(char command) {
  digitalWrite(ledR, LOW);
  digitalWrite(ledA, LOW);
  digitalWrite(ledV, LOW);
  
  switch (command) {
    case 'R':
      digitalWrite(ledR, HIGH);
      break;
    case 'A':
      digitalWrite(ledA, HIGH);
      break;
    case 'V':
      digitalWrite(ledV, HIGH);
      break;
    default:
      break;
  }
}
