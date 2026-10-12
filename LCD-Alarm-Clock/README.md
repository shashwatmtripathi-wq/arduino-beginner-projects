# Arduino LCD Alarm Clock

A basic Arduino alarm clock using a 16x2 LCD, a buzzer,
and a push button. The current time and alarm time are
entered through the Arduino Serial Monitor.

## Features
- Displays current time and alarm time on an LCD
- Accepts time input through Serial Monitor
- Activates a buzzer when the alarm time is reached
- Uses a push button to silence the alarm

## Components
- Arduino board
- 16x2 LCD
- Buzzer
- Push button
- Breadboard and jumper wires

## Pin Connections

| Component | Arduino Pin |
| LCD RS    |       9     |
| LCD Enable|       8     |
| LCD D4    |       5     |
| LCD D5    |       4     |
| LCD D6    |       3     |
| LCD D7    |       2     |
| Buzzer    |       7     |
| Pushbutton|       10    |

The push button uses INPUT_PULLUP and should connect
between pin 10 and GND.

## How to Run
1. Connect the components according to the pin table.
2. Upload the Arduino sketch.
3. Open Serial Monitor at 9600 baud.
4. Enter the current hour and minute when prompted.
5. Enter the desired alarm hour and minute.

## Limitations
Timekeeping relies on software delays rather than a
dedicated real-time clock (RTC), so timing may drift.
