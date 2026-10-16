// SCRATCH <-> ARDUINO MEGA
// UNIVERSAL WORKSHOP BRIDGE
// FARA JOYSTICK

const int SENSOR_PIN = 7;
const int INPUT2_PIN = 8;
const int INPUT3_PIN = 9;
const int INPUT4_PIN = 10;

int lastSensor;
int lastInput2;
int lastInput3;
int lastInput4;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(INPUT2_PIN, INPUT_PULLUP);
  pinMode(INPUT3_PIN, INPUT_PULLUP);
  pinMode(INPUT4_PIN, INPUT_PULLUP);

  Serial.begin(9600);

  lastSensor = digitalRead(SENSOR_PIN);
  lastInput2 = digitalRead(INPUT2_PIN);
  lastInput3 = digitalRead(INPUT3_PIN);
  lastInput4 = digitalRead(INPUT4_PIN);
}

void loop() {

  // SCRATCH -> ARDUINO

  if (Serial.available() > 0) {

    char command = Serial.read();

    if (command == '1') {
      digitalWrite(LED_BUILTIN, HIGH);
    }

    else if (command == '0') {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  // D7 -> SENSOR + INPUT1

  int sensor = digitalRead(SENSOR_PIN);

  if (sensor != lastSensor) {

    if (sensor == LOW) {
      Serial.println("SENSOR:1");
      Serial.println("INPUT1:1");
    }

    else {
      Serial.println("SENSOR:0");
      Serial.println("INPUT1:0");
    }

    lastSensor = sensor;
  }

  // D8 -> INPUT2

  int input2 = digitalRead(INPUT2_PIN);

  if (input2 != lastInput2) {

    Serial.println(
      input2 == LOW ? "INPUT2:1" : "INPUT2:0"
    );

    lastInput2 = input2;
  }

  // D9 -> INPUT3

  int input3 = digitalRead(INPUT3_PIN);

  if (input3 != lastInput3) {

    Serial.println(
      input3 == LOW ? "INPUT3:1" : "INPUT3:0"
    );

    lastInput3 = input3;
  }

  // D10 -> INPUT4

  int input4 = digitalRead(INPUT4_PIN);

  if (input4 != lastInput4) {

    Serial.println(
      input4 == LOW ? "INPUT4:1" : "INPUT4:0"
    );

    lastInput4 = input4;
  }

  delay(20);
}
