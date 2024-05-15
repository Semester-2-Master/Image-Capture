//#include <C:\Users\magnu\Documents\Arduino\libraries\ServoESP32\src\Servo.h>

#include <ESP32Servo.h>

static const int servoPin = 12;
Servo myservo;



void init_motor() {

  myservo.attach(servoPin);
  myservo.write(90);
  Serial.println("motor init done");
}

void motor_step(){
  Serial.println("Stepping motor");
  //change 0 to change how much servo rotates
  myservo.write(0);
  delay(1000);
  myservo.write(90);
  Serial.println("motor stopped");
}

void init_light(){


}