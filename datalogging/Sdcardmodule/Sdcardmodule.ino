#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "RTClib.h"
int tON=0;
int tOFF=0;
int Tperiod=0;
int freq=0;
int RPM=0,Wcspin;
double speed;
double diameter;
File DataLog;
RTC_DS1307 rtc;

int pinCS=53;
void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  pinMode(Wcspin,OUTPUT);
  pinMode(pinCS,OUTPUT);
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  rtc.begin();
}

void loop() {
  DataLog= SD.open("Data.txt",FILE_WRITE);
  DateTime now = rtc.now();
  tON=pulseIn(Wcspin,HIGH);
  tOFF=pulseIn(Wcspin,LOW);
  Tperiod=tON + tOFF;
  freq= 1000000.0/ Tperiod;
  RPM=freq * 60;
  speed=(RPM*diameter*PI*60*1.60934)/(63360);
    
  // make a string for assembling the data to log:
  String dataString = "";
  dataString += String(now.year(), DEC);
  dataString += String('/');
  dataString += String(now.month(), DEC);
  dataString += String('/');
  dataString += String(now.day(), DEC);
  dataString += String(' ');
  dataString += String(now.hour(), DEC);
  dataString += String(':');
  dataString += String(now.minute(), DEC);
  dataString += String(':');
  dataString += String(now.second(), DEC);
  dataString += String(" Response: ");
  dataString += String(speed);
  dataString +=String("km/h");
   
  if(DataLog){
    DataLog.println(dataString);
    DataLog.close(); // close the file
  }
  // if the file didn't open, print an error:
  else 
  {
    Serial.println("error opening Data.txt");
  }
  delay(1000);

}
