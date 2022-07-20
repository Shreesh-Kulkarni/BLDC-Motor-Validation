    
#include "Voltage.h"
//#include "Gyro.h"
#include "Current.h"
#include "SD.h"
#include "RTC_Clock.h"

#include "RTClib.h"


#include <Wire.h>
#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
#include<SPI.h>
#include<SD.h>



//#define rxPin 0
//#define txPin 1
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
//const int  rs=7,en=6,d4=5,d5=4,d6=3,d7=2;


//SoftwareSerial BlueTooth(0,1);//rxPin, txPin); 
//LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//LiquidCrystal lcd(12,11,5,4,3,2);

int AnalogInput = A0;
float Voltage_Data;
//String Gyro_Data;
float Current_Data;
String Final_Data;
String Timer_Data;



Voltage V;
//Gyro G;
Current I;
SDCard SDC;
File DataLogger;
RTCCLock T;



void setup()
{
  Serial.begin(9600);
  //BlueTooth.begin(115200);
  pinMode(AnalogInput,INPUT);
 // G.GyroSetup();
  I.CurrentISetup();
  //lcd.begin(16,2);
  Serial.println("Voltage Current");
 // BlueTooth.println("Voltage Current");
  SDC.SDCardsetup();
  T.RTCsetup ();
  
  
}

void loop()
{


  Voltage_Data=V.VoltageData(AnalogInput);
  delay (500);
  Serial.print("Volatge:");
  Serial.println(Voltage_Data);
 // Gyro_Data = G.Gyroloop();
  //Serial.println(Gyro_Data);
  Current_Data = I.CurrentIloop();
  Serial.print("Current:");
  Serial.println(Current_Data);
  Timer_Data= T.RTCloop(); 
  
  Final_Data = String(' ')+String(Voltage_Data)+String (' ')+String (' ')+String (' ')+String (' ')+String(Current_Data);
  Serial.println(Timer_Data);
  Serial.println(Final_Data);
 // BlueTooth.println(Final_Data);
  delay(500);

  //lcd.setCursor(0,0);
  //if( Voltage_Data||Current_Data)
  //{
    //lcd.print("Voltage:");
    //lcd.print(Voltage_Data);
    //lcd.println("Current:");
    //lcd.print(Current_Data);
    //delay(100);
  //}
  //lcd.noAutoscroll();
  //lcd.clear();

 /* DataLogger = SD.open("DataLoggers.txt",FILE_WRITE);
  if (DataLogger)
  {
    DataLogger.println(Final_Data);
    DataLogger.close();
  }
    else{
      Serial.println("error opening");
      //BlueTooth.println("error opening");
    }*/
 }
  
     
        
     
