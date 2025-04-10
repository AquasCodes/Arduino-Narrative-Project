#include <Servo.h>

// interactions
int entrancePin = 2;
int faceCaesarPin = 3;
int killPin = 4;
int backCaesarPin = 5;
int exitPin = 6;

// servo pins
int door1Pin = 7;
int caesarPin = 8;
int door2Pin = 9;

// servos
Servo door1;
Servo caesar;
Servo door2;

// LEDs
int interiorLightPin = 10;
int killLightPin = 11;

void setup() {
  // interactions
  pinMode(entrancePin, INPUT);
  pinMode(faceCaesarPin, INPUT);
  pinMode(killPin, INPUT);
  pinMode(backCaesarPin, INPUT);
  pinMode(exitPin, INPUT);

  // servos
  door1.attach(door1Pin);
  caesar.attach(caesarPin);
  door2.attach(door2Pin);

  // LEDs
  pinMode(interiorLightPin, OUTPUT);
  pinMode(killLightPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // reset everything
  door1.write(0);
  caesar.write(0);
  door2.write(90);
  digitalWrite(interiorLightPin, LOW);
  digitalWrite(killLightPin, LOW);

  // wait for things to settle
  delay(2500);

  // wait for interaction 1
  while (digitalRead(entrancePin) == LOW) {
    delay(1);
  }

  // open door1, turn on light
  door1.write(90);
  digitalWrite(interiorLightPin, HIGH);

  // wait for interaction 2
  while (digitalRead(faceCaesarPin) == LOW) {
    delay(1);
  }

  // turn on red light
  digitalWrite(killLightPin, HIGH);

  // wait for interaction 3
  while (digitalRead(killPin) == LOW) {
    delay(1);
  }

  // spin caesar
  caesar.write(180);

  // flash red led dramatically
  digitalWrite(killLightPin, LOW);
  delay(50);
  digitalWrite(killLightPin, HIGH);
  delay(100);
  digitalWrite(killLightPin, LOW);

  // wait for interaction 4
  while (digitalRead(backCaesarPin) == LOW) {
    delay(1);
  }

  // open door2
  door2.write(0)

  // wait for interaction 5
  while (digitalRead(exitPin) == LOW) {
    delay(1);
  }

  // close both doors, turn off light
  door1.write(0);
  door2.write(90);
  digitalWrite(interiorLightPin, LOW);
}
