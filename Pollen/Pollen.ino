#include "esp_camera.h"

#include "sd.h"
#include "camera.h"

void test_sd() {
  char *filename = "/test2.txt";
  uint8_t *content = (uint8_t *)"hello world";
  int content_len = 11;
  write_file(filename, content, content_len);
}

void test_camera() {
  camera_fb_t * fb = NULL;
  char *filename = "/picture.jpg";
  
  fb = esp_camera_fb_get();

  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  write_file(filename, fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

void setup() {
  init_sd();
  init_camera();

  // test SD card access
  //test_sd();

  // test camera and save picture to SD card
  delay(100);
  test_camera();
}

void loop() {
  // put your main code here, to run repeatedly:

}
