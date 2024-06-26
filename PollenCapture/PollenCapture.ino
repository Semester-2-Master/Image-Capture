#include "esp_camera.h"
#include "camera.h"
#include "wifi_client.h"
//#include "http_server.h"
#include "http_client.h"
#include "time.h"
#include "time_config.h"
#include "hardware_controller.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_wifi();
  init_camera();
  init_motor();
  init_time();
  
  delay(5000);

  post_picture();
  delay(2000);
  //motor_step();
  delay(30000);

    post_picture();
  delay(2000);
  //motor_step();
  delay(30000);
  
    post_picture();
  delay(2000);
  motor_step();
  delay(30000);

}

int counter =0;

void loop() {
  //
  post_picture();
  delay(2000);
  if(counter > 11){
    motor_step();
    counter = 0;
  }
  counter++;

  
  delay(1800000);

  //delay(30000);
}
