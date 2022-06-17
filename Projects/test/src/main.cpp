#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial upSerial(0);
HardwareSerial downSerial(1);

unsigned int flag = 0;

void OnDisconnect() {
  detachInterrupt(0);
  if(!flag)
  {
    flag = 1;
  }
  // delay(2);
  // Serial.printf("DIGITAL: %d.", digitalRead(27));
} 

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  // Serial.println("STARTED");

  upSerial.begin(115200, SERIAL_8N1, 4, 5);       //RX--4; TX--5
  downSerial.begin(115200, SERIAL_8N1, 10, 1);    //RX--10; TX--1

  pinMode(0, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  
  delay(2000);
  // upSerial.printf("P1: %d", digitalRead(0));
  if(!digitalRead(0))
  {
    upSerial.print("{START}{int a = 2}");
  }

  attachInterrupt(0, OnDisconnect, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!downSerial.available())
  {
    if(1 == flag)
    {
      upSerial.print("{START}{int a = 2}");
      flag = 0;
      attachInterrupt(0, OnDisconnect, FALLING);
    }
    // Serial.print("HHHHHHHHHHHHH");
    delay(10);
  }

  String buff = downSerial.readString();
  String send = buff + "{int a = 2}";
  upSerial.print(send);
  downSerial.flush();
}