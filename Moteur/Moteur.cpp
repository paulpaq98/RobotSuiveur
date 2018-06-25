#include "Moteur.h"

Moteur::Moteur(int pinGauche, int pinDroite, int pinPWM) : m_pinGauche(pinGauche), m_pinDroite(pinDroite), m_pinPWM(pinPWM), m_ratioPWMActuel(0)
{

}

void Moteur::setup()
{
    pinMode(m_pinGauche, OUTPUT);
    pinMode(m_pinDroite, OUTPUT);
    pinMode(m_pinPWM, OUTPUT);
}

void Moteur::stop()
{
    digitalWrite(m_pinGauche, LOW); 
    digitalWrite(m_pinDroite, LOW);
    analogWrite(m_pinPWM, 0);
    m_ratioPWMActuel = 0;
}

void Moteur::tourneVersDroite(int vitesse)
{
    if (vitesse == 0)
    {
        stop();
        m_ratioPWMActuel = 0;
    }
    else 
    {
        digitalWrite(m_pinGauche, HIGH); 
        digitalWrite(m_pinDroite, LOW);
        analogWrite(m_pinPWM, vitesse);
        m_ratioPWMActuel = vitesse;
    }
}

void Moteur::tourneVersGauche(int vitesse)
{
    if (vitesse == 0)
    {
        stop();
        m_ratioPWMActuel = 0;
    }
    else 
    {
        digitalWrite(m_pinGauche, LOW); 
        digitalWrite(m_pinDroite, HIGH);
        analogWrite(m_pinPWM, vitesse);
        m_ratioPWMActuel = vitesse;
    }
}

int Moteur::getRatioPWMActuel()
{
    return m_ratioPWMActuel;
}