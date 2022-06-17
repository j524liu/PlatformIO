#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial downSerial(1);

unsigned int flag = 0;

void OnDisconnect() {
  detachInterrupt(27);
  // delay(2);
  Serial.printf("DIGITAL: %d.", digitalRead(27));
  if(!flag)
  {
    flag = 1;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  downSerial.begin(115200, SERIAL_8N1, 12, 14);   //RX--12; TX--14
  Serial.print("{start}{end}");

  pinMode(27, INPUT);
  // digitalWrite(27, LOW);
  attachInterrupt(27, OnDisconnect, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  // while(!downSerial.available())
  while(!downSerial.available())
  {
    if(1 == flag)
    {
      Serial.print("{start}{end}");
      flag = 0;
      attachInterrupt(27, OnDisconnect, FALLING);
    }
    // Serial.print("HHHHHHHHHHHHH");
    delay(10);
  }
  String buff = downSerial.readString();
  String send = buff + "{end}";
  Serial.print(send);
}