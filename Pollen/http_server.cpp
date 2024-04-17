#include <WebServer.h>
#include <Arduino.h>

static WebServer *server = nullptr;

class PollenServer {
  public:
    void init();
    WebServer* getServer();

    static void printDirectory() {
      server->send(200, "text/plain", "hello world from server class");
    }
};

void PollenServer::init() {
  Serial.println("Web server init");
  server = new WebServer(80);
  server->on("/", HTTP_GET, PollenServer::printDirectory);
  server->begin();
  Serial.println("Web server init done");
}

WebServer* PollenServer::getServer() {
  return server;
}
