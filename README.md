#Si7020 Arduino & Spark Core Library and Breakout board #

The software is released under GNU License.   
The PCB design is released under Creative Commons License.

## Library ##

Arduino and Spark Core library for Silicon Labs Si7020 relative humidity and temperature
sensor. When using Arduino, copy the files from firmware to Arduino IDE library folder. 
The sensor uses I2C communication. 

**USAGE:**  
See firmware/examples/Si7020\_example.ino for basic usage.

## Breakout ##
Bill of materials:
- 1 x Si7020 [Mouser] (http://www.mouser.com/ProductDetail/Silicon-Labs/Si7020-A10-GM1/?qs=sGAEpiMZZMsrQJTAfdCBRL5%2fWaPBRwpVjGUfQvjZXAsH9hImHflyUA%3d%3d)
- 2 x resistor 10kΩ [Digikey] (http://www.digikey.com/product-detail/en/ERJ-3GEYJ103V/P10KGCT-ND/134717)
- 1 x capacitor 0.1uF [Digikey] (http://www.digikey.com/product-detail/en/GRM188R71C104KA01D/490-1532-1-ND/587771)
- 1 x JST-SH 4pin [Digikey] (http://www.digikey.com/product-detail/en/SM04B-SRSS-TB(LF)(SN)/455-1804-1-ND/926875)

For the photo of assembled board see PCB/Si7020BB.jpg

## Conecting to Arduino ##
- VCC - Arduino 3.3V
- SDA - Arduino pin A4
- SCL - Arduino pin A5
- GND - Arduino GND

## Connection to Spark Core ##
- VCC - Spark 3.3V
- SDA - Spark D0
- SCL - Spark D1
- GND - Spark GND

