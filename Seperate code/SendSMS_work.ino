/* This part will just use the SIM7600 to send text message to the phone number written in the void loop() section.
The code here is re-adapted from tlfong01 blog post, the link is https://tlfong01.blog/2020/03/26/sim900-sim7600-notes/
In this iteration, the SMS message is continously sent to the phone number below (so beware of the cost incurred if you put it in a quick loop)

The board I use is Arduino Mega 2560, developed by DFRobot. And for some reasons, the plug RX-7 or TX-8 doesn't work, so I have to plug the RX and TX of the SIM to the TX3 
and RX3 on the Mega board, thus "Serial3"

On another note, visit the link to the blog post above. There are more than just "send SMS to a phone number"
*/

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
  Serial3.println("AT+CMGS=\"xxxxxxxxx\"");// Replace xxxxxxxxxxx with phone number to sms you don't need the +ZZ country code at the beginning, if you want to send in-country message
  updateSerial();
  Serial3.print("Last Minute Engineers"); //text content
  updateSerial();
  Serial3.write(26);
  Serial.println("Sent.");
  delay(10000); // A text is sent every 10s, much better than the 1s loop I forget at the beginning...
  
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
