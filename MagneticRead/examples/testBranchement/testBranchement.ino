#include "MagneticRead.h"

MagneticRead mag;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mag.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("heading : ");
  Serial.println(mag.getHeadingRad());
}
