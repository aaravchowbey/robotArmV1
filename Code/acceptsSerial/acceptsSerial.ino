#include <Servo.h>

// Servo objects
Servo baseServo;        // base_joint
Servo shoulderServo;    // arm_one_joint
Servo elbowServo;       // arm_two_joint
Servo wristServo;       // wrist_rotate_joint
Servo gripperRotServo;  // gripper_rotate

void setup() {
  baseServo.attach(7);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  wristServo.attach(4);
  gripperRotServo.attach(3);
  
  Serial.begin(9600);
  Serial.println("Ready");
  
  homePosition();
}

void homePosition() {
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristServo.write(90);
  gripperRotServo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    // Expected format: "base,shoulder,elbow,wrist,gripper"
    // Example: "90,45,30,15,90"
    
    int idx1 = input.indexOf(',');
    int idx2 = input.indexOf(',', idx1 + 1);
    int idx3 = input.indexOf(',', idx2 + 1);
    int idx4 = input.indexOf(',', idx3 + 1);
    
    if (idx1 > 0 && idx2 > 0 && idx3 > 0 && idx4 > 0) {
      float base = input.substring(0, idx1).toFloat();
      float shoulder = input.substring(idx1 + 1, idx2).toFloat();
      float elbow = input.substring(idx2 + 1, idx3).toFloat();
      float wrist = input.substring(idx3 + 1, idx4).toFloat();
      float gripper = input.substring(idx4 + 1).toFloat();
      
      // Move servos
      baseServo.write(base);
      shoulderServo.write(shoulder);
      elbowServo.write(elbow);
      wristServo.write(wrist);
      gripperRotServo.write(gripper);
      
      Serial.println("OK");
    } else {
      Serial.println("ERROR");
    }
  }
}