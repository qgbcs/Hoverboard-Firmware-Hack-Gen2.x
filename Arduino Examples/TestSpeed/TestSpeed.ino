//    Tested with Arduino Pro Mini 3.3V and Hoverboard-TX to pin 9 and Hoverboard-RX to pin 8
//
//    PB6 (Hoverboard-TX) and PB7 (Hoverboard-RX) can handle 5V I/O-Level :-)
//
//    please share feedback to https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x


#define _DEBUG      // debug output to first hardware serial port
//#define DEBUG_RX    // additional hoverboard-rx debug output

#include "util.h"
#include "hoverserial.h"

#include <SoftwareSerial.h>
SoftwareSerial oSerialHover(9,8); // RX, TX 
//#define oSerialHover Serial     // Arduino, see PPMDevice.ino for help
//#define oSerialHover Serial1    // ESP32

SerialHover2Server oHoverFeedback;

void setup()
{
  #ifdef _DEBUG
    Serial.begin(115200);
    Serial.println("Hello Hoverbaord V2.x :-)");
  #endif
  
  HoverSetupArduino(oSerialHover,19200);    //  8 Mhz Arduino Mini too slow for 115200 !!!

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long iLast = 0;
void loop()
{
  unsigned long iNow = millis();
  digitalWrite(LED_BUILTIN, (iNow%2000) < 500);

  int iSpeed = 3 * (ABS( (int)((iNow/20+200) % 400) - 200) - 100);   // repeats from +300 to -300 to +300 :-)
  int iSteer = 0;
  
  if (Receive(oSerialHover,oHoverFeedback))   // Reply only when you receive data
  {
    DEBUGT("millis",iNow-iLast);
    HoverLog(oHoverFeedback);
    
    HoverSend(oSerialHover,iSteer,iSpeed);
    iLast = iNow;
  }
}
