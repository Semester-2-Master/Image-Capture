#include <ESP32Servo.h>

Servo myservo;
int run_time = 400;

void init_motor() {
  myservo.attach(13);
}

void motor_step() {
  Serial.println("Stepping motor");
  for (int pos = 85; pos >= 60; pos -= 5) {
    myservo.write(pos);
    delay(100);
  }
  delay(run_time);
  myservo.write(90);
}
