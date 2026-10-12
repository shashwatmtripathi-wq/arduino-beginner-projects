# Approach-Triggered Automatic Door

An Arduino-based automatic door prototype that uses ultrasonic scanning and distance-change detection to identify approaching objects within a defined range. The system triggers door opening when an object approaches and automatically closes the door after a set interval.

## Project Objective

Design an automatic-door control system that responds to an approaching object rather than triggering solely because an object is nearby. The approach-detection rule aims to reduce unnecessary door actuation.

## Key Features

- **Ultrasonic scanning:** A servo sweeps the HC-SR04 sensor between 0° and 105°.
- **Approach detection:** Detects a decrease in measured distance at the same scan angle.
- **Defined detection range:** Objects beyond 30 cm are ignored.
- **Distance-change threshold:** A decrease of at least 5 cm triggers the door.
- **Automatic closing:** The door closes after 4 seconds without another qualifying approach.
- **Dual-servo control:** One servo scans the sensor, while the other controls the door.

## Hardware Components

- Arduino Uno
- HC-SR04 ultrasonic distance sensor
- 2 servo motors
- Jumper wires
- Suitable power supply
- Breadboard or mounting platform

## Pin Connections

|       Component      |     Arduino Pin     |
| Scanner servo signal |           3         |
| Door servo signal    |           5         |
| HC-SR04 TRIG         |           7         |
| HC-SR04 ECHO         |           8         |

## Working Principle

1. The scanning servo moves the ultrasonic sensor across the configured angular range.
2. At each scan angle, the Arduino measures the distance to an object.
3. Measurements outside the 30 cm detection range are ignored.
4. For an object within range, the system establishes a reference distance at that scan angle.
5. If a subsequent measurement at the same angle is at least 5 cm closer than the stored reference, the door-opening servo is activated.
6. The door remains open for 4 seconds after the last qualifying approach before the closing command is issued.

## Technologies Used

Arduino C/C++

HC-SR04 ultrasonic sensing

Servo motor control

Distance-based event detection

Timing using millis()
