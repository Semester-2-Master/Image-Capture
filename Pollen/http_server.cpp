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

  static void serveImg() {
    Serial.println("ServeIMG here");
    File myFile;
    readFile(SD_MMC, "/hair.jpg", &myFile);

    if (!myFile) {
        server->send(500, "text/plain", "Failed to open file for reading");
        return;
    }

    server->setContentLength(myFile.size()); 
    server->sendHeader("Content-Type", "image/jpeg"); 
    server->send(200, "application/octet-stream"); 

    // ridiculously slow
    while (myFile.available()) {
        server->client().write(myFile.read());
    }

    myFile.close(); 
}

};

void PollenServer::init() {
  Serial.println("Web server init");
  server = new WebServer(80);
  server->on("/", HTTP_GET, PollenServer::printDirectory);
  server->on("/msg", HTTP_GET, PollenServer::printMessage);
  server->on("/png", HTTP_GET, PollenServer::serveImg);

  server->begin();
  Serial.println("Web server init done");
}

WebServer* PollenServer::getServer() {
  return server;
}
