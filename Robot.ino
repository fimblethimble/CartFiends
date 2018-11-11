// Initialize variables, functions, libraries here
// #define and #include
#include <PIDLoop.h>      // NewPing Library to read ultrasonic sensors
#include <Pixy2.h>        // Pixy2 Libraries
// Motor Setup
  // MAKE SURE THE INPUTS ARE WIRED TO THESE PINS
      // Motor1
  #define in1 10 // HbridgeA 1
  #define in2 9  // HbridgeA 2
  #define enA 8  // PWM1
      // Motor2
  #define in3 5  // HbridgeB 1
  #define in4 7  // HbridgeB 2
  #define enB 6  // PWM2
// Pixy Setup
  // Limit max velocity to highest PWM Value
  #define MAX_TRANSLATE_VELOCITY 255
  // min velocity may need to be 90 or 100 to avoid stalling.
  #define MIN_VELOCITY 80
  Pixy2 pixy; // initialize global instance of pixy
  // define motor speeds
  int speedLeft=0;
  int speedRight=0;
  // Define PIDLoops (Kp,Ki,Kd,boolean)
  PIDLoop panLoop(350, 0, 600, true);
  PIDLoop tiltLoop(500, 0, 700, true);
  PIDLoop rotateLoop(300, 600, 300, false);
  PIDLoop translateLoop(400, 800, 300, false);
// Pixy notes
  // CC1=Green
  // CC2=Blue
  // CC3=Pink
// Ultrasonic Setup
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
    Serial.begin(115200); // start 115200baud communication for camera
    Serial.print("Begin Serial Monitor\n");
  // set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
  // initialize pixyamc
  pixy.init();
  pixy.changeProg("color_connected_components"); // select CCC pixycam program
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
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 255);
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
  analogWrite(enA, 255);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 255);
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
  analogWrite(enA, 255);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 255);
  // run motors for delay(runtime)
  delay(500);  //NOTE: Delay = motor runtime
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
  analogWrite(enA, 255);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 255);
  delay(500); //NOTE: Delay = motor runtime
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
// CAMERA FUNCTIONS //
// Find largest block (index 0 = largest) at least .25s old (15 frames)
// Return block index, if no block return -1.
// "Locks on" to object
int16_t acquireBlock()
{
  if (pixy.ccc.numBlocks && pixy.ccc.blocks[0].m_age>15)
    return pixy.ccc.blocks[0].m_index;

  return -1;
}
// Find block with the index detailed in int16_t acquireBlock()
// within the current frame. If block not found, return NULL
Block *trackBlock(uint8_t index)
{
  uint8_t i;

  for (i=0; i<pixy.ccc.numBlocks; i++)
  {
    if (index==pixy.ccc.blocks[i].m_index)
      return &pixy.ccc.blocks[i];
  }

  return NULL;
}
// When we have the object,
void loop()
{
  static int16_t index = -1;
  int32_t panOffset, tiltOffset, headingOffset, left, right;
  Block *block=NULL;

  pixy.ccc.getBlocks();

  if (index==-1) // search....
  {
    Serial.println("Searching for block...");
    index = acquireBlock();
    if (index>=0)
      Serial.println("Found block!");
 }
  // If we've found a block, find it, track it
  if (index>=0)
     block = trackBlock(index);

  // If we're able to track it, move motors
  if (block)
  {
    // calculate pan and tilt errors
    panOffset = (int32_t)pixy.frameWidth/2 - (int32_t)block->m_x;
    tiltOffset = (int32_t)block->m_y - (int32_t)pixy.frameHeight/2;

    // calculate translate and rotate errors
    panOffset += panLoop.m_command - PIXY_RCS_CENTER_POS;
    tiltOffset += tiltLoop.m_command - PIXY_RCS_CENTER_POS - PIXY_RCS_CENTER_POS/2 + PIXY_RCS_CENTER_POS/8;

    rotateLoop.update(panOffset);
    translateLoop.update(-tiltOffset);

    // keep translation velocity below maximum
    if (translateLoop.m_command>MAX_TRANSLATE_VELOCITY)
      translateLoop.m_command = MAX_TRANSLATE_VELOCITY;

    // calculate left and right wheel velocities based on rotation and translation velocities
    left = -rotateLoop.m_command + translateLoop.m_command;
    right = rotateLoop.m_command + translateLoop.m_command;

    // set wheel velocities
    speedLeft=left;   //set these to pass into motor method
    //Serial.println(left);
    speedRight=right; //set these to pass into motor method
    //Serial.print("right speed: ",right)

    // print the block we're tracking -- wait until end of loop to reduce latency
    // issue move commands
    // to change turn tolerance, increase or decrease the value
    // that abs() is compared to
    block->print();
    Serial.println(speedLeft);
    Serial.println(speedRight);
    if (speedLeft>speedRight && abs(speedLeft-speedRight)>50)
      Serial.println("Turn right");
      right(); // turn right
    if (speedRight>speedLeft && abs(speedLeft-speedRight)>50)
      Serial.println("Turn left");
      left();  // turn left
    if (abs(speedLeft-speedRight)<=50)
      Serial.println("Move Forward");
      forward();  // move towards target
  }
  else // no object detected, stop motors, go into search state
  {
    rotateLoop.reset();
    translateLoop.reset();
    speedLeft=0;
    speedRight=0;
    index = -1; // set search state
  }

}
