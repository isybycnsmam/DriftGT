#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int MOTOR_COUNT;
extern const unsigned int MOTOR_PINS[][3];

extern const unsigned int LED_DATA_PIN;
extern const unsigned int LED_NUM_PIXELS;
extern const unsigned int BUZZER_PIN;

extern const unsigned long BAUD_RATE;

extern const unsigned int WEB_SERVER_PORT;
extern const unsigned int DNS_PORT;
extern const char* WEB_SOCKET_PATH;
extern const char* SSID;
extern const char* HOST_NAME;

#endif // CONFIG_H