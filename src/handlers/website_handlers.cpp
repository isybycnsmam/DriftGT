#include "handlers/website_handlers.h"

#include "handlers/static_website_content.h"
#include "ESPAsyncWebServer.h"

void initWebsiteHandlers(AsyncWebServer *server) {
	initStaticContentEndpoints(server);

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->redirect("/index.html"); });
}