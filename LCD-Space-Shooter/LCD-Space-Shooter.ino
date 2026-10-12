#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

const int moveButton = 9;
const int shootButton = 10;

// Player
int shipRow = 0;

// Obstacles
int obs1Col = 15;
int obs2Col = 23;
int obs1Row;
int obs2Row;

// Bullet
bool bulletActive = false;
int bulletCol = 1;
int bulletRow = 0;

// Timing
unsigned long lastMove = 0;
unsigned long lastSpeedChange = 0;
unsigned long lastDifficultyIncrease = 0;
unsigned long gameStartTime = 0;

// Faster start difficulty
int speedDelay = 100;
int minSpeed = 70;
int maxSpeed = 120;

// Stats
long hits = 0;
long missed = 0;

// Row control
int lastGeneratedRow = 0;
int sameRowCount = 0;

int getNextRow()
{
    int row = random(0, 2);

    if (row == lastGeneratedRow)
    {
        sameRowCount++;

        if (sameRowCount >= 2)
        {
            row = !lastGeneratedRow;
            sameRowCount = 0;
        }
    }
    else
    {
        sameRowCount = 0;
    }

    lastGeneratedRow = row;

    return row;
}

void drawGame()
{
    lcd.clear();

    lcd.setCursor(0, shipRow);
    lcd.print(">");

    if (bulletActive)
    {
        lcd.setCursor(bulletCol, bulletRow);
        lcd.print(".");
    }

    if (obs1Col >= 0 && obs1Col < 16)
    {
        lcd.setCursor(obs1Col, obs1Row);
        lcd.print("O");
    }

    if (obs2Col >= 0 && obs2Col < 16)
    {
        lcd.setCursor(obs2Col, obs2Row);
        lcd.print("O");
    }

    // Show elapsed time in seconds
    unsigned long t =
        (millis() - gameStartTime) / 1000;

    lcd.setCursor(10, 0);

    if (t < 100)
        lcd.print(" ");

    if (t < 10)
        lcd.print(" ");

    lcd.print(t);
}

void showResults()
{
    unsigned long survivalTime =
        (millis() - gameStartTime) / 1000;

    int minutes = survivalTime / 60;
    int seconds = survivalTime % 60;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Survived:");

    lcd.setCursor(0, 1);

    if (minutes < 10)
        lcd.print("0");

    lcd.print(minutes);
    lcd.print(":");

    if (seconds < 10)
        lcd.print("0");

    lcd.print(seconds);

    while (1);
}

void setup()
{
    pinMode(moveButton, INPUT_PULLUP);
    pinMode(shootButton, INPUT_PULLUP);

    lcd.begin(16, 2);

    randomSeed(analogRead(A0));

    obs1Row = getNextRow();
    obs2Row = getNextRow();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("SPACE DODGER");

    lcd.setCursor(0, 1);
    lcd.print("Press Button");

    while (
        digitalRead(moveButton) == HIGH &&
        digitalRead(shootButton) == HIGH)
    {
    }

    gameStartTime = millis();

    drawGame();
}

void loop()
{
    // Difficulty ramp
    if (millis() - lastDifficultyIncrease > 10000)
    {
        if (minSpeed > 40)
            minSpeed -= 5;

        if (maxSpeed > 80)
            maxSpeed -= 5;

        lastDifficultyIncrease = millis();
    }

    // Random speed
    if (millis() - lastSpeedChange > 3000)
    {
        speedDelay = random(minSpeed, maxSpeed);
        lastSpeedChange = millis();
    }

    // Move button
    static bool prevMoveState = HIGH;
    bool moveState = digitalRead(moveButton);

    if (prevMoveState == HIGH &&
        moveState == LOW)
    {
        shipRow = !shipRow;
    }

    prevMoveState = moveState;

    // Shoot button
    static bool prevShootState = HIGH;
    bool shootState = digitalRead(shootButton);

    if (prevShootState == HIGH &&
        shootState == LOW)
    {
        if (!bulletActive)
        {
            bulletActive = true;
            bulletCol = 1;
            bulletRow = shipRow;
        }
    }

    prevShootState = shootState;

    // Game tick
    if (millis() - lastMove >= speedDelay)
    {
        lastMove = millis();

        obs1Col--;
        obs2Col--;

        if (bulletActive)
        {
            bulletCol++;

            if (bulletCol > 15)
            {
                bulletActive = false;
            }
        }

        // Bullet hit asteroid 1
        if (bulletActive &&
            bulletRow == obs1Row &&
            abs(bulletCol - obs1Col) <= 1)
        {
            hits++;

            obs1Col = random(16, 28);
            obs1Row = getNextRow();

            bulletActive = false;
        }

        // Bullet hit asteroid 2
        if (bulletActive &&
            bulletRow == obs2Row &&
            abs(bulletCol - obs2Col) <= 1)
        {
            hits++;

            obs2Col = random(18, 32);
            obs2Row = getNextRow();

            bulletActive = false;
        }

        // Game over on collision
        if ((obs1Col == 0 &&
             obs1Row == shipRow) ||
            (obs2Col == 0 &&
             obs2Row == shipRow))
        {
            showResults();
        }

        // Asteroid escaped
        if (obs1Col < 0)
        {
            obs1Col = random(16, 28);
            obs1Row = getNextRow();

            missed++;
        }

        if (obs2Col < 0)
        {
            obs2Col = random(18, 32);
            obs2Row = getNextRow();

            missed++;
        }

        drawGame();
    }
}