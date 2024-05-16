//#include <C:\Users\magnu\Documents\Arduino\libraries\ServoESP32\src\Servo.h>

#include <ESP32Servo.h>


Servo myservo;

int pos = 0;



//Position goes 0>90 positive rotation 90>180 neg
void update_pos(){
  pos += 5;
  if (pos > 90) {
    pos = 0; 
  }
   Serial.println(pos);
}

void init_motor() {
 Serial.println("motor init");
  myservo.setPeriodHertz(50); 
  myservo.attach(12); // Attach the servo to pin 12 with min and max pulse width
  myservo.write(0);
  update_pos();
  Serial.println("motor init done");
}



void motor_step(){
  Serial.println("Stepping motor");
  delay(2000); // Delay for 2 seconds before reattaching
  //myservo.attach(12, 1000, 2000); // Reattach the servo after it has been detached
  myservo.write(pos); // Move servo to the 0-degree position
  update_pos();
  //myservo.detach(); // Turn the servo off
  delay(1000); // Delay for 2 seconds
  myservo.write(0);
  Serial.println("motor stopped");
}
