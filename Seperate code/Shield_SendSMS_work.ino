//#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
//SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  
  //Begin serial communication with Arduino and SIM900
  Serial3.begin(115200);

  Serial.println("Initializing..."); 
  delay(1000);
  Serial.println("Done.");


}

void loop()
{
  delay(1000);
  Serial3.println("AT"); //Handshaking with SIM900
  updateSerial();

  Serial3.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial3.println("AT+CMGS=\"0988906420\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  Serial3.print("Last Minute Engineers"); //text content
  updateSerial();
  Serial3.write(26);
  Serial.println("Sent.");
  delay(10000);
  
}

void updateSerial()
{
  delay(1500);
  while (Serial.available()) 
  {
    Serial3.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial3.available()) 
  {
    Serial.write(Serial3.read());//Forward what Software Serial received to Serial Port
  }
}
