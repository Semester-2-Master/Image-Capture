#include <Arduino.h>
#include "esp_camera.h"
#include "camera_pins.h"

  void init_camera() {
  Serial.println("Initializing camera");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; //YUV422,GRAYSCALE,RGB565,JPEG
  config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 10; //0-63, lower number means higher quality
  config.fb_count = 1;
  
  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.println("Camera init error");
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  s->set_vflip(s, 1); // flip it back
 // s->set_brightness(s, 1); // up the brightness just a bit
 // s->set_saturation(s, -2); // lower the saturation
 
  s->set_wb_mode(s, 2);   //maybe change?
    
  s->set_awb_gain(s, 0); // Disable AWB gain
  s->set_whitebal(s, 0); // Disable white balance
  s->set_gain_ctrl(s, 0); // Disable gain control
  s->set_agc_gain(s, 0); // Set AGC gain to 0
  s->set_exposure_ctrl(s, 0); // Disable exposure control
  s->set_aec2(s, 0); // Disable additional auto exposure control
  s->set_ae_level(s, 0); // Set AE level to 0
  s->set_aec_value(s, 0); // Set AEC value to 0
  s->set_lenc(s, 0); // Disable lens correction
  s->set_raw_gma(s, 0); // Disable RAW gamma correction
  s->set_bpc(s, 1); // Disable black pixel correction
  s->set_wpc(s, 1); // Disable white pixel correction



  // Read out first frame to avoid saving a green picture
  delay(500);
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  esp_camera_fb_return(fb);
  delay(500);

  Serial.println("Camera init success");
}
