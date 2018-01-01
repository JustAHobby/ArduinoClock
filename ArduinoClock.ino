#include <TinyWireM.h>
#include <Tiny_LEDBackpack.h>
#define DS1307_ADDRESS 0x68
#define i2c_addr 0x70
#include <Wire.h>
#include <RTClib.h>

Tiny_7segment sevenseg = Tiny_7segment();
RTC_DS1307 rtc;
bool colon;

void setup() {
  sevenseg.begin(i2c_addr);
  sevenseg.clear();
  sevenseg.drawColon(false);
  sevenseg.writeDisplay();
  delay(1000);
  if (!rtc.begin()) {
    while (1);
  }
  colon = true;
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  /*
  if (! rtc.isrunning()) {
    //following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //This line sets the RTC with an explicit date & time, for example to set
    //January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2017, 12, 31, 3, 45, 0));
  }
  */
}
void loop() {
  printDate(colon);
  colon = !colon;
  delay(500);
}
byte bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}
void printDate(bool colon) {
  DateTime now = rtc.now();
  int hour2 = now.hour();
  
  TinyWireM.beginTransmission(DS1307_ADDRESS);
  byte zero = 0x00;
  TinyWireM.send(zero);
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(DS1307_ADDRESS, 7);
  int second = bcdToDec(TinyWireM.receive());
  int minute = bcdToDec(TinyWireM.receive());
  int hour = bcdToDec(TinyWireM.receive() & 0b111111); //24 hour time
  int weekDay = bcdToDec(TinyWireM.receive()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(TinyWireM.receive());
  int month = bcdToDec(TinyWireM.receive());
  int year = bcdToDec(TinyWireM.receive());

  if(hour > 12) {
    hour = hour-12;
  }
  
  sevenseg.print((hour*100)+minute);
  //sevenseg.print(hour);
  sevenseg.drawColon(colon);
  sevenseg.writeDisplay();
}

