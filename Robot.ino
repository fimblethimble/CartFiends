// Initialize variables, functions, libraries here
// #define and #include
#include <PIDLoop.h>      // NewPing Library to read ultrasonic sensors
#include <Pixy2.h>        // Pixy2 Libraries
#include <Pixy2CCC.h>     // Need to review Pixy documentation
#include <Pixy2I2C.h>     // to determine which of these are necessary.
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>   //end Pixy2 Libraries
// define pins for driving motor
// MAKE SURE THE INPUTS ARE WIRED TO THESE PINS
    // Motor1
#define in1 10 // HbridgeA 1
#define in2 9  // HbridgeA 2
#define enA 8  // PWM1
    // Motor2
#define in3 5  // HbridgeB 1
#define in4 7  // HbridgeB 2
#define enB 6  // PWM2
// define pins for ultrasonic array
#define TRIGGER_PIN 1 // decide what pins later
#define ECHO_PIN 0    // I believe these can be mapped to TX/RX pins
#define MAX_DISTANCE 300
// set new ping at defined pins/distance. MAX_DISTANCE is optional.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE)
Pixy pixy; // initialize global instance of pixy
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
  Serial.begin(115200); // start 115200bt/s communication for NewPing & cam
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
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000); //NOTE: Delay = motor runtime
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void reverse()
{
  // this function will run the motors in one direction at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000); //NOTE: Delay = motor runtime
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void right() // NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  // run motors for delay(runtime)
  delay(2000);
  // turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void left() //NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000); //NOTE: Delay = motor runtime
  // turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void demoTwo()  //acceleration motor demo
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void loop() // main method to call the rest
{
  // demoOne();
  // delay(1000);
  demoTwo();
  delay(1000);
}
