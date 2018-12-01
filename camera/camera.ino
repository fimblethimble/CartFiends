// ME366J CartFiends
//
// Initialize variables, functions, libraries here
//folder copy to compile and run
// #define and #include
    #include <Pixy2.h>        // Pixy2 Libraries
    Pixy2 pixy;
// Pixy Setup
  //set up distance variables
    #define calDistance 24 //in inches 24inches or 2 foot
  //NOTE: run the calibrate program to get distance coef. for different objects
    int signature = 0; // stores color signature
    int calWidth = 66; //Calibrated width reading
    int calHeight = 64; //Calibrated height reading
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
  long distance1;
  long distance2;
  long distance3;
  long distance4;
  long distance5;
  int speedA;
  int speedB;
// end declarations
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
    Serial.begin(9600); // start 115200baud communication for camera?
    Serial.print("Begin Serial Monitor\n");
  // initialize pixycam
    pixy.init();
    //pixy.changeProg("color_connected_components"); // select CCC pixycam program
    //calculate focal length
    focalLengthWidth = (calWidth * calDistance) / widthOfObject;
    focalLengthHeight = (calHeight * calDistance) / heightOfObject;
}
//
// NOTE: functions will be listed first, then main method calls them at the end
//
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
        //Serial.print("x pos: ");
        //Serial.print(xPosition);
        //Serial.print(" - ");
        //Serial.print("xCenter: ");
        //Serial.println(xCenter);
        //Serial.print(" - ");
       //
        /*
        Serial.print("xDifference: ");
        Serial.println(xDifference);
        Serial.print("Average: ");
        Serial.print(avg);
        Serial.println("in. ");
        */
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
          if (avg < 25)
          {
            // if object is closer than minimum follow distance, STOP
            Serial.println("Stop");
          }
          else
          {
          //
          // The first two IF statements cover the forward driving case.
          //
          if (xDifference<=0 && xDifference> -50)
          {
            // if the x offset is between 0 & -50, scale one PWM speed down
            speedA=2000-(12*xDifferenceABS);  // left wheel slower than right
            speedB=2000;
            Serial.println("forward/left");
          }
          if (xDifference>=0 && xDifference< 50)
          {
            // if the x offset is between 0 & 50, scale one PWM speed down
            speedA=2000;
            speedB=2000-(12*xDifferenceABS); //right wheel slower than left
            Serial.println("forward/right");
          }
          //
          // The next two IF statements set the speed for left/right turning
          //
          if (xDifferenceABS>=50 && xDifferenceABS<100)
          {
            // if the x offset is between 50 and 100, set speed to 70%
            speedA=1700;
            speedB=1700;
          }
          if (xDifferenceABS>=100 && xDifferenceABS<160)
          {
            // if the x offset is between 100 and 160 (max), set speed to 100%
            speedA=2000;
            speedB=2000;
          }
          //
          // The next two IF statements cover right or left turns
          //
          if (xDifference >=0 && abs(xDifference)>=50)
          {
            // if object is on right half of frame
            Serial.println("Right");
          }
          if (xDifference <=0 && abs(xDifference)>=50)
          {
            // if object is on left half of frame
            Serial.println("Left");
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
    // end processing of block
}
