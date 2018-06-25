#include "DetectionObstacle.h"

DetectionObstacle::DetectionObstacle(int pinTrig, int pinEcho)
{
    m_pinTrig = pinTrig;
    m_pinEcho = pinEcho;
    timeOut = 125000UL;
}

void DetectionObstacle::setup()
{
    pinMode(m_pinTrig, OUTPUT);
    digitalWrite(m_pinTrig, LOW);
    pinMode(m_pinEcho, INPUT);
}

long DetectionObstacle::recupDistanceMM()
{
    /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(m_pinTrig, HIGH);
  delayMicroseconds(20);
  digitalWrite(m_pinTrig, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(m_pinEcho, HIGH, timeOut);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * Utils::vitesseSonAir/1000;

  return distance_mm;
}

float DetectionObstacle::recupDistanceCM()
{
  return recupDistanceMM()/10;
}

float DetectionObstacle::recupDistanceM()
{
  return recupDistanceCM()/100;
}