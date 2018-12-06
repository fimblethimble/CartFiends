#include <Servo.h>        // Servo Library for motor control
// Motor Setup
Servo left;  // initialize left motor object
Servo right; // initialize right motor object
int speedA = 1000; // left motor (1) (microseconds)
int speedB = 1000; // right motor (2) (microseconds)
// There are two motor drivers connected to each motor, with one inputs each.
// Motor1
#define signal1 2 // left motor
// Motor2
#define signal2 3 // right motor
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
  delay(6000);
  Serial.println("FWD 10%");
  driveForward(1100,1100);
  delay(4000);
  Serial.println("FWD 20%");
  driveForward(1200,1200);
  delay(4000);
  Serial.println("FWD 30%");
  driveForward(1300,1300);
  delay(4000);
  Serial.println("FWD 40%");
  driveForward(1400,1400);
  delay(4000);
  Serial.println("FWD 50%");
  driveForward(1500,1500);
  delay(4000);
  Serial.println("FWD 60%");
  driveForward(1600,1600);
  delay(4000);
  Serial.println("FWD 70%");
  driveForward(1700,1700);
  delay(4000);
  Serial.println("FWD 80%");
  driveForward(1800,1800);
  delay(4000);
  Serial.println("FWD 90%");
  driveForward(1900,1900);
  delay(4000);
  Serial.println("FWD 90%");
  driveForward(2000,2000);
  delay(4000);
}
