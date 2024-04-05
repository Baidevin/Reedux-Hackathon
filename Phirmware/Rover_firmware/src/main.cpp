#include <Arduino.h>
// #include<pins_arduino.h>

void setup() {}
void loop() {}


int main()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  while (1)
  {
    digitalWrite(2, LOW);
    sleep(1000);
    digitalWrite(2, HIGH);
    sleep(1000);
  }
}