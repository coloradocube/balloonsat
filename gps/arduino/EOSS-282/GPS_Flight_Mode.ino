

/*
GPS Level Convertor Board Test Script
03/05/2012 2E0UPU

Connects the GPS via Software Serial.
Initialise the GPS Module in Flight Mode and then
echo's the NMEA Data to the Arduino's Serial port.

This example code is in the public domain.
Additional Code by J Coxon (http://ukhas.org.uk/guides:falcom_fsa03)
*/

void FlightMode() { 
   GPSSerial.begin(9600);
   // START OUR SERIAL DEBUG PORT
   Serial.begin(9600);
   Serial.println("GPS Level Convertor Board Test Script");
   Serial.println("03/06/2012 2E0UPU");
   Serial.println("Initializing....");
   //
   // THE FOLLOWING COMMAND SWITCHES MODULE TO 4800 BAUD
   // THEN SWITCHES THE SOFTWARE SERIAL TO 4,800 BAUD
   //
   GPSSerial.print("$PUBX,41,1,0007,0003,9600,0*13\r\n");
   GPSSerial.begin(9600);
   GPSSerial.flush();
  
   //  THIS COMMAND SETS FLIGHT MODE AND CONFIRMS IT
   Serial.println("Setting uBlox nav mode: ");
   uint8_t setNav[] = {
                   0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06,
                   0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00,
                   0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 
                   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xDC };
   while(!gps_set_sucess)
   {
     sendUBX(setNav, sizeof(setNav)/sizeof(uint8_t));
     gps_set_sucess=getUBX_ACK(setNav);

   }
   gps_set_sucess=0;
  
   // THE FOLLOWING COMMANDS DO WHAT THE $PUBX ONES DO BUT WITH CONFIRMATION
   // UNCOMMENT AS NEEDED
   /*
   Serial.println("Switching off NMEA GLL: ");
    uint8_t setGLL[] = {
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B                   };
    while(!gps_set_sucess)
    {
    sendUBX(setGLL, sizeof(setGLL)/sizeof(uint8_t));
    gps_set_sucess=getUBX_ACK(setGLL);
    }
    gps_set_sucess=0;
    Serial.println("Switching off NMEA GSA: ");
    uint8_t setGSA[] = {
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32                   };
    while(!gps_set_sucess)
    {
    sendUBX(setGSA, sizeof(setGSA)/sizeof(uint8_t));
    gps_set_sucess=getUBX_ACK(setGSA);
    }
    gps_set_sucess=0;
    Serial.println("Switching off NMEA GSV: ");
    uint8_t setGSV[] = {
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39                   };
    while(!gps_set_sucess)
    {
    sendUBX(setGSV, sizeof(setGSV)/sizeof(uint8_t));
    gps_set_sucess=getUBX_ACK(setGSV);
    }
    gps_set_sucess=0;
    Serial.print("Switching off NMEA RMC: ");
    uint8_t setRMC[] = {
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40                   };
    while(!gps_set_sucess)
    {
    sendUBX(setRMC, sizeof(setRMC)/sizeof(uint8_t));
    gps_set_sucess=getUBX_ACK(setRMC);
    }
    */
  
  }
  
  void loop2()
  {
   while(1)
   {
     if(GPSSerial.available())
     {
       // THIS IS THE MAIN LOOP JUST READS IN FROM THE GPS SERIAL AND ECHOS OUT TO THE ARDUINO SERIAL.
       Serial.write(GPSSerial.read());
     }
  
   }
  }  
  
  
  // Send a byte array of UBX protocol to the GPS
  void sendUBX(uint8_t *MSG, uint8_t len) {
   for(int i=0; i<len; i++) {
     GPSSerial.write(MSG[i]);
     Serial.print(MSG[i], HEX);
   }
   GPSSerial.println();
  }
  
  
  // Calculate expected UBX ACK packet and parse UBX response from GPS
  boolean getUBX_ACK(uint8_t *MSG) {
   uint8_t b;
   uint8_t ackByteID = 0;
   uint8_t ackPacket[10];
   unsigned long startTime = millis();
   Serial.print(" * Reading ACK response: ");
  
   // Construct the expected ACK packet    
   ackPacket[0] = 0xB5; // header
   ackPacket[1] = 0x62; // header
   ackPacket[2] = 0x05; // class
   ackPacket[3] = 0x01; // id
   ackPacket[4] = 0x02; // length
   ackPacket[5] = 0x00;
   ackPacket[6] = MSG[2]; // ACK class
   ackPacket[7] = MSG[3]; // ACK id
   ackPacket[8] = 0; // CK_A
   ackPacket[9] = 0; // CK_B
  
   // Calculate the checksums
   for (uint8_t i=2; i<8; i++) {
     ackPacket[8] = ackPacket[8] + ackPacket[i];
     ackPacket[9] = ackPacket[9] + ackPacket[8];
   }
  
   while (1) {
  
     // Test for success
     if (ackByteID > 9) {
       // All packets in order!
       Serial.println(" (SUCCESS!)");
       return true;
     }
  
     // Timeout if no valid response in 3 seconds
     if (millis() - startTime > 3000) {
       Serial.println(" (FAILED!)");
       return false;
     }
  
     // Make sure data is available to read
     if (GPSSerial.available()) {
       b = GPSSerial.read();
  
       // Check that bytes arrive in sequence as per expected ACK packet
       if (b == ackPacket[ackByteID]) {
         ackByteID++;
         Serial.print(b, HEX);
       }
       else {
         ackByteID = 0; // Reset and look again, invalid order
       }
  
     }
   }
  }  
