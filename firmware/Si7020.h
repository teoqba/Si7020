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
 */

// There are some differences in libraries between Arduino and Spark
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include "Wire.h"
#elif defined(SPARK)
#include "application.h"
#define _BV(bit) (1 << (bit))
#endif

#ifndef Si7020_h
#define Si7020_h

#define SI7020      0x40
#define RH_HOLD     0xE5
#define RH_NOHOLD   0xF5
#define TEMP_HOLD   0xE3
#define TEMP_NOHOLD 0xF3
#define TEMP_PREV   0xE0
#define RESET_SI    0xFE
#define WREG        0xE6
#define RREG        0xE7
#define HTRE        0x02 

class Si7020
{
	public:
		Si7020();
		void  begin();
		float getRH();
		float readTemp();
		float getTemp();
		void  heaterOn();
		void  heaterOff();
		void  changeResolution(uint8_t i);
		void  resetSettings();
	private:
		uint16_t makeMesurment(uint8_t command);
		void     writeReg(uint8_t value);
		uint8_t  readReg();
};

#endif

