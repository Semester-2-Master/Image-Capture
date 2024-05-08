#include "esp_camera.h"
#include "camera.h"
#include "wifi_client.h"
//#include "http_server.h"
#include "http_client.h"
// #include "time.h"
// #include "time_config.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_wifi();
  init_camera();
  //init_server();
  // init_time();
  init_client();
}

void loop() {
  sendRequest();
  delay(5000);
}
