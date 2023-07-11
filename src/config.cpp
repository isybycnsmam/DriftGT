#include "config.h"

const unsigned int MOTOR_COUNT = 2;

const int MOTOR_PINS[MOTOR_COUNT][3] = {
    // { pin 1, pin 2, pwm pin }
    {13, 12, 14}, // motor 1
    {4, 5, 0},    // motor 2
};

const int LED_DATA_PIN = 2;
const int LED_NUM_PIXELS = 2;
const int BUZZER_PIN = 16;

const int BAUD_RATE = 115200;

const int WEB_SERVER_PORT = 80;
const int DNS_PORT = 53;
const char* WEB_SOCKET_PATH = "/ws";
const char* SSID = "DriftGT";
const char* HOST_NAME = "driftgt";