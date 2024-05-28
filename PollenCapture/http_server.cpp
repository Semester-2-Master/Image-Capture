#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp_camera.h"
#include "time_config.h"

AsyncWebServer server(80);
camera_fb_t * fb = nullptr;

void init_server() {
  Serial.println("Web server init");

 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
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

    const size_t maxTimeBufferSize = 30; // Maximum size for the time string buffer
    char timeBuffer[maxTimeBufferSize]; // Buffer to hold the formatted time string
    // Obtain the current time and store it in the time buffer
    get_time(timeBuffer, maxTimeBufferSize);
      // Construct the filename with the time string
    String filename = String(timeBuffer) + ".jpg";
    
    response->addHeader("Content-Disposition", "inline; filename=" + filename);
    request->send(response);

    Serial.println("request end");
  });


  server.begin();

  Serial.println("Web server init done");
}
