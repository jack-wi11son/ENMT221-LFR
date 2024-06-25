const int leftMotorPin = 9;
const int rightMotorPin = 3;

const int sensorThreshold = 250; // Midpoint between 800 (white) and 50 (black)

const int fullSpeed = 80;
const int slightSpeed = 65;
const int hardSpeed = 20;

int sensors[5];

void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);

  Serial.begin(9600);  // For debugging purposes
}

void loop() {
  
  sensors[0] = analogRead(A1);
  sensors[1] = analogRead(A2);
  sensors[2] = analogRead(A3);
  sensors[3] = analogRead(A4);
  sensors[4] = analogRead(A5);

  // Debugging
  for (int i = 0; i < 5; i++) {
    Serial.print(sensors[i]);
    Serial.print("\t");
  }
  Serial.println();

  if(sensors[0] < sensorThreshold) { // Far to the left
    hardLeft();
  }
  else if(sensors[4] < sensorThreshold) { // Far to the right
    hardRight();
  }
  else if(sensors[1] < sensorThreshold) { // A bit to the left
    slightLeft();
  }
  else if(sensors[3] < sensorThreshold) { // A bit to the right
    slightRight();
  }
  else if(sensors[2] < sensorThreshold) { // Middle sensor on the line
    driveStraight();
  }
  else {
    //stopRobot();
    //swing memory
  }
}

void driveStraight() {
  analogWrite(leftMotorPin, fullSpeed);
  analogWrite(rightMotorPin, fullSpeed);
}

void slightLeft() {
  analogWrite(leftMotorPin, slightSpeed);
  analogWrite(rightMotorPin, fullSpeed);
}

void slightRight() {
  analogWrite(leftMotorPin, fullSpeed);
  analogWrite(rightMotorPin, slightSpeed);
}

void hardLeft() {
  analogWrite(leftMotorPin, hardSpeed);
  analogWrite(rightMotorPin, slightSpeed);
}

void hardRight() {
  analogWrite(leftMotorPin, slightSpeed);
  analogWrite(rightMotorPin, hardSpeed);
}

void stopRobot() {
  analogWrite(leftMotorPin, 0);
  analogWrite(rightMotorPin, 0);
}
