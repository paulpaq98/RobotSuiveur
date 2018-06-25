#include <DetectionObstacle.h>

#define PIN_TRIGGER 3
#define PIN_ECHO 4

DetectionObstacle mesureDistance(PIN_TRIGGER, PIN_ECHO);

void setup()
{
  Serial.begin(9600);
  mesureDistance.setup();
}

void loop()
{
  Serial.println();
  mesureDistance.recupDistanceCM();
}

