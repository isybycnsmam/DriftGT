#include "websocket_handlers.h"

#include "ESPAsyncWebServer.h"
#include "motor_controls.h"
#include "config.h"

AsyncWebSocket ws(WEB_SOCKET_PATH);

void init_websocket_handlers(AsyncWebServer *server)
{
	Serial.println("Initializing websocket");

	ws.onEvent(onEvent);
	server->addHandler(&ws);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
	if (type == WS_EVT_DATA)
	{
		handleMotorCommand(data, len);
	}
	else if (type == WS_EVT_CONNECT)
	{
		Serial.println("Client connected");
	}
	else if (type == WS_EVT_DISCONNECT)
	{
		Serial.println("Client disconnected");
	}
	else
	{
		Serial.print("Unknown websocket event: '");
		Serial.println(String((char *)data));
	}
}

int charToInt(uint8_t ch)
{
	return ch - 48;
}

bool validateParameter(const char *name, int value, int min, int max)
{
	if (value < min || value > max)
	{
		Serial.printf("Invalid %s: '%d'\r\n", name, value);
		return false;
	}

	return true;
}

void handleMotorCommand(uint8_t *data, size_t len)
{
	if (!validateParameter("length", len, 5, 5))
	{
		return;
	}

	int motor = charToInt(data[0]);
	if (!validateParameter("motor", motor, 0, MOTOR_COUNT - 1))
	{
		return;
	}

	int command = charToInt(data[1]);
	if (!validateParameter("command", command, 0, 3))
	{
		return;
	}

	int speed = charToInt(data[2]) * 100 +
				charToInt(data[3]) * 10 +
				charToInt(data[4]);
	if (!validateParameter("speed", speed, 0, 255))
	{
		return;
	}

	setMotor(motor, (MotorAction)command, speed);
}