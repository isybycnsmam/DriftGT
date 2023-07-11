#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int MOTOR_COUNT;
extern const int MOTOR_PINS[][3];

extern const int LED_DATA_PIN;
extern const int LED_NUM_PIXELS;
extern const int BUZZER_PIN;

extern const int BAUD_RATE;

extern const int WEB_SERVER_PORT;
extern const int DNS_PORT;
extern const char* WEB_SOCKET_PATH;
extern const char* SSID;
extern const char* HOST_NAME;

#endif // CONFIG_H