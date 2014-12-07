#if defined(ARDUINO)
#include "Wire.h"
#include "Si7020.h"
#elif defined(SPARK)
#include "Si7020/Si7020.h"
#endif

Si7020 sensor;

void setup(){
  Serial.begin(57600);
  sensor.begin();
  
  // To change resolution of the sensor use
  // sensor.changeResolution(int i) where i=[0-3], 
  //sensor.changeResolution(0);

}

void loop(){
  // Measure RH
  float rh = sensor.getRH();
  // Measure Temperature
  float t = sensor.getTemp();
  
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement instead with readTemp()
  // float t = sensor.readTemp();
  
  // Print the result in the JSON format
  Serial.print("{\"rh\":\"");
  Serial.print(rh,1);
  Serial.print("\",\"temp\":\"");
  Serial.print(t,2);
  Serial.println("\"}"); 


  delay(1000);

  // To play switch on/off onboard heater use heaterOn() and heaterOff()
  // heaterOn();
  // delay(5000);
  // heaterOff();
}
