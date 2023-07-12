#include "controls/motor_controls.h"

#include <Arduino.h>
#include "config.h"

void init_motor_controls()
{
    for (unsigned int first_index = 0; first_index < MOTOR_COUNT; first_index++)
    {
        for (unsigned int second_index = 0; second_index < 3; second_index++)
        {
            const unsigned int pin = MOTOR_PINS[first_index][second_index];
            Serial.printf("Setting pin %d as OUTPUT\r\n", pin);
            pinMode(pin, OUTPUT);
        }
    }
}

void setMotor(unsigned int motor, unsigned int action, unsigned int speed)
{
    if (!validateSetMotorParameters(motor, action, speed))
    {
        return;
    }

    const unsigned int pin1 = MOTOR_PINS[motor][0];
    const unsigned int pin2 = MOTOR_PINS[motor][1];
    const unsigned int pwm = MOTOR_PINS[motor][2];
    
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

bool validateSetMotorParameters(unsigned int motor, unsigned int action, unsigned int speed)
{
    if (motor >= MOTOR_COUNT)
    {
        Serial.printf("Invalid motor index: '%d'\r\n", motor);
        return false;
    }

    if (action > 3)
    {
        Serial.printf("Invalid action: '%d'\r\n", action);
        return false;
    }

    if (speed > 255)
    {
        Serial.printf("Invalid speed: '%d'\r\n", speed);
        return false;
    }

    return true;
}