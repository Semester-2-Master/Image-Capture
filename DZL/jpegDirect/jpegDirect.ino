#include <WiFi.h>
#include <WebSocketsServer.h>
#include "camera.h"
WebSocketsServer webSocket = WebSocketsServer(81);
bool online = false;

int connection = -1;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      connection = -1;
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        connection = num;
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);

      // send message to client
      // webSocket.sendTXT(num, "message here");

      // send data to all connected clients
      // webSocket.broadcastTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\n", num, length);

      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  initCamera();
  WiFi.begin("DZL_NET2", "dzlandvanessa");
}

int frameNo = 0;
void loop() {

  if (online) {
    if (WiFi.status() != WL_CONNECTED) {
      online = false;
    }
  } else {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Local IP:");
      Serial.println(WiFi.localIP());
      webSocket.begin();
      webSocket.onEvent(webSocketEvent);
      online = true;
    }
  }

  camera_fb_t* fb = esp_camera_fb_get();
  if (fb) {
    //Serial.println(frameNo++);

    //DoYour Stuff
    if (online && connection != -1)
      webSocket.sendBIN(connection, (uint8_t*)fb->buf, fb->len);
    esp_camera_fb_return(fb);
  }
  webSocket.loop();
}
