const int leftMotorPin = 9;
const int rightMotorPin = 3;
static bool update = false;
int power_difference = 0;
static int lastDir = 0;
static bool bang = false;
// Array to store five sensor values
int sensors[5];

int last_proportional = 0;
int integral = 0;

void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readSensors();                 // Reads sensor values into sensors array
  int error = calculateError();  // Calculates proportional error
  PID(error);                    // Implements PID control
  delay(5);                      // Short delay to avoid sensor reading saturation
}

void readSensors() {
  sensors[0] = constrain(analogRead(A1), 0, 600);
  sensors[1] = constrain(analogRead(A2), 0, 600);
  sensors[2] = constrain(analogRead(A3), 0, 600);
  sensors[3] = constrain(analogRead(A4), 0, 600);
  sensors[4] = constrain(analogRead(A5), 0, 600);
  for (int i = 0; i < 5; i++) {
    Serial.print(sensors[i]);
    Serial.print("\t");

    if (sensors[i] < 300) {
      update = true;
    }
  }
  if (sensors[2] < 300) {
    lastDir = 0;
    bang = false;
  } else if (sensors[4] < 300) {
    lastDir = 1;
  } else if (sensors[0] < 300) {
    lastDir = -1;
  }
  if (sensors[3] < 300) {
    // lastDir = 0;
    bang = false;
  }
  if (sensors[1] < 300) {
    // lastDir = 0;
    bang = false;
  }
}

int calculateError() {
  float weights[5] = { -2.2, -1.7, 0., 1.7, 2.2 };
  int error = 0;

  for (int i = 0; i < 5; i++) {
    error += weights[i] * sensors[i];
  }

  return error;
}

void PID(int error) {
  float Kp = 0.05;
  float Kd = 0.25;
  Serial.print(update);
  Serial.print("\t");
  int derivative = error - last_proportional;
  if (update) {
    power_difference = Kp * error + Kd * derivative;
  }


  int leftSpeed = constrain(70 - power_difference, 0, 70);
  int rightSpeed = constrain(70 + power_difference, 0, 70);


  if (update) {
    if (!bang) {
      analogWrite(leftMotorPin, leftSpeed);
      analogWrite(rightMotorPin, rightSpeed);
    }
    update = false;
  } else {
    if (lastDir == 1) {
      bang = true;
      analogWrite(leftMotorPin, 50);
      analogWrite(rightMotorPin, 0);

    } else if (lastDir == -1) {
      bang = true;
      analogWrite(leftMotorPin, 0);
      analogWrite(rightMotorPin, 50);
    }
  }


  // } else if (lastDir == 1) {
  //   analogWrite(leftMotorPin, 65);
  //   analogWrite(rightMotorPin, 10);
  // } else if (lastDir == -1) {
  //   analogWrite(leftMotorPin, 10);
  //   analogWrite(rightMotorPin, 65);
  // }


  // Serial.print(error);
  // Serial.print("\t");

  // Serial.print(derivative);
  // Serial.print("\t");
  // Serial.print(power_difference);
  // Serial.print("\t");
  // Serial.print(leftSpeed);
  // Serial.print("\t");
  // Serial.print(rightSpeed);
  // Serial.print("\t");
  // Serial.print(lastDir);
  // Serial.print("\t");
  // Serial.print(bang);
  // Serial.print("\t");

  // //Serial.print("HI");
  // Serial.println();



  last_proportional = error;
}
