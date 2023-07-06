#include "config.h"

const unsigned int MOTOR_COUNT = 2;

const int motor_pins[MOTOR_COUNT][3] = {
    // { pin 1, pin 2, pwm pin }
    {13, 12, 14}, // motor 1
    {4, 5, 0},    // motor 2
};


const int WEB_SERVER_PORT = 80;
const int DNS_PORT = 53;
const char* WEB_SOCKET_PATH = "/ws";
const char* SSID = "DriftGT";
const char* HOST_NAME = "driftgt";