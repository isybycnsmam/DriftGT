#include "motor_controls.h"
#include <Arduino.h>
#include "config.h"

void init_motor_controls()
{
    Serial.println("Initializing motors control pins.");

    for (unsigned int first_index = 0; first_index < MOTOR_COUNT; first_index++)
    {
        for (unsigned int second_index = 0; second_index < 3; second_index++)
        {
            const unsigned int pin = motor_pins[first_index][second_index];
            Serial.printf("Setting pin %d to OUTPUT\r\n", pin);
            pinMode(pin, OUTPUT);
        }
    }
}

void setMotor(int motor, MotorAction action, int speed)
{
    int pin1 = motor_pins[motor][0];
    int pin2 = motor_pins[motor][1];
    int pwm = motor_pins[motor][2];

    if (action == Forward)
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        analogWrite(pwm, speed);
    }
    else if (action == Backward)
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        analogWrite(pwm, speed);
    }
    else if (action == Stop)
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
        analogWrite(pwm, 255);
    }
    else if (action == Neutral)
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
        analogWrite(pwm, 0);
    }
}