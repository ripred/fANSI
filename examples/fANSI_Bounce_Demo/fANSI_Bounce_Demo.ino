#include <Arduino.h>
#include <fANSI.h>
using namespace fANSI;
static int const Width  = 80;
static int const Height = 40;

struct Ball {
    int color, x, y, deltaX, deltaY;

    Ball(int clr = White) : color(clr) { set_random_spot(); }

    void set_random_spot() {
        x = random(1, Width);          y = random(1, Height);
        deltaX = random(2) ? -1 : 1;   deltaY = random(2) ? -1 : 1;
    }

    void check_bounce() {
        static const int left = 1, top = 1, right = Width - 1, bottom = Height - 1;
        if ((x + deltaX) <= left || (x - deltaX) <= left || (x + deltaX) >= right || (x - deltaX) >= right) { deltaX *= -1; }
        if ((y + deltaY) <= top || (y - deltaY) <= top || (y + deltaY) >= bottom || (y - deltaY) >= bottom) { deltaY *= -1; }
    }

    void update() {
        cursPos(x, y);
        setColor(Black, Back, ':');
        Serial.write(' ');
        x += deltaX;
        y += deltaY;
        cursPos(x, y);
        setColor(color, Back, ':');
        Serial.write(' ');

        cursOff();
    }
} balls[3];

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(34));
    for (Ball &ball : balls) {
        ball.set_random_spot();
    }
    cls();
    cursOff();
    border(0, 0, Width, Height, Black, White, White, Black);
    balls[0].color = Red + Bright;
    balls[1].color = White + Bright;
    balls[2].color = Blue + Bright;
}

void loop() {
    for (Ball &ball : balls) {
        ball.check_bounce();
        ball.update();
    }
}
