#ifndef DETECTION_OBSTACLE_h
#define DETECTION_OBSTACLE_h

#include "Arduino.h"
#include "Utils.h"

class DetectionObstacle 
{
private:
    unsigned int m_pinTrig;
    unsigned int m_pinEcho;
    unsigned long timeOut;


public:
    DetectionObstacle(int pinTrig, int pinEcho);

    void setup();

    long recupDistanceMM();
    float recupDistanceCM();
    float recupDistanceM();

};

#endif