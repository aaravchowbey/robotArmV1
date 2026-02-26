#include <Servo.h>

Servo myservo;  // creates a servo object

void setup() {
  // servo.attach(pin)
  // servo.attach(pin, min, max)
  // 7 is base, 6 is shoulder, 5 is elbow, etc  
  myservo.attach(2);

  myservo.write(0);  // sets servo to midpoint
}

void loop() {
  // put your main code here, to run repeatedly:

}
