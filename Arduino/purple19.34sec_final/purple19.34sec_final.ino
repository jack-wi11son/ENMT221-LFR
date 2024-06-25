const int leftMotorPin = 9;
const int rightMotorPin = 3;
static bool update = false;
int power_difference = 0;
static int lastDir = 0;
static bool bang = false;
const int ledG = 6;
// Array to store five sensor values
int sensors[5];

int last_proportional = 0;
int integral = 0;
int ticks;
bool start = true;

void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(ledG, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readSensors(); // Reads sensor values into sensors array
  int error = calculateError(); // Calculates proportional error
  PID(error); // Implements PID control
  delay(5); // Short delay to avoid sensor reading saturation
}

void readSensors() {
  sensors[0] = constrain(analogRead(A1), 0, 600);
  sensors[1] = constrain(analogRead(A2), 0, 600);
  sensors[2] = constrain(analogRead(A3), 0, 600);
  sensors[3] = constrain(analogRead(A4), 0, 600);
  sensors[4] = constrain(analogRead(A5), 0, 600);
  for (int i=0; i < 5; i++) {
    if (sensors[i] < 400) {
      update = true;
    }
  }
  if (sensors[2] < 350) {
    lastDir = 0;
    bang = false;
  }
   else if (sensors[4] < 300) {
    lastDir = 1;
  } else if (sensors[0] < 300) {
    lastDir = -1;
  }
  if (sensors[3] < 350) {
    // lastDir = 0;
    bang = false;
  }
  if (sensors[1] < 350) {
    // lastDir = 0;
    bang = false;
  }
}

int calculateError() {
  float weights[5] = {-2.2, -1.5, 0., 1.5, 2.2};
  int error = 0;

  for (int i = 0; i < 5; i++) {
    error += weights[i] * sensors[i];
  }

  return error;
}

void PID(int error) {
  float Kp = 0.05;
  float Kd = 0.43;

  int derivative = error - last_proportional;
  if (update) {
    power_difference = Kp*error + Kd*derivative;
  } 
  int leftSpeed;
  int rightSpeed;
  if (ticks < 35 && start) {
    if (abs(power_difference) <= 900) {
      leftSpeed = constrain(150 - power_difference, 0, 150);
      rightSpeed = constrain(150 + power_difference, 0, 150);
    } else {
      leftSpeed = constrain(80 - power_difference, 0, 80);
      rightSpeed = constrain(80 + power_difference, 0, 80);
    } 
    ticks++;
  } else {
    start = false;
    if (abs(power_difference) <= 900) {
      if (ticks > 8) {
        leftSpeed = constrain(62 - power_difference, 0, 62);
        rightSpeed = constrain(62 + power_difference, 0, 62);
      } else {
        ticks++;
        leftSpeed = constrain(78 - power_difference, 0, 78);
        rightSpeed = constrain(78 + power_difference, 0, 78);
      }
    } else {
      ticks = 0;
      leftSpeed = constrain(78 - power_difference, 0, 78);
      rightSpeed = constrain(78 + power_difference, 0, 78);
    }
  }


  if(update) {
    if(!bang) {
      analogWrite(leftMotorPin, leftSpeed);
      analogWrite(rightMotorPin, rightSpeed);
    }
    update = false;
  } else {
    if (lastDir == 1) {
      bang = true;
      analogWrite(leftMotorPin, 55);
      analogWrite(rightMotorPin, 0);

    } else if (lastDir == -1) {
      bang = true;
      analogWrite(leftMotorPin, 0);
      analogWrite(rightMotorPin, 55);
    } 
  }

  last_proportional = error;
}