#include "esp_camera.h"
#include "camera.h"
#include "wifi_client.h"
#include "http_server.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_wifi();
  init_camera();
  init_server();
}

void loop() {
}
