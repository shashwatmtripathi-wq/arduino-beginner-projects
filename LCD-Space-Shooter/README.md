# LCD Space Shooter — Arduino

A button-controlled space shooter game built using an Arduino and a 16×2 LCD. Dodge incoming asteroids, fire projectiles, and survive as long as possible while the game gradually becomes faster.

## Features

- **Two-button controls:** Switch between the two LCD rows and fire projectiles.
- **Asteroid movement:** Asteroids approach the player from the right side of the screen.
- **Projectile firing:** Shoot asteroids travelling along the same row.
- **Collision detection:** The game ends when an asteroid collides with the player.
- **Dynamic difficulty:** Asteroid movement speed varies and progressively increases over time.
- **Randomised gameplay:** Asteroids appear on different rows and at varying distances.
- **Survival timer:** Displays the time survived when the game ends.

## Hardware Components

- Arduino-compatible board
- 16×2 character LCD
- 2 push buttons
- Breadboard and jumper wires
- USB cable and suitable power supply
- LCD contrast potentiometer, if required by your display setup

## Pin Connections

### LCD to Arduino

| LCD Pin | Arduino Pin |
| RS      |      8      |
| Enable  |      7      |
| D4      |      5      |
| D5      |      4      |
| D6      |      3      |
| D7      |      2      |

### Push Buttons

|      Button       |   Arduino Pin   |
| Move / Change Row |         9       |
| Shoot             |         10      |

Both buttons use `INPUT_PULLUP`, so connect each button between its assigned Arduino pin and GND.

Connect the LCD power, ground, contrast and backlight pins according to your display module's requirements. The LCD's R/W pin is typically connected to GND when using write-only operation.

## How to Play

1. Connect the LCD and buttons according to the pin tables.
2. Open `LCD-Space-Shooter.ino` in the Arduino IDE.
3. Select the appropriate Arduino board and port.
4. Upload the sketch.
5. Press either button to begin the game.
6. Press the Move button to switch between the upper and lower rows.
7. Press the Shoot button to fire a projectile along the player's current row.
8. Avoid asteroids and try to maximise your survival time.

When an asteroid collides with the player, the game displays the survival time. Reset the Arduino to play again.

## How It Works

The project uses the `LiquidCrystal` library to render the player, projectiles and asteroids on the 16×2 LCD.

Button inputs are read digitally, with edge detection used to respond to individual button presses. The `millis()` function manages movement updates, elapsed time and difficulty progression without relying on long blocking delays during normal gameplay.

Asteroids move from right to left, while projectiles travel from left to right. The program checks for projectile–asteroid collisions and respawns asteroids when they are destroyed or escape the screen.

The asteroid speed changes periodically, and the difficulty increases over time to make survival more challenging.

## Technologies Used

- Arduino C/C++
- 16×2 LCD interfacing
- Digital input and button handling
- Collision detection
- Random number generation
- Non-blocking timing using `millis()`
