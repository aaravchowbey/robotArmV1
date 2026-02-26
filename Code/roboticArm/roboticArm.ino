#include "ServoEasing.hpp"

// Creating a instance of each servo
ServoEasing base;
ServoEasing shoulder;
ServoEasing elbow;
ServoEasing wrist;
ServoEasing wristRotate;
ServoEasing gripper;

const int MOVE_DURATION = 3000; // Duration for servo movements in milliseconds

void setup() {
  Serial.begin(9600); // Opens serial port, sets data rate to 9600 bps
  
  // Wait for serial connection
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  // Assigning each servo a pin and setting its starting position
  base.attach(7, 90);
  shoulder.attach(6, 90);
  elbow.attach(5, 90);
  wrist.attach(4, 90);
  wristRotate.attach(3, 90);
  gripper.attach(2, 0);
  
  delay(1000); // Giving servo time to reach starting position

  // Setting the easing type for each servo
  base.setEasingType(EASE_SINE_IN_OUT);
  shoulder.setEasingType(EASE_SINE_IN_OUT);
  elbow.setEasingType(EASE_SINE_IN_OUT);
  wrist.setEasingType(EASE_SINE_IN_OUT);
  wristRotate.setEasingType(EASE_SINE_IN_OUT);
  gripper.setEasingType(EASE_SINE_IN_OUT);
  
  Serial.println("READY"); // Signal to Python that Arduino is ready
}

void loop() {
  updateAllServos(); // Update servo positions if moving
  
  // Check if data is available on serial port
  if (Serial.available() > 0) {
    // Read the incoming string until newline
    String data = Serial.readStringUntil('\n');
    data.trim(); // Remove any whitespace
    
    // Parse the comma-separated angles
    float angles[5];
    int angleIndex = 0;
    int lastComma = -1;
    
    for (int i = 0; i <= data.length(); i++) {
      if (i == data.length() || data.charAt(i) == ',') {
        if (angleIndex < 5) {
          String angleStr = data.substring(lastComma + 1, i);
          angles[angleIndex] = angleStr.toFloat();
          angleIndex++;
          lastComma = i;
        }
      }
    }
    
    // Check if we received all 5 angles
    if (angleIndex == 5) {
      // Start moving all servos to target angles
      base.startEaseTo(angles[0], MOVE_DURATION);
      shoulder.startEaseTo(angles[1], MOVE_DURATION);
      elbow.startEaseTo(angles[2], MOVE_DURATION);
      wrist.startEaseTo(angles[3], MOVE_DURATION);
      wristRotate.startEaseTo(angles[4], MOVE_DURATION);
      
      // Wait for all servos to complete their movement
      while (base.isMoving() || shoulder.isMoving() || elbow.isMoving() || 
             wrist.isMoving() || wristRotate.isMoving()) {
        updateAllServos();
        delay(10);
      }
      
      // Send confirmation back to Python
      Serial.println("DONE");
    } else {
      Serial.println("ERROR: Expected 5 angles");
    }
  }
}
