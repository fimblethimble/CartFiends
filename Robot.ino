// Initialize variables, functions, libraries here
  //folder copy to compile and run
// #define and #include
  #include <PIDLoop.h>      // NewPing Library to read ultrasonic sensors
  #include <Pixy2.h>        // Pixy2 Libraries
// Motor Setup
  // MAKE SURE THE INPUTS ARE WIRED TO THESE PINS
      // Motor1
  #define in1 22 // HbridgeA 1
  #define in2 23  // HbridgeA 2
  #define enA 2  // PWM1
      // Motor2
  #define in3 24  // HbridgeB 1
  #define in4 25  // HbridgeB 2
  #define enB 3  // PWM2
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
  //set up distance variables
  #define calDistance 24 //in inches 24inches or 2 foot
  int calWidth = 33; //Calibrated width reading
  int calHeight = 33; //Calibrated height reading
  int pixelsWidth;   //read by the camera
  int pixelsHeight; //read by the camera
  int xPosition;    //read by camera
  int yPosition;    //read by camera
  float distanceWidth;   //calculated distance based on the width of the object
  float distanceHeight;  //calculated distance based on the height of the object
  float widthOfObject = 3.0; //inches (3.75 inches) real size of your object
  float heightOfObject = 3.0; //inches (2.5 inches) real size of your object
  int focalLengthWidth;  //calculated focal length for width
  int focalLengthHeight; //calculated focal length for height
  int xDifference; //difference between xpos and center
  float avg;
  int feet;
  int inches;
  int xCenter = 157;
  int yCenter = 103;
  //Formula = FocalLengthWidth = (pixels * knowdistanceininches) / widthOfObject
  //Distance = (widthOfObject * FocalLengthWidth) / pixelsWidth
  //focal length and distance for height is calculated the same way replacing width with height values
// Pixy notes
  // CC1=Green
  // CC2=Blue
  // CC3=Pink
// Ultrasonic Setup
  const int  echo1=26;
  const int  trig1=27;
  int  duration1=0;
  int  distance1=0;
  const int  echo2=28;
  const int  trig2=29;
  int  duration2=0;
  int  distance2=0;
  const int  echo3=30;
  const int  trig3=31;
  int  duration3=0;
  int  distance3=0;
  const int  echo4=32;
  const int  trig4=33;
  int  duration4=0;
  int  distance4=0;
  const int  echo5=34;
  const int  trig5=35;
  int  duration5=0;
  int  distance5=0;
  long duration;
  long distance;
// end declarations
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
    Serial.begin(9600); // start 115200baud communication for camera
    Serial.print("Begin Serial Monitor\n");
  // set all the motor control pins to outputs
    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
  // initialize pixycam
    pixy.init();
    //pixy.changeProg("color_connected_components"); // select CCC pixycam program
    //calculate focal length
    focalLengthWidth = (calWidth * calDistance) / widthOfObject;
    focalLengthHeight = (calHeight * calDistance) / heightOfObject;
  // set ultrasonic pins to input/output
    pinMode(trig1,OUTPUT);
    pinMode(echo1,INPUT);
    pinMode(trig2,OUTPUT);
    pinMode(echo2,INPUT);
    pinMode(trig3,OUTPUT);
    pinMode(echo3,INPUT);
    pinMode(trig4,OUTPUT);
    pinMode(echo4,INPUT);
    pinMode(trig5,OUTPUT);
    pinMode(echo5,INPUT);
}
//
// NOTE: functions will be listed first, then main method calls them at the end
//
void ultrasonic()
{
  // Clears the trigPins
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
    delayMicroseconds(2);
  // Sets the trigPins on HIGH state for 10 micro seconds
    digitalWrite(trig1, HIGH);
    digitalWrite(trig2, HIGH);
    digitalWrite(trig3, HIGH);
    digitalWrite(trig4, HIGH);
    digitalWrite(trig5, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
  // Reads the echoPins, returns the sound wave travel time in microseconds
    duration1 = pulseIn(echo1, HIGH);
    duration2 = pulseIn(echo2, HIGH);
    duration3 = pulseIn(echo3, HIGH);
    duration4 = pulseIn(echo4, HIGH);
    duration5 = pulseIn(echo5, HIGH);
  // Calculating the distance
    distance1 = duration1*0.034/2;
    distance2 = duration2*0.034/2;
    distance3 = duration3*0.034/2;
    distance4 = duration4*0.034/2;
    distance5 = duration5*0.034/2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance1: ");
    //Serial.println(distance1);
}
void driveForward()
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
void driveReverse()
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
  delay(500); //NOTE: Delay = motor runtime
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
//
void turnLeft() // NOTE: NEED TO TEST MOTOR DIRECTION
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
void turnRight() //NOTE: NEED TO TEST MOTOR DIRECTION
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
void driveStop() //turns off all motors
{
  // turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
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
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];

blocks = pixy.ccc.getBlocks();

  if (blocks)
    {
    i++;

   // do this (print) every 50 frames because printing every
   // frame would bog down the Arduino
   if (i%50==0)
    {

      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
          }
      for (j=0; j<blocks; j++)
      {
        //sprintf(buf, "  block %d: ", j);
        //Serial.print(buf);
        pixelsWidth = pixy.ccc.blocks[j].m_width;
        pixelsHeight = pixy.ccc.blocks[j].m_height;
        xPosition = pixy.ccc.blocks[j].m_x;
        yPosition = pixy.ccc.blocks[j].m_y;
        distanceWidth = (widthOfObject * focalLengthWidth) / pixelsWidth;
        distanceHeight = (heightOfObject * focalLengthHeight) / pixelsHeight;
        avg = (distanceWidth + distanceHeight)/2;
        avg = round(avg);
        feet = avg/12;
        inches = int(avg) % 12;
        Serial.print("x pos: ");
        Serial.print(xPosition);
        Serial.print(" - ");
        Serial.print("xCenter: ");
        Serial.println(xCenter);
        xDifference = (xPosition-xCenter);
        Serial.println(xDifference);
        if (xDifference >=0 && abs(xDifference)>=50) // if object is on right half of frame
        {
          turnRight();
          Serial.println("Right");
        }
        if (xDifference <=0 && abs(xDifference)>=50) // if object is on right half of frame
        {
          turnLeft();
          Serial.println("Left");
        }
        if (abs(xDifference)<50 && avg >= 22) // if object is on right half of frame
        {
          driveForward();
          Serial.println("Forward");
        }
        if (avg < 22)
        {
          driveStop();
          driveReverse();
          Serial.println("Stop");
        }
        //Serial.print("Width: ");
        //Serial.print(pixelsWidth);
        //Serial.print(" Height: ");
        //Serial.print(pixelsHeight);
        //Serial.print(" Distance W: ");
        //Serial.print(distanceWidth);
        //Serial.print("in. ");
        //Serial.print("Distance H: ");
        //Serial.print(distanceHeight);
        Serial.print("Average: ");
        Serial.print(avg);
        Serial.println("in. ");
        Serial.println("-----------------");
       }
     }
}
