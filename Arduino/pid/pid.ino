const int leftMotorPin = 9;
const int rightMotorPin = 3;

const int sensorThreshold = 200;

const int fullSpeed = 100;

int sensors[5];

const float Kp = 0.5;  

float error = sensors[2] - sensorThreshold;
float correction = Kp * error;
const int some_small_value = 10;  // 5% of 200

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

  float error = sensors[2] - sensorThreshold;
  float correction = Kp * error;
  
  if (abs(error) < some_small_value) { 
    driveStraight();
  } else {
    adjustMotors(correction);
  }
}

void adjustMotors(float correction) {
  int leftSpeed = fullSpeed - correction;
  int rightSpeed = fullSpeed + correction;
  
  // Ensure motor speeds don't exceed fullSpeed or go below 0.
  leftSpeed = constrain(leftSpeed, 0, fullSpeed);
  rightSpeed = constrain(rightSpeed, 0, fullSpeed);

  analogWrite(leftMotorPin, leftSpeed);
  analogWrite(rightMotorPin, rightSpeed);
}

void driveStraight() {
  analogWrite(leftMotorPin, fullSpeed);
  analogWrite(rightMotorPin, fullSpeed);
}