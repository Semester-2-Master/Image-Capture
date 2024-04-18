#include "esp_camera.h"

#include "sd.h"
#include "camera.h"
#include "wifi_ap.h"
#include "http_server.h"

PollenServer ps;

void test_sd() {
  char *filename = "/test2.txt";
  uint8_t *content = (uint8_t *)"hello world";
  int content_len = 11;
  write_file(filename, content, content_len);
}

void test_camera() {
  Serial.println("test_camera");
  camera_fb_t * fb = NULL;
  char *filename = "/picture.jpg";
  
  fb = esp_camera_fb_get();

  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  write_file(filename, fb->buf, fb->len);
  esp_camera_fb_return(fb);

  Serial.println("Camera capture success");
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_sd();
  init_camera();
  init_wifi();

  // Initialize web server
  ps.init();

  // test SD card access
  //test_sd();

  // test camera and save picture to SD card
  //test_camera();



  

  // char **file_list = NULL;
  // int count = 0;
  // print_card(&file_list, &count);

  // Serial.print("Count: ");
  // Serial.println(count);

  // for (int i = 0; i < count; i++) {
  //   Serial.print("File: ");
  //   Serial.println(file_list[i]);
  // }
}

void loop() {
  ps.getServer()->handleClient();
}
