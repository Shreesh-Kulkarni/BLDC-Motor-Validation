#include <Wire.h> 
#include <Robojax_WCS.h>


#define MODEL 9 //see list above
#define SENSOR_PIN A1 //pin for reading sensor
#define SENSOR_VCC_PIN 8 //pin for powring up the sensor
#define ZERO_CURRENT_LED_PIN 2 //zero current LED pin

#define ZERO_CURRENT_WAIT_TIME 100 //wait for 5 seconds to allow zero current measurement
#define CORRECTION_VLALUE 164 //mA
#define MEASUREMENT_ITERATION 100
#define VOLTAGE_REFERENCE  5000.0 //5000mv is for 5V
#define BIT_RESOLUTION 10
#define DEBUT_ONCE true
float crnt;
float i;
  
  Robojax_WCS sensor(
          MODEL, SENSOR_PIN, SENSOR_VCC_PIN, 
          ZERO_CURRENT_WAIT_TIME, ZERO_CURRENT_LED_PIN,
          CORRECTION_VLALUE, MEASUREMENT_ITERATION, VOLTAGE_REFERENCE,
          BIT_RESOLUTION, DEBUT_ONCE           
          );
class Current{
  public:
  void CurrentISetup()
{
  
  sensor.start();
  sensor.getModel();
  //Serial.print("Sensor: "); Serial.println(sensor.getModel());
  //blueTooth.print("Sensor"); blueTooth.println(sensor.getModel());
}
float CurrentIloop()
{ 
  sensor.readCurrent();//this must be inside loop
  //sensor.printCurrent();
 i = sensor.getCurrent();
 return i;
 //Serial.print("Current:");
//Serial.println(i);
delay(100);

 

}

  
};
