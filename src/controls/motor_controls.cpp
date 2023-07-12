#include "controls/motor_controls.h"

#include <Arduino.h>
#include "config.h"

void initMotorControls()
{
    for (unsigned int motor_index = 0; motor_index < MOTOR_COUNT; motor_index++)
    {
        for (unsigned int pin_index = 0; pin_index < 3; pin_index++)
        {
            const unsigned int pin = MOTOR_PINS[motor_index][pin_index];
            Serial.printf("Setting pin %d as OUTPUT\r\n", pin);
            pinMode(pin, OUTPUT);
        }
    }
}

void turnOffAllMotors()
{
    for (unsigned int motor_index = 0; motor_index < MOTOR_COUNT; motor_index++)
    {
        setMotor(motor_index, 0, 0);
    }
}

void setMotor(unsigned int motor_index, unsigned int action, unsigned int speed)
{
    if (!validateSetMotorParameters(motor_index, action, speed))
    {
        return;
    }

    const unsigned int pin_one = MOTOR_PINS[motor_index][0];
    const unsigned int pin_two = MOTOR_PINS[motor_index][1];
    const unsigned int pin_pwm = MOTOR_PINS[motor_index][2];

    if (action == Forward)
    {
        digitalWrite(pin_one, HIGH);
        digitalWrite(pin_two, LOW);
        analogWrite(pin_pwm, speed);
    }
    else if (action == Backward)
    {
        digitalWrite(pin_one, LOW);
        digitalWrite(pin_two, HIGH);
        analogWrite(pin_pwm, speed);
    }
    else if (action == Stop)
    {
        digitalWrite(pin_one, HIGH);
        digitalWrite(pin_two, HIGH);
        analogWrite(pin_pwm, 255);
    }
    else if (action == Neutral)
    {
        digitalWrite(pin_one, HIGH);
        digitalWrite(pin_two, HIGH);
        analogWrite(pin_pwm, 0);
    }
}

bool validateSetMotorParameters(unsigned int motor_index, unsigned int action, unsigned int speed)
{
    if (motor_index >= MOTOR_COUNT)
    {
        Serial.printf("Invalid motor index: '%d'\r\n", motor_index);
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