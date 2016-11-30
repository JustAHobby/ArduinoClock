#include <Wire.h>
#define DS1307_ADDRESS 0x68
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
bool colon;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  matrix.begin(0x70);
  colon = true;
}

void loop() {
  printDate(colon);
  colon = !colon;
  delay(1000);
  
  /*
  DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print('.');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(500);
  now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(' ');
  Serial.print(now.minute(), DEC);
  Serial.print('.');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(500);
  */
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(bool colon) {
  Wire.beginTransmission(DS1307_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);
  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());
  Serial.print(hour);
  if(colon) {
    Serial.print(":");
  }
  else 
  {
    Serial.print(" "); 
  }
  matrix.drawColon(colon);
  Serial.println(minute);
  matrix.print(hour);
  matrix.print(minute);
  matrix.writeDisplay();
}

