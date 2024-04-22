#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SD_MMC.h"
#include "esp_camera.h"

AsyncWebServer server(80);
camera_fb_t * fb = nullptr;

class PollenServer {
  public:
    void init();
};

void PollenServer::init() {
  Serial.println("Web server init");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD_MMC, "/hair.jpg", "image/jpeg");
  });

  server.on("/capture", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("request begin");

    fb = esp_camera_fb_get();
    AsyncWebServerResponse *response = request->beginChunkedResponse("image/jpeg", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
      //Write up to "maxLen" bytes into "buffer" and return the amount written.
      //index equals the amount of bytes that have been already sent
      //You will be asked for more data until 0 is returned
      //Keep in mind that you can not delay or yield waiting for more data!

      int len = fb->len - index;
      if (len > maxLen) {
        len = maxLen;
      }
      else if (len <= 0) {
        Serial.println("esp_camera_fb_return");
        esp_camera_fb_return(fb);
        return 0;
      }

      memcpy(buffer, fb->buf + index, len);

      return len;
    });

    request->send(response);

    Serial.println("request end");
  });

  server.serveStatic("/", SD_MMC, "/");

  server.begin();

  Serial.println("Web server init done");
}
