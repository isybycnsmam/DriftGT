#include "controls/buzzer_controls.h"

#include <Arduino.h>
#include "config.h"

void init_buzzer_controls() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void set_buzzer_state(bool state) {
    digitalWrite(BUZZER_PIN, state);
}