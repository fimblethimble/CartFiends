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
// End Definitions
void setup()
{

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
  // begin serial comms
    Serial.begin(9600);
}
void loop()
{
  // Procedure: Clear trigpins, write low, delay 2us, write high
  // delay 10us, write low. Read echopin as duration "high"
  //
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
  // Calculating the distance (inches)
    distance1 = duration1*0.393701*0.034/2;
    distance2 = duration2*0.393701*0.034/2;
    distance3 = duration3*0.393701*0.034/2;
    distance4 = duration4*0.393701*0.034/2;
    distance5 = duration5*0.393701*0.034/2;
// Prints the distance on the Serial Monitor
    Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.println(" in.");
    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.println(" in.");
    Serial.print("Distance 3: ");
    Serial.print(distance3);
    Serial.println(" in.");
    Serial.print("Distance 4: ");
    Serial.print(distance4);
    Serial.println(" in.");
    Serial.print("Distance 5: ");
    Serial.print(distance5);
    Serial.println(" in.");
    Serial.println("------------------");
}
