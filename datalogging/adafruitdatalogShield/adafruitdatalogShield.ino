// Following sketch is a combination of code derived from Arduino IDE datalogger example sketch, and 
// code developed by Adafruit for use with its own datalogger shield. This code monitors response on a 
// hall effect  sensor and records the results to a datalogger hosing an SD card to include 
// time stamping of your data.

// The Arduino datalogger example sketch is available within the IDE under 
// File -> Examples - SD -> Datalogger and is attributed to Tom Igoe.

// Adafruit's code is available here:
// https://learn.adafruit.com/adafruit-data-logger-shield/using-the-real-time-clock-3
// (Thank you Adafruit!)

// Setting the time on the datalogging shield via the RTC is explained by Adafruit via this link:
// https://learn.adafruit.com/adafruit-data-logger-shield/using-the-real-time-clock

// This code is copied and simplified from the original sketches to work specifically with an Arduino UNO 
// or a clone. This simplified demonstration will not work with Leonardo or Mega

// Date and time functions are using a real time clock connected via I2C and Wire library

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.

const int chipSelect = 10; //specific to Arduino UNO

File dataFile;
int ledPin = 8; // pin for lighting LED when water is detected
int analogPin = 0; // pin attached to signal on "Funduino" water sensor

void setup()
{

 // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;    
  }
  Serial.println("card initialized.");
  
  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE); 
  // will create the file if it doesn't exist  
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we can't write data
    while (1) ;
  }

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); // Wait forever since we can't log timestamp
  }  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
    DateTime now = rtc.now();
    
  // make a string for assembling the data to log:
  String dataString = "";

  int sensor = analogRead(analogPin);

   dataString += String(now.year(), DEC);
   dataString += String('/');
   dataString += String(now.month(), DEC);
   dataString += String('/');
   dataString += String(now.day(), DEC);
   dataString += String(" (");
   dataString += String(daysOfTheWeek[now.dayOfTheWeek()]);
   dataString += String(") ");
   dataString += String(now.hour(), DEC);
   dataString += String(':');
   dataString += String(now.minute(), DEC);
   dataString += String(':');
   dataString += String(now.second(), DEC);
   dataString += String(" Response: ");
   
   dataString += String(sensor);

   if(sensor > 400) {
     digitalWrite(ledPin, HIGH);
     dataString += String(" : FLOW ON");
   } 
   else {
     digitalWrite(ledPin, LOW);
     dataString += String(" : FLOW OFF");
   }  
  
  dataFile.println(dataString);
  
  // The following line will 'save' the file to the SD card after every
  // line of data - this will use more power and slow down how much data
  // you can read but it's safer! 
  
  // If you want to speed up the system, remove the call to flush() and it
  // will save the file only every 512 bytes - every time a sector on the 
  // SD card is filled with data.
  
  dataFile.flush();

  // print our dataString to the serial port too:
  Serial.println(dataString);
  
  // Take 1 measurement every 2000 milliseconds
  delay(2000);
}

