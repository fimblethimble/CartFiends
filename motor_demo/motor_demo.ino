#include <Servo.h>        // Servo Library for motor control
// Motor Setup
Servo left;  // initialize left motor object
Servo right; // initialize right motor object
int speedA = 1000; // left motor (1) (microseconds)
int speedB = 1000; // right motor (2) (microseconds)
// There are two motor drivers connected to each motor, with one inputs each.
// Motor1
#define signal1 3 // left motor
// Motor2
#define signal2 2 // right motor
// end declarations
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
  Serial.begin(9600); // start 115200bt/s communication for NewPing & cam
  // set all the motor control pins to outputs
  // set all the motor control pins to outputs
    left.attach(signal1,1000,2000);   // (pin,min,max)
    left.writeMicroseconds(1000);
    right.attach(signal2,1000,2000);  // (pin,min,max)
    right.writeMicroseconds(1000);
}
//
// NOTE: functions will be listed first, then main method calls them at the end
//
void driveForward(int speedA, int speedB)
{
// this function will run the motors in one direction at a fixed speed
  left.writeMicroseconds(speedA);
  right.writeMicroseconds(speedB);
}
//
void driveStop() //turns off all motors
{
  left.writeMicroseconds(1000);
  right.writeMicroseconds(1000);
}
//
void loop() // main method to call the rest
{
  Serial.println("SWITCH OFF");
  driveStop();
  delay(5000);
  Serial.println("SWITCH ON LEFT");
  driveForward(1500,1000);
  delay(5000);
  Serial.println("SWITCH TO RIGHT");
  driveForward(1000,1500);
  delay(5000);
  Serial.println("---------------");
  //Serial.println("FORWARD 75%");
  //driveForward(1750,1750);
  //delay(2000);
  //Serial.println("STOP");
  //driveStop();
  //delay(2000);
  //Serial.println("FORWARD 100%");
  //driveForward(2000,2000);
  //Serial.println("STOP");
  //driveStop();
  //delay(2000);
}
