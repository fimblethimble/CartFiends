// Initialize variables, functions, libraries here
// #define and #include
#include <PIDLoop.h>
#include <Pixy2.h>
//Motor 1 pins
#define in1 22 // HbridgeA 1
#define in2 23  // HbridgeA 2
#define enA 2  // PWM1
    // Motor2
#define in3 5  // HbridgeB 1
#define in4 7  // HbridgeB 2
#define enB 6  // PWM2
// define pins for ultrasonic array
#define TRIGGER_PIN 1 // decide what pins later
#define ECHO_PIN 0    // I believe these can be mapped to TX/RX pins
#define MAX_DISTANCE 300
// set new ping at defined pins/distance. MAX_DISTANCE is optional.
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
  Serial.begin(9600); // start 115200bt/s communication for NewPing & cam
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
//
// NOTE: functions will be listed first, then main method calls them at the end
//
void forward()
{
  // this function will run the motors in one direction at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 255);
  // turn on motor B
  //digitalWrite(in3, HIGH);
  //digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  //analogWrite(enB, 200);
  delay(2000); //NOTE: Delay = motor runtime
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
}
//
void reverse()
{
  // this function will run the motors in one direction at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 255);
  // turn on motor B
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  //analogWrite(enB, 200);
  delay(2000); //NOTE: Delay = motor runtime
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
}
//
void loop() // main method to call the rest
{
  forward();
  delay(2000);
  reverse();
  delay(2000);
}
