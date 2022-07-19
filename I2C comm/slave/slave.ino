//code for Slave(Arduino nano)

#include <Wire.h>

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("SPEED OF VEHICLE:"); // respond with message of 6 bytes
  Wire.write("10km/h");
  Wire.write("\n");
  delay(100);
                       // as expected by master
}
