/* Arduino Si7010 relative humidity + temperature sensor example
 * Copyright (C) 2014 by Jakub Kaminski
 *
 * This file is an example for the Arduino Si7020 Library
 *
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino Si7020 Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "Si7020.h"
#include "Wire.h"

Si7020 sensor;

void setup(){
  Serial.begin(9600);
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
  
  // Print out the result
  Serial.print(rh,1);
  Serial.print(" %   ");
  Serial.print(t,2);
  Serial.println(" C");

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
