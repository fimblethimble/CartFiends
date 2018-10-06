//Initialize variables and functions here

void setup() {
  // put your SETUP CODE HERE, to run ONCE:
  Serial.begin(9600) // start 9600 bits/s serial communication
                     // Needed for monitoring on computer
  // ***BEGIN GPS SETUP***
  // You can adjust which sentences to have the module emit, below
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data for high update rates!
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // uncomment this line to turn on all the available data - for 9600 baud you'll want 1 Hz rate
    //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  // Set the update rate
  // 1 Hz update rate
    //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  // 5 Hz update rate- for 9600 baud you'll have to set the output to RMC or RMCGGA only (see above)
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
  // 10 Hz update rate - for 9600 baud you'll have to set the output to RMC only (see above)
    //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
  // ***END GPS SETUP***
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
// put your MAIN CODE HERE, to run REPEATEDLY:

// read gps, optimally once every ms in an interrupt
  GPS.read()
  if(GPS.newNMEAreceived()==true){ //parse new data every loop
    GPS.parse(GPSlastNMEA())
    //Available data from parsed NMEA:
      //GPS.day, GPS.month, GPS.year
      //GPS.fix (1=fix, 0=no fix)
      //IF fix = 1, we can ask:
        //GPS.latitude, GPS.longitude, GPS.speed (knots)
        //GPS.angle, GPS.altitude (cm), GPS.sattelites (if ALLDATA enabled)
  }
//SECOND GOAL: Send parsed data to primary arduino
  //code to follow. Will change depending on if we use TI transceiver or ASK RF transceiver
}
