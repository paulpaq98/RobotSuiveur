#ifndef Motor_h
#define Motor_h

/** 
 * Les noms de cette librairie sont adaptés si vous placez la roue du moteur en face de vous, et la carte derrière la roue
 */ 

#include "Arduino.h"

class Moteur {
protected:
    int m_pinGauche;
    int m_pinDroite;
    int m_pinPWM;

    int m_ratioPWMActuel;
    
public:
    Moteur(int pinGauche, int pinDroite, int pinPWM);
    void setup();

    void stop();
    void tourneVersGauche(int vitesse);
    void tourneVersDroite(int vitesse);

    int getRatioPWMActuel();
    
};

#endif