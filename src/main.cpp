#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "controls/motor_controls.h"
#include "controls/light_controls.h"
#include "controls/buzzer_controls.h"

#include "handlers/websocket_handlers.h"
#include "handlers/website_handlers.h"

#include "config.h"

DNSServer dnsServer;
AsyncWebServer server(WEB_SERVER_PORT);

void initWebServices()
{
	Serial.printf("Initializing AP with wifi name: '%s'\r\n", SSID);
	WiFi.softAP(SSID);

	Serial.printf("Setting board host name: '%s'\r\n", HOST_NAME);
	WiFi.setHostname(HOST_NAME);

	Serial.printf("Starting dns server on port: '%d'\r\n", DNS_PORT);
	dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

	Serial.println("Initializing websocket handlers");
	initWebsocketHandlers(&server);

	Serial.println("Initializing website handlers");
	initWebsiteHandlers(&server);

	Serial.println("Starting webserver");
	server.begin();
}

void initControls()
{
	Serial.println("Initializing motors controls");
	initMotorControls();

	Serial.println("Initializing light controls");
	initLightControls();

	Serial.println("Initializing buzzer controls");
	initBuzzerControls();
}

void setup()
{
	Serial.begin(BAUD_RATE);

	initWebServices();
	initControls();

	Serial.println("Setup complete");
}

void loop()
{
	dnsServer.processNextRequest();
}