/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

const int sensor1 = A1; //J1 Sensor
const int sensor2 = A2; //J2 Sensor
const int sensor3 = A3; //J3 Sensor
const int sensor4 = A4; //J4 Sensor
const int sensor5 = A5; //J5 Sensor

const int ledR = 7;  //Green led pin
const int ledG = 6;  // Red led pin

const int motorLeft = 9; //J7 motor left
const int motorRight = 3; //J8 motor left

int sensor1Value = 0;  //J1 Sensor
int sensor2Value = 0;  //J2 Sensor
int sensor3Value = 0;  //J3 Sensor
int sensor4Value = 0;  //J4 Sensor
int sensor5Value = 0;  //J5 Sensor

int leftSpeed = 0;  // motor left speed out
int leftSpeed = 0;  // motor right speed out

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensor5);
  outputValue = map(sensorValue, 10, 800, 0, 255);
  if (outputValue < 0) {
    outputValue = 0;
  }
  if (outputValue > 255) {
    outputValue = 255;
  }
  digitalWrite(ledG, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);

  analogWrite(motorRight, outputValue);
  analogWrite(motorLeft, outputValue);
  Serial.println(outputValue);                      // wait for a second
  digitalWrite(ledG, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a second
}
