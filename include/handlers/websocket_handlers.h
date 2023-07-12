#include "ESPAsyncWebServer.h"

#ifndef WEBSOCKET_HANDLERS
#define WEBSOCKET_HANDLERS

extern AsyncWebSocket ws;

void initWebsocketHandlers(AsyncWebServer *server);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void onDataEvent(uint8_t *data, size_t len);

#endif // WEBSOCKET_HANDLERS