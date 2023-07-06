#include "ESPAsyncWebServer.h"

#ifndef WEBSOCKET_HANDLERS
#define WEBSOCKET_HANDLERS

extern AsyncWebSocket ws;

void init_websocket_handlers(AsyncWebServer *server);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

int charToInt(uint8_t ch);
bool validateParameter(const char *name, int value, int min, int max);
void handleMotorCommand(uint8_t *data, size_t len);

#endif // WEBSOCKET_HANDLERS