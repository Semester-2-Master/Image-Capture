#include "esp_camera.h"

#include "camera.h"
#include "wifi_client.h"
#include "http_server.h"
#include "time.h"
#include "time_config.h"



// void test_camera() {
//   Serial.println("test_camera");
//   camera_fb_t * fb = NULL;
  
//   fb = esp_camera_fb_get();

//   if(!fb) {
//     Serial.println("Camera capture failed");
//     return;
//   }
//   //change to send file through wifi
//   //write_file(filename, fb->buf, fb->len);
//   esp_camera_fb_return(fb);

//   Serial.println("Camera capture success");
// }


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_wifi();
  init_camera();
  init_server();

  //time
  init_time();
  
  
}

void loop() {
}
