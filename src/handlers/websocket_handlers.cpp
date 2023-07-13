#include "handlers/websocket_handlers.h"

#include "controls/motor_controls.h"
#include "controls/light_controls.h"
#include "controls/buzzer_controls.h"

#include "ESPAsyncWebServer.h"
#include "config.h"

AsyncWebSocket ws(WEB_SOCKET_PATH);

void initWebsocketHandlers(AsyncWebServer *server)
{
	ws.onEvent(onEvent);
	server->addHandler(&ws);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
	if (type == WS_EVT_CONNECT)
	{
		Serial.println("Client connected");
		return;
	}

	if (type == WS_EVT_DISCONNECT)
	{
		Serial.println("Client disconnected");
		turnOffAllMotors();
		return;
	}

	if (type == WS_EVT_DATA)
	{
		onDataEvent(data, len);
		return;
	}

	if (type == WS_EVT_ERROR)
	{
		Serial.print("Websocket error event");
		return;
	}
}

void onDataEvent(uint8_t *data, size_t len)
{
	if (len == 4 && data[0] == 0) // motor command
	{
		setMotor(data[1], data[2], data[3]);
		return;
	}

	if (len == 4 && data[0] == 1) // lights command
	{
		setLights(data[1], data[2], data[3]);
		return;
	}

	if (len == 2 && data[0] == 2) // buzzer command
	{
		bool buzzer_on = data[1] == 1;
		setBuzzerState(buzzer_on);
		return;
	}

	Serial.println("Unknown websocket event data");
}