#include <Pixy2.h>

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

Pixy2 pixy;

void setup()
{
  Serial.begin(9600); // 9600 baud for the serial *console* (not for the UART connected to Pixy)
  Serial.print("Starting...\n");

  pixy.init();
  //calculate focal length
  focalLengthWidth = (calWidth * calDistance) / widthOfObject;
  focalLengthHeight = (calHeight * calDistance) / heightOfObject;

}

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
        xPosition = pixy.ccc.blocks[i].m_x;
        yPosition = pixy.ccc.blocks[i].m_y;
        distanceWidth = (widthOfObject * focalLengthWidth) / pixelsWidth;
        distanceHeight = (heightOfObject * focalLengthHeight) / pixelsHeight;
        avg = (distanceWidth + distanceHeight)/2;
        avg = round(avg);
        feet = avg/12;
        inches = int(avg) % 12;
        xDifference = (xPosition-xCenter);

        if (xDifference >=0 && abs(xDifference)>=20) // if object is on right half of frame
        {
          turnRight();
        }
        if (xDifference <=0 && abs(xDifference)>=20) // if object is on right half of frame
        {
          turnLeft();
        }
        if (xDifference<20) // if object is on right half of frame
        {
          driveForward();
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
        Serial.print("in. ");

       }
     }
    }
