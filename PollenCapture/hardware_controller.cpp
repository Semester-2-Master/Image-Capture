#include <ESP32Servo.h>

Servo myservo;
int pos = 0;
int run_time = 500;

void motor_step() {
    Serial.println("Stepping motor");
    myservo.attach(13);
    myservo.write(0);
    delay(run_time); 
    myservo.detach();

}
