#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H

#include <WebSocketsServer.h>

extern WebSocketsServer webSocket;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);
void init_socket();

#endif
