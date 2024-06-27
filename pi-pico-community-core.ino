#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico!");
  myservo.attach(9);
}

void loop() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
}
