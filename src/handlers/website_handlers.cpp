#include "handlers/website_handlers.h"

#include "handlers/static_website_content.h"
#include "ESPAsyncWebServer.h"

void init_website_handlers(AsyncWebServer *server) {
	init_static_content_endpoints(server);

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->redirect("/index.html"); });
}