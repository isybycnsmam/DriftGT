#include "website_handlers.h"
#include "static_website_content.h"
#include "ESPAsyncWebServer.h"

void init_website_handlers(AsyncWebServer *server) {
	Serial.println("Initializing webserver endpoints");

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->redirect("/index.html"); });

	server->on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/html", INDEX_CONTENT); });

	server->on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/javascript", SCRIPTS_CONTENT); });

	server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/css", STYLE_CONTENT); });
}