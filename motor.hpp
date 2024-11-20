#pragma once

#include <Arduino.h>

struct Motor
{
    byte inp1Pin;
    byte inp2Pin;
    byte enablePin;

    void init()
    {
        pinMode(inp1Pin, OUTPUT);
        pinMode(inp2Pin, OUTPUT);
        pinMode(enablePin, OUTPUT);
        stop();
    }

    void stop()
    {
        digitalWrite(inp1Pin, LOW);
        digitalWrite(inp2Pin, LOW);
        analogWrite(enablePin, 0);
    }

    void spin(bool forward = true, unsigned int speed = 1023)
    {
        speed = constrain(speed, 0, 1023);
        digitalWrite(inp1Pin, forward ? HIGH : LOW);
        digitalWrite(inp2Pin, forward ? LOW : HIGH);
        analogWrite(enablePin, speed);
    }
};