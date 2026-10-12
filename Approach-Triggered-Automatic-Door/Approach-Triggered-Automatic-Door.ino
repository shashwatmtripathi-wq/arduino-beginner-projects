#include <Servo.h>

const int scannerServoPin = 3;  // Rotates the ultrasonic sensor
const int doorServoPin    = 5;  // Opens/closes the door
const int triggerPin      = 7;  // HC-SR04 TRIG
const int echoPin         = 8;  // HC-SR04 ECHO


const int scanMinAngle = 0;
const int scanMaxAngle = 105;
const int scanStep     = 5;  // Larger steps make a full scan faster
const int scanPositions = ((scanMaxAngle - scanMinAngle) / scanStep) + 1;
int scanAngle = scanMinAngle;
int scanDirection = scanStep;


const float detectionRangeCm = 30.0;       // Ignore objects beyond this range
const float approachDeltaCm  = 5.0;        // Must get at least 5 cm closer
const unsigned long doorHoldMs = 4000;      // Close 4 s after the last trigger
const int doorClosedAngle = 0;              // Adjust to match your door linkage
const int doorOpenAngle   = 90;             // Adjust to match your door linkage

Servo scannerServo;
Servo doorServo;

// One previous distance value for each scanner angle.
// -1 means there is no valid previous reading inside the detection range.
float previousDistance[scanPositions];

bool doorIsOpen = false;
unsigned long lastApproachTriggerMs = 0;

float measureDistanceCm() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Timeout avoids waiting indefinitely if the sensor receives no echo.
  unsigned long travelTime = pulseIn(echoPin, HIGH, 25000UL);

  if (travelTime == 0) {
    return -1.0;  // Not a valid echo
  }

  return (travelTime * 0.0343) / 2.0;
}

void openDoorAfterApproach() {
  if (!doorIsOpen) {
    doorServo.write(doorOpenAngle);
    doorIsOpen = true;
    Serial.println(F("Approach detected: door OPEN"));
  }

  // Extend the open period whenever another valid approach is detected.
  lastApproachTriggerMs = millis();
}

void updateDoorTimeout() {
  if (doorIsOpen && (millis() - lastApproachTriggerMs >= doorHoldMs)) {
    doorServo.write(doorClosedAngle);
    doorIsOpen = false;
    Serial.println(F("No new approach detected: door CLOSED"));
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  scannerServo.attach(scannerServoPin);
  doorServo.attach(doorServoPin);

  doorServo.write(doorClosedAngle);
  scannerServo.write(scanAngle);

  for (int i = 0; i < scanPositions; i++) {
    previousDistance[i] = -1.0;
  }

  delay(300);
  Serial.println(F("Automatic door system ready"));
  Serial.println(F("Trigger: within 30 cm AND at least 5 cm closer at the same scan angle"));
}

void loop() {
  // Move the sensor to the current scan angle and allow it to settle.
  scannerServo.write(scanAngle);
  delay(25);

  float distanceCm = measureDistanceCm();
  int sampleIndex = (scanAngle - scanMinAngle) / scanStep;

  // Objects outside 30 cm do not trigger the door. Reset the reading so
  // movement while outside the detection zone is ignored.
  if (distanceCm > 0.0 && distanceCm <= detectionRangeCm) {

    // Establish a baseline when an object first enters range.
    if (previousDistance[sampleIndex] <= 0.0) {
      previousDistance[sampleIndex] = distanceCm;
    } else {
      float approachDistance =
          previousDistance[sampleIndex] - distanceCm;

      // Trigger when the object is at least 5 cm closer
      // than the stored reference at this scan angle.
      if (approachDistance >= approachDeltaCm) {
        openDoorAfterApproach();

        Serial.print(F("Approach at angle "));
        Serial.print(scanAngle);
        Serial.print(F(" deg; distance = "));
        Serial.print(distanceCm, 1);
        Serial.println(F(" cm"));

        // Reset the reference after a successful trigger.
        previousDistance[sampleIndex] = distanceCm;
      }
    }

  } else {
    // Ignore objects outside range or invalid sensor readings.
    previousDistance[sampleIndex] = -1.0;
  }

  // Sweep back and forth between 0 and 105 degrees.
  if (scanAngle >= scanMaxAngle) {
    scanDirection = -scanStep;
  } else if (scanAngle <= scanMinAngle) {
    scanDirection = scanStep;
  }
  scanAngle += scanDirection;

  updateDoorTimeout();
}
