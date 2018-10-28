// ME366J CartFiends
// Camera demo
//
// Goal is to read color codes and output their location + drive signal
// CC1=Green
// CC2=Blue
// CC3=Pink
//
#include <Pixy2.h>
#include <PIDLoop.h>
// Limit max velocity to highest PWM Value
#define MAX_TRANSLATE_VELOCITY 255
// min velocity may need to be 90 or 100 to avoid stalling.
#define MIN_VELOCITY 80
//
Pixy2 pixy;
// Define PIDLoops (Kp,Ki,Kd,boolean)
PIDLoop panLoop(350, 0, 600, true);
PIDLoop tiltLoop(500, 0, 700, true);         // why are these true
PIDLoop rotateLoop(300, 600, 300, false);
PIDLoop translateLoop(400, 800, 300, false); // why are these false
// define motor speeds
int speedLeft=0;
int speedRight=0;
//
void setup()
{
  Serial.begin(115200);
  Serial.print("Begin Serial Monitor\n");
  // initialize motor objects
  //
  // initialize pixy object
  pixy.init();
  pixy.changeProg("color_connected_components"); // run CCC on pixycam
}
// Find largest block (index 0 = largest) at least .5s old (30 frames)
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
    block->print();
    Serial.println(speedLeft);
    Serial.println(speedRight);
    if (speedLeft>speedRight)
      Serial.println("Turn right");
    if (speedRight>speedLeft)
      Serial.println("Turn left");
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
