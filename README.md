# ArduinoClock

## Overview
Codebase for a homemade Arduino clock using an Adafruit 7 segment LED display running on code found online.
http://imgur.com/DtJGGeH

## Details
### Parts
  1. ADAFRUIT TRINKET - MINI MICROCONTROLLER - 5V LOGIC
  ..* https://www.adafruit.com/product/1501
  2. ADAFRUIT 0.56" 4-DIGIT 7-SEGMENT DISPLAY W/I2C BACKPACK - YELLOW
  ..* https://www.adafruit.com/product/879
  3. CHRONODOT - ULTRA-PRECISE REAL TIME CLOCK
  ..* https://www.adafruit.com/product/255

### Libraries
Extra Library files were needed as the trinket had trouble working with the main adafruit libs. They are included in this repo.
  1. Tiny_LEDBackpack
  ..* https://github.com/millerlp/Tiny_LEDBackpack
  2. TinyWireM
  ..* http://arduino.cc/playground/uploads/Code/TinyWireM.zip
  3. RTClib
  ..* https://github.com/adafruit/RTClib