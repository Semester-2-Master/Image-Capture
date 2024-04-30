#include <WiFi.h>
#include "esp_camera.h"

String serverName = "127.0.0.1";
int port = 5194;
String serverPath = "/Image";
WiFiClient client;

void post_picture() {
  if(WiFi.status()== WL_CONNECTED){
    if (client.connect(serverName.c_str(), port)) {
      Serial.println("Connection successful!");

      camera_fb_t * fb = nullptr;
      fb = esp_camera_fb_get();
      
      String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
      String tail = "\r\n--RandomNerdTutorials--\r\n";

      uint16_t imageLen = fb->len;
      uint16_t extraLen = head.length() + tail.length();
      uint16_t totalLen = imageLen + extraLen;
    
      client.println("POST " + serverPath + " HTTP/1.1");
      client.println("Host: " + serverName);
      client.println("Content-Length: " + String(totalLen));
      client.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
      client.println();
      client.print(head);

      uint8_t *fbBuf = fb->buf;
      size_t fbLen = fb->len;
      for (size_t n=0; n<fbLen; n=n+1024) {
        if (n+1024 < fbLen) {
          client.write(fbBuf, 1024);
          fbBuf += 1024;
        }
        else if (fbLen%1024>0) {
          size_t remainder = fbLen%1024;
          client.write(fbBuf, remainder);
        }
      }   
      client.print(tail);
      client.stop();
      esp_camera_fb_return(fb);
    }
  }
}
