#include <Servo.h>

// interaction pins
int entrancePin = 2;
int approachPin = 3;
int killPin = 4;
int escapePin = 5;
int endPin = 6;

// servo pins
int door1Pin = 7;
int caesarPin = 8;
int senatorsPin = 9;
int door2Pin = 10;

// LED pins
int whitePin = 11;
int redPin = 12;

// servos
Servo door1;
Servo caesar;
Servo senators;
Servo door2;

void setup() {
  // setup interactions
  pinMode(entrancePin, INPUT);
  pinMode(approachPin, INPUT);
  pinMode(killPin, INPUT);
  pinMode(escapePin, INPUT);
  pinMode(endPin, INPUT);

  // setup servos
  door1.attach(door1Pin);
  caesar.attach(caesarPin);
  senators.attach(senatorsPin);
  door2.attach(door2Pin);

  // setup LEDs
  pinMode(whitePin, OUTPUT);
  pinMode(redPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // reset all servos
  door1.write(90);
  caesar.write(0);
  door2.write(90);
  senators.write(0);

  // turn off all LEDs
  digitalWrite(whitePin, LOW);
  digitalWrite(redPin, LOW);

  // give the project a second to settle
  delay(500);

  Serial.println("Ready!");

  // wait for interaction 1 --------------------------------
  interaction(1, entrancePin);

  // open front door, turn on interior light
  door1.write(0);
  digitalWrite(whitePin, HIGH);

  // wait for interaction 2 --------------------------------
  interaction(2, approachPin);

  // turn on evil kill light
  digitalWrite(redPin, HIGH);

  // wait for interaction 3 --------------------------------
  interaction(3, killPin);

  // kill caesar
  caesar.write(180);
  digitalWrite(redPin, LOW);

  // senators suprised
  senators.write(180);

  // wait for interaction 4 --------------------------------
  interaction(4, escapePin);

  // open exit door
  door2.write(180);

  // wait for interaction 5 --------------------------------
  interaction(5, endPin);

  Serial.println("Resetting...");

  // reset all servos (except caesar)
  door1.write(90);
  door2.write(90);

  // turn off all LEDs
  digitalWrite(whitePin, LOW);
  digitalWrite(redPin, LOW);

  // let things sit for a bit until restarting
  delay(5000);
}

// waits until an interaction is pressed and logs it
void interaction(int num, int pin) {
  while (digitalRead(pin) == LOW) {
    delay(10);
  }  
  String prnt = "Interaction ";
  prnt += num;
  Serial.println(prnt);
}
