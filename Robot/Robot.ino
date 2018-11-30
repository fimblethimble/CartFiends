// ME366J CartFiends
//
// Initialize variables, functions, libraries here
//folder copy to compile and run
// #define and #include
    #include <PIDLoop.h>      // NewPing Library to read ultrasonic sensors
    #include <Pixy2.h>        // Pixy2 Libraries
// Motor Setup
    int pwmA = 0;
    int pwmB = 0;
  // There are two motor drivers connected to each motor, with 3 inputs each.
    // Motor1
    #define in1 22  // HbridgeA 1 (A1)
    #define in2 23  // HbridgeA 2 (A1)
    #define in3 24  // HbridgeA 3 (A2)
    #define in4 25  // HbridgeA 4 (A2)
    #define enA1 2   // PWM: A1
    #define enA2 3   // PWM: A2
    // Motor2
    #define in5 26  // HbridgeB 1 (B1)
    #define in6 27  // HbridgeB 2 (B1)
    #define in7 28  // HbridgeB 3 (B2)
    #define in8 29  // HbridgeB 4 (B2)
    #define enB1 4   // PWM: B1
    #define enB2 5   // PWM: B2
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
  //NOTE: run the calibrate program to get distance coef. for different objects
    int signature = 0; // stores color signature
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
// end declarations
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
    Serial.begin(9600); // start 115200baud communication for camera?
    Serial.print("Begin Serial Monitor\n");
  // set all the motor control pins to outputs
    pinMode(enA1,OUTPUT);
    pinMode(enA2,OUTPUT);
    pinMode(enB1,OUTPUT);
    pinMode(enB2,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(in5,OUTPUT);
    pinMode(in6,OUTPUT);
    pinMode(in7,OUTPUT);
    pinMode(in8,OUTPUT;)
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
void driveForward(pwmA, pwmB)
{
// this function will run the motors in one direction at a fixed speed
  // turn on motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  // set motor speed (PWM)
    analogWrite(enA1, pwmA);
    analogWrite(enA2, pwmA);
  // turn on motor B
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB1, pwmB);
    analogWrite(enB2, pwmB);
  // hold motor at these speeds for at least delay() time.
  // if no other control signals sent, motor will maintain speed.
    delay(250); //NOTE: Delay = motor runtime
//NOTE: if motor control presents issues, include stop command.
}
//
void driveReverse()
{
  // this function will run the motors in one direction at a fixed speed
  // turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  // set motor speed (PWM)
    analogWrite(enA1, 255);
    analogWrite(enA2, 255);
  // turn on motor B
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  // set motor speed (PWM)
    analogWrite(enB1, 255);
    analogWrite(enB2, 255);
  // hold motor at these speeds for at least delay() time.
  // if no other control signals sent, motor will maintain speed.
    delay(250); //NOTE: Delay = motor runtime
}
//
void turnLeft(pwmA, pwmB) // NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  // set motor speed (PWM)
    analogWrite(enA1, pwmA);
    analogWrite(enA2, pwmA);
  // turn on motor B
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB1, pwmB);
    analogWrite(enB2, pwmB);
  // hold motor at these speeds for at least delay() time.
  // if no other control signals sent, motor will maintain speed.
    delay(250); //NOTE: Delay = motor runtime
}
//
void turnRight(pwmA, pwmB) //NOTE: NEED TO TEST MOTOR DIRECTION
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  // set motor speed (PWM)
    analogWrite(enA1, pwmA);
    analogWrite(enA2, pwmA);
  // turn on motor B
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB1, pwmB);
    analogWrite(enB2, pwmB);
  // hold motor at these speeds for at least delay() time.
  // if no other control signals sent, motor will maintain speed.
    delay(250); //NOTE: Delay = motor runtime
}
void driveStop() //turns off all motors
{
  // turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
  // Maintain "STOP" for at least delat() time.
    delay(250);
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
  // At every loop, check proximity sensors first. (~20 microsec)
    ultrasonic();
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
    if (i%5==0)
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
        avg = (distanceWidth + distanceHeight)/2; // ??
        avg = round(avg);
        feet = avg/12;          //integer no. feet
        inches = int(avg) % 12; //inches remaining (eg 5' 3")
    // Print x positional data
        Serial.print("x pos: ");
        Serial.print(xPosition);
        Serial.print(" - ");
        Serial.print("xCenter: ");
        Serial.println(xCenter);
        Serial.print(" - ");
        Serial.print("xDifference: ");
        Serial.println(xDifference);
    // Navigation and Control Signals here
      // Based on magnitude of X offset, set motor speed.
        /*
        if (abs(xDifference)<50 && avg >= 22) // if object in center region
        {
          driveForward();
          Serial.println("Forward");
        }
        */
        //
        // The first two IF statements cover the forward driving case.
        //
        if (xDifference)<=0 && xDifference> -50)
        {
          // if the x offset is between 0 & -50, scale one PWM speed down
          pwmA=255-(2*xDifferenceABS); // Right wheel slower than left
          pwmB=255;
          driveForward(pwmA,pwmB);
          Serial.println("forward/right")
        }
        if (xDifference>=0 && xDifference< 50)
        {
          // if the x offset is between 0 & 50, scale one PWM speed down
          pwmA=255;
          pwmB=255-(2*abs(xDifference)); // Left wheel slower than right
          driveForward(pwmA,pwmB);
          Serial.println("forward/left")
        }
        //
        // The next two IF statements set the speed for left/right turning
        //
        if (xDifferenceABS>=50 && xDifferenceABS<100)
        {
          // if the x offset is between 50 and 100, set speed slower
          pwmA=150;
          pwmB=150;
        }
        if (xDifferenceABS>=100 && xDifferenceABS<160)
        {
          // if the x offset is between 100 and 160 (max), set speed to max
          pwmA=255;
          pwmB=255;
        }
        //
        // The next two IF statements cover right or left turns
        //
        if (xDifference >=0 && abs(xDifference)>=50)
        {
          // if object is on right half of frame
          turnRight(pwmA,pwmB);
          Serial.println("Right");
        }
        if (xDifference <=0 && abs(xDifference)>=50)
        {
          // if object is on right half of frame
          turnLeft(pwmA,pwmB);
          Serial.println("Left");
        }
        //
        // The following IF statement stops the motors
        //
        if (avg < 22)
        {
          // if object is closer than minimum follow distance, STOP
          driveStop();
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
    } // end processing of block
}
