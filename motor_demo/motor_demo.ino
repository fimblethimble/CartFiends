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
//
void setup()
{
  // put your SETUP CODE HERE, to run ONCE:
  Serial.begin(9600); // start 115200bt/s communication for NewPing & cam
  // set all the motor control pins to outputs
  pinMode(enA1,OUTPUT);
  pinMode(enA2,OUTPUT);
  pinMode(enB1, OUTPUT);
  pinMode(enB2, OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}
//
// NOTE: functions will be listed first, then main method calls them at the end
//
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
//
void loop() // main method to call the rest
{
  int pwmA = 150;
  int pwmB = 150;
  forward(pwmA,pwmB);
  driveStop();
  delay(750);
  reverse(pwmA,pwmB);
  driveStop();
  delay(750);
}
