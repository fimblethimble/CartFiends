// ME366J CartFiends
//
// Initialize variables, functions, libraries here
//folder copy to compile and run
// #define and #include
    #include <PIDLoop.h>      // NewPing Library to read ultrasonic sensors
    #include <Pixy2.h>        // Pixy2 Libraries
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
// Pixy Setup
  // PINK = SIGNATURE 1  (NOT CC1)
  // GREEN = SIGNATURE 2 (NOT CC2)
  //set up distance variables
    #define calDistance 24 //in inches 24inches or 2 foot
  //NOTE: run the calibrate program to get distance coef. for different objects
    int signature = 0; // stores color signature
    int calWidth = 66; //Calibrated width reading
    int calHeight = 62; //Calibrated height reading
    int pixelsWidth;   //read by the camera
    int pixelsHeight; //read by the camera
    int xPosition;    //read by camera
    int yPosition;    //read by camera
    float distanceWidth;   //calculated distance based on the width of the object
    float distanceHeight;  //calculated distance based on the height of the object
    float widthOfObject = 5.5; //inches (3.75 inches) real size of your object
    float heightOfObject = 5.4; //inches (2.5 inches) real size of your object
    int focalLengthWidth;  //calculated focal length for width
    int focalLengthHeight; //calculated focal length for height
    int xDifference; //difference between xpos and center
    int xDifferenceABS; // abs(xDifference)
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
  Pixy2 pixy;
// Ultrasonic Setup
    // Sensor 1: Front facing, left side
    const int  echo1=30;
    const int  trig1=31;
    long duration1=0;
    long distance1=0;
    // Sensor 2: Left facing
    const int  echo2=32;
    const int  trig2=33;
    long duration2=0;
    long distance2=0;
    // Sensor 3: Front facing, right side
    const int  echo3=34;
    const int  trig3=35;
    long duration3=0;
    long distance3=0;
    // Sensor 4: Right facing
    const int  echo4=36;
    const int  trig4=37;
    long duration4=0;
    long distance4=0;
    // Sensor 5: Rear facing, center
    const int  echo5=38;
    const int  trig5=39;
    long duration5=0;
    long distance5=0;
// Speaker setup
    int piezoPin=4;
// end declarations
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
    Serial.begin(9600); // start 115200baud communication for camera?
    Serial.print("Begin Serial Monitor\n");
  // set all the motor control pins to outputs
    left.attach(signal1,1000,2000);   // (pin,min,max)
    left.writeMicroseconds(1000);
    right.attach(signal2,1000,2000);  // (pin,min,max)
    right.writeMicroseconds(1000);
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
  // Read Sensor 1
    digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    duration1 = pulseIn(echo1, HIGH);
  // Read Sensor 2
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    duration2 = pulseIn(echo2, HIGH);
 // Read Sensor 3
    digitalWrite(trig3, LOW);
    delayMicroseconds(2);
    digitalWrite(trig3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3, LOW);
    duration3 = pulseIn(echo3, HIGH);
 // Read Sensor 4
    digitalWrite(trig4, LOW);
    delayMicroseconds(2);
    digitalWrite(trig4, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig4, LOW);
    duration4 = pulseIn(echo4, HIGH);
 // Read Sensor 5
    digitalWrite(trig5, LOW);
    delayMicroseconds(2);
    digitalWrite(trig5, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig5, LOW);
    duration5 = pulseIn(echo5, HIGH);
  // Calculate the distance (inches)
    distance1 = duration1*0.393701*0.034/2;
    distance2 = duration2*0.393701*0.034/2;
    distance3 = duration3*0.393701*0.034/2;
    distance4 = duration4*0.393701*0.034/2;
    distance5 = duration5*0.393701*0.034/2;
}
void driveForward(int speedA, int speedB)
{
// this function will run the motors in one direction at a fixed speed
    left.writeMicroseconds(speedA);
    right.writeMicroseconds(speedB);
}
//
void turnLeft(int speedA, int speedB) // NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  left.writeMicroseconds(speedA);
  right.writeMicroseconds(speedB);
}
//
void turnRight(int speedA, int speedB) //NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  left.writeMicroseconds(speedA);
  right.writeMicroseconds(speedB);
}
void driveStop() //turns off all motors
{
  left.writeMicroseconds(1000);
  right.writeMicroseconds(1000);
}
//----CAMERA SUBFUNCTIONS----//
int16_t acquireBlock()
{
  // Find largest block (index 0 = largest) at least .25s old (15 frames)
  // Return block index, if no block return -1.
  // "Locks on" to object
    if (pixy.ccc.numBlocks && pixy.ccc.blocks[0].m_age>15)
      return pixy.ccc.blocks[0].m_index;

    return -1;
}
// Find block with the index detailed in int16_t acquireBlock()
// within the current frame. If block not found, return NULL
Block *trackBlock(uint8_t index)
{
    uint8_t i;
  //Using acquireBlock(), find block that matches the index and return it.
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      if (index==pixy.ccc.blocks[i].m_index)
        return &pixy.ccc.blocks[i];
    }
  // if it doesn't match, do nothing.
    return NULL;
}
//--END CAMERA SUBFUNCTIONS--//
void loop() // need a "no object found" case
{
  // At every loop, check proximity sensors first. (~100 microsec)
    ultrasonic();
    if (distance1<5 || distance2<5 || distance3<5 || distance4<5)
    {
      tone(piezoPin,1500,200); // tone (pin,frequency,ms duration)
      delay(400);
      tone(piezoPin,1500,200); // tone (pin,frequency,ms duration)
      delay(400);
      tone(piezoPin,1500,200); // tone (pin,frequency,ms duration)
      delay(400);
    }
    if (distance1<15)
    {
      // if front facing left side covered, turn right
      turnRight(1600,1200);
      delay(1000);
      Serial.println("US TURN RIGHT");
    }
    if (distance3<15)
    {
      // if front facing right side covered, turn left
      turnLeft(1200,1600);
      delay(1000);
      Serial.println("US TURN LEFT");
    }
  // Initialize values for blocks array
    static int i = 0;
    int j;
    uint16_t blocks;
    char buf[32];
  // Search for blocks:
    blocks = pixy.ccc.getBlocks();
    if (blocks)
    {
    i++;
  // IF there is a block added to array, run the following:
  // 1) Every FIVE frames, print block data. Previously 50.
  // NOTE: need to verify if this i = frames or # of blocks
  // or if it is the age of the object
    if (i%50==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
    }
  // 2) For each block detected, return data and send control signals
    for (j=0; j<blocks; j++)
    {
    // Maybe print the J index here to tell if its processing multiple objs.
      // sprintf(buf, "  block %d: ", j);
      // Serial.print(buf);
      // Calculate positional data
        signature = pixy.ccc.blocks[j].m_signature; // get color sig as int(?)
        pixelsWidth = pixy.ccc.blocks[j].m_width;
        pixelsHeight = pixy.ccc.blocks[j].m_height;
        xPosition = pixy.ccc.blocks[j].m_x;
        yPosition = pixy.ccc.blocks[j].m_y;
        xDifference = (xPosition-xCenter);
        xDifferenceABS = abs(xDifference);
        distanceWidth = (widthOfObject * focalLengthWidth) / pixelsWidth;
        distanceHeight = (heightOfObject * focalLengthHeight) / pixelsHeight;
        avg = (distanceWidth + distanceHeight)/2; //
        avg = round(avg);
        feet = avg/12;          //integer no. feet
        inches = int(avg) % 12; //inches remaining (eg 5' 3")
    // Print x positional data
/*
        Serial.print("x pos: ");
        Serial.print(xPosition);
        Serial.print(" - ");
        Serial.print("xCenter: ");
        Serial.println(xCenter);
        Serial.print(" - ");
        Serial.print("xDifference: ");
        Serial.println(xDifference);
*/
        //Serial.print("Signature: ");
        //Serial.println(signature);
        //Serial.print("Average: ");
        //Serial.print(avg);
        //Serial.println("in. ");

    // Navigation and Control Signals here
      // Based on magnitude of X offset, set motor speed.
        /*
        if (abs(xDifference)<50 && avg >= 22) // if object in center region
        {
          driveForward();
          Serial.println("Forward");
        }
        */
          // if ultrasonic sensors show clear immediately ahead,
          // check the camera distance to object
          if (signature == 7)
          {
            driveStop();
            Serial.println("STOP, ALARM");
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
            tone(piezoPin,4000,200); // tone (pin,frequency,ms duration)
            delay(400);
          }
          else if (avg < 33)
          {
            // if object is closer than minimum follow distance, STOP
            driveStop();
            Serial.println("Stop");
          }
          else
          {
          //
          // The first two IF statements cover the forward driving case.
          //
          if (xDifference<=40 && xDifference> -140)
          {
            // if the x offset is between 0 & -50, scale one PWM speed down
            speedA=1200;  // left wheel slower than right
            speedB=1650;
            Serial.println("forward/left");
            driveForward(speedA,speedB);
            delay(50);
          }
          if (xDifference >= -40 && xDifference <= 40)
          {
            speedA=1600;
            speedB=1650;
            driveForward(speedA,speedB);
            Serial.println("forward");
            delay(50);
          }
          if (xDifference>40 && xDifference< 140)
          {
            // if the x offset is between 0 & 50, scale one PWM speed down
            speedA=1600;
            speedB=1250; //right wheel slower than left
            driveForward(speedA,speedB);
            Serial.println("forward/right");
            delay(50);
          }
          // The next two IF statements cover right or left turns
          //
          if (xDifference > 0 && abs(xDifference) >=140)
          {
            // if object is on right half of frame
            turnRight(1600,1200);
            Serial.println("Right");
            delay(500);
            driveStop();
          }
          if (xDifference < 0 && abs(xDifference) >= 140)
          {
            // if object is on left half of frame
            turnLeft(1200,1600);
            Serial.println("Left");
            delay(500);
            driveStop();
          }
        }
          //end control processing
        //Serial.print("Width: ");
        //Serial.print(pixelsWidth);
        //Serial.print(" Height: ");
        //Serial.print(pixelsHeight);
        //Serial.print(" Distance W: ");
        //Serial.print(distanceWidth);
        //Serial.print("in. ");
        //Serial.print("Distance H: ");
        //Serial.print(distanceHeight);
        Serial.println("-----------------");
    }
    }
    else driveStop();// end processing of block
}
