/* Arduino Si7010 relative humidity + temperature sensor
 * Copyright (C) 2014 by Jakub Kaminski
 *
 * This file is part of the Arduino Si7020 Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino Si7020 Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * TODO: implement checksum checking
 */

#include "Si7020.h"

Si7020::Si7020(){}

void Si7020::begin()
{
	Wire.begin();
}

float Si7020::getRH()
{
	// Measure the relative humidity 
	uint16_t RH_Code = makeMesurment(RH_HOLD);
	float result = (125.0*RH_Code/65536)-6;
	return result;
}

float Si7020::readTemp()
{
	// Read temperature from previous RH measurement.
	uint16_t temp_Code = makeMesurment(TEMP_PREV);
	float result = (175.25*temp_Code/65536)-46.85;
	return result;
}

float Si7020::getTemp()
{
	// Measure temperature 
	uint16_t temp_Code = makeMesurment(TEMP_HOLD);
	float result = (175.25*temp_Code/65536)-46.85;
	return result;
}

void Si7020::heaterOn()
{
	// Turns on the Si7020 heater
	uint8_t regVal = readReg();
	regVal |= _BV(HTRE);
	//turn on the heater
	writeReg(regVal);
}

void Si7020::heaterOff()
{
	// Turns off the Si7020 heater
	uint8_t regVal = readReg();
	regVal &= ~_BV(HTRE);
	writeReg(regVal);
}

void Si7020::changeResolution(uint8_t i)
{
	// Changes to resolution of Si7020 measurements.
	// Set i to:
	//      RH         Temp
	// 0: 12 bit       14 bit (default)
	// 1:  8 bit       12 bit
	// 2: 10 bit       13 bit
	// 3: 11 bit       11 bit

	uint8_t regVal = readReg();
	// zero resolution bits
	regVal &= 0b011111110;
	switch (i) {
	  case 1:
	    regVal |= 0b00000001;
	    break;
	  case 2:
	    regVal |= 0b10000000;
	    break;
	  case 3:
	    regVal |= 0b10000001;
	  default:
	    regVal |= 0b00000000;
	    break;
	}
	// write new resolution settings to the register
	writeReg(regVal);
}

void Si7020::resetSettings()
{
	//Reset user resister
	writeReg(RESET_SI);
}

uint16_t Si7020::makeMesurment(uint8_t command)
{
	// Take one Si7020 measurement given by command.
	// It can be either temperature or relative humidity
	// TODO: implement checksum checking
	
	uint16_t nBytes = 3;
	// if we are only reading old temperature, read olny msb and lsb
	if (command == 0xE0) nBytes = 2;

	Wire.beginTransmission(SI7020);
	Wire.write(command);
	Wire.endTransmission();
	// When not using clock stretching (*_NOHOLD commands) delay here 
	// is needed to wait for the measurement.
	// According to datasheet the max. conversion time is ~22ms
	// delay(30);
		
	Wire.requestFrom(SI7020,nBytes);
	//Wait for data
	int counter = 0;
	while (Wire.available() < nBytes){
	  delay(1);
	  counter ++;
	  if (counter >100){
	    // Timeout: Sensor did not return any data
	    return 0;
	  }
	}

	unsigned int msb = Wire.read();
	unsigned int lsb = Wire.read();
	// Clear the last to bits of LSB to 00. 
	// According to datasheet LSB of RH is always xxxxxx10
	lsb &= 0xFC;
	unsigned int mesurment = msb << 8 | lsb;

	return mesurment;
}

void Si7020::writeReg(uint8_t value)
{  
	// Write to user register on Si7020
	Wire.beginTransmission(SI7020);
	Wire.write(WREG);
	Wire.write(value);
	Wire.endTransmission();
}

uint8_t Si7020::readReg()
{
	// Read from user register on Si7020
	Wire.beginTransmission(SI7020);
	Wire.write(RREG);
	Wire.endTransmission();
	Wire.requestFrom(SI7020,1);
	uint8_t regVal = Wire.read();
	return regVal;
}
