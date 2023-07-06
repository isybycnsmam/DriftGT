#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "motor_controls.h"
#include "websocket_handlers.h"
#include "website_handlers.h"
#include "config.h"

DNSServer dnsServer;
AsyncWebServer server(WEB_SERVER_PORT);

void init_webservices()
{
	Serial.printf("Initializing AP with wifi name: '%s'\r\n", SSID);
	WiFi.softAP(SSID);

	Serial.printf("Setting board host name: '%s'\r\n", HOST_NAME);
	WiFi.setHostname(HOST_NAME);

	Serial.printf("Starting dns server on port: '%d'\r\n", DNS_PORT);
	dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
}

void setup()
{
	Serial.begin(115200);

	init_webservices();

	init_websocket_handlers(&server);
	init_website_handlers(&server);

	Serial.println("Starting webserver");
	server.begin();

	init_motor_controls();

	Serial.println("Setup complete");
}

void loop()
{
	dnsServer.processNextRequest();
}