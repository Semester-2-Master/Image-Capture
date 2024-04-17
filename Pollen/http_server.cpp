#include <WebServer.h>
#include <Arduino.h>
#include "sd.h"

static WebServer *server = nullptr;

class PollenServer {
  public:
    void init();
    WebServer* getServer();

    static void printDirectory() {
      server->send(200, "text/plain", "hello world from server class");
    }

    static void printMessage() {
      char **file_list = NULL;
      int count = 0;
      print_card(&file_list, &count);

      server->send(200, "text/plain", file_list[3]);
    }
};

void PollenServer::init() {
  Serial.println("Web server init");
  server = new WebServer(80);
  server->on("/", HTTP_GET, PollenServer::printDirectory);
  server->on("/msg", HTTP_GET, PollenServer::printMessage);
  server->begin();
  Serial.println("Web server init done");
}

WebServer* PollenServer::getServer() {
  return server;
}
