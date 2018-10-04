//Initialize variables here

//NOTE: comment+int are from DigitalReadSerial example code
// Reads a digital input on pin 2, prints the result to the Serial Monitor
// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
// not sure why this is here instead of in setup()

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) // start 9600 bits/s serial communication
                     // only needed for monitoring from pc?
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  // initialize digital pin LED_BUILTIN as an output.
  // built in pin found on specs https://www.arduino.cc/en/Main/Products
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
// NOTE: example analog read code
  // read the input on analog pin 0:
   int sensorValue = analogRead(A0);
   // print out the value you read:
   Serial.println(sensorValue);
// NOTE: example digital read code
   // read the input pin:
   int buttonState = digitalRead(pushButton);
   // print out the state of the button:
   Serial.println(buttonState);
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(1);        // delay in between reads for stability
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

}


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}
