#include <Pixy2.h>

#define Calibrate 1
#define calDistance 24 //24 inch calibration distance

int calWidth = 40; //Calibrated width reading
int calHeight = 29; //Calibrated height reading
int pixelsWidth;   //read by the camera
int pixelsHeight; //read by the camera
float distanceWidth;   //calculated distance based on the width of the object
float distanceHeight;  //calculated distance based on the height of the object 
float widthOfObject = 3.0; //inches (3.75 inches) real size of your object
float heightOfObject = 3.0; //inches (2.5 inches) real size of your object
int focalLengthWidth;  //calculated focal length for width
int focalLengthHeight; //calculated focal length for height
float avg;
int feet;
int inches;

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

void loop() {

  static int i = 0;
  int j;
  uint16_t blocks=NULL;
  char buf[32]; 

  blocks = pixy.ccc.getBlocks();

  if (blocks)
    {
    i++;
    
   // do this (print) every 50 frames because printing every
   // frame would bog down the Arduino
   if (i%50==0)
    {

      if (Calibrate) {
          sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf); 
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.ccc.blocks[j].print();
      }
    }
    }
}
}
