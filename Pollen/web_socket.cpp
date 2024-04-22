#include "web_socket.h"

WebSocketsServer webSocket = WebSocketsServer(81);
bool online = false;
int connection = -1;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
        Serial.printf("hi from socket");

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
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\n", num, length);
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }
}

void init_socket() {
  Serial.printf("init socket begin");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
 