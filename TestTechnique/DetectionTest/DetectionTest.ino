#include <DetectionObstacle.h>

#define PIN_TRIGGER 8
#define PIN_ECHO 13

DetectionObstacle mesureDistance(PIN_TRIGGER, PIN_ECHO);

void setup()
{
  Serial.begin(9600);
  mesureDistance.setup();
}

void loop()
{
  distance_echo = mesureDistance.recupDistanceCM();
    Serial.print("distance mesurée :");
    Serial.println(distance_echo);
    
    if (5<distance_echo && distance_echo<20 )
    {
          Serial.println("mouvement");     
          robot.stop();
          delay(500);
          robot.recule(100);
          delay(500);
          robot.tournerADroite(100);
          delay(500);
          robot.stop();
          delay(500);
        }
}

