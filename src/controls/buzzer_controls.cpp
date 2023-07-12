#include "controls/buzzer_controls.h"

#include <Arduino.h>
#include "config.h"

void initBuzzerControls() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void setBuzzerState(bool state) {
    digitalWrite(BUZZER_PIN, state);
}