#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
int servoPin = 13;  // Pin to which the servo is attached

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  myservo.setPeriodHertz(50);    // Standard 50 Hz servo
  myservo.attach(servoPin, 500, 2400); // Attaches the servo on pin 13 to the servo object
}

void loop() {
  // Sweep from 90 degrees (center) to 150 degrees (60 degrees to the right)
  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(30);             // waits 30ms for the servo to reach the position
  }

  // Sweep back from 150 degrees to 30 degrees (60 degrees to the left)
  for (pos = 180; pos >= 20; pos -= 1) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(30);             // waits 30ms for the servo to reach the position
  }

  // Sweep back to center (90 degrees)
  for (pos = 20; pos <= 90; pos += 1) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(30);             // waits 30ms for the servo to reach the position
  }
}
