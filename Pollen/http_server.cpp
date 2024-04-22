#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SD_MMC.h"

AsyncWebServer server(80);

class PollenServer {
  public:
    void init();
};

void PollenServer::init() {
  Serial.println("Web server init");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD_MMC, "/hair.jpg", "image/jpeg");
  });

  server.serveStatic("/", SD_MMC, "/");

  server.begin();

  Serial.println("Web server init done");
}
