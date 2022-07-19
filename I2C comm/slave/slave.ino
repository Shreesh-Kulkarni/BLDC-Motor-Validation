//code for Slave(Arduino nano)

#include <Wire.h>
int tON=0;
int tOFF=0;
int Tperiod=0;
int freq=0;
int hallpin;

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  pinMode(hallpin,OUTPUT);
  Wire.onRequest(requestEvent);
  // register event
}

void loop()
{
  tON=pulseIn(hallpin,HIGH);
  tOFF=pulseIn(hallpin,LOW);
  Tperiod=tON + tOFF;
  freq= 1000000.0/ Tperiod;
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  // respond with frequency message
  Wire.write(freq);
  delay(100);
                       // as expected by master
}
