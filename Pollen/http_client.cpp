#include <WiFi.h>
#include "esp_camera.h"

String serverName = "192.168.1.142";
int port = 5194;
String serverPath = "/Image";
WiFiClient client;

void post_picture() {
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverName.c_str(), port)) {
      Serial.println("Connection successful!");

      camera_fb_t *fb = esp_camera_fb_get();
      if (!fb) {
        Serial.println("Failed to capture image");
        return;
      }

      String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"file\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
      String tail = "\r\n--RandomNerdTutorials--\r\n";
      size_t imageLen = fb->len;
      size_t extraLen = head.length() + tail.length();
      size_t totalLen = imageLen + extraLen;

      // Send HTTP POST request headers
      client.println("POST " + serverPath + " HTTP/1.1");
      client.println("Host: " + serverName + ":" + String(port));
      client.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
      client.println("Content-Length: " + String(totalLen));
      client.println();
      
      // Send image data
      Serial.println("Uploading image");
      client.print(head);
      client.write(fb->buf, fb->len);
      client.print(tail);
      Serial.println("Uploading image done");

      // Wait for response
      delay(10); // Allow time for server to process
      while (client.available()) {
        char c = client.read();
        Serial.print(c);
      }

      // Clean up
      client.stop();
      esp_camera_fb_return(fb);
    } else {
      Serial.println("Connection failed!");
    }
  }
}
