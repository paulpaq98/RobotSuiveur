#include "Plateforme.h"

Plateforme::Plateforme(int pinGaucheMGauche, int pinDroiteMGauche, int pinPWMMGauche, int pinGaucheMDroite, int pinDroiteMDroite, int pinPWMMDroite) : m_moteurGauche(Moteur(pinDroiteMGauche, pinGaucheMGauche, pinPWMMGauche)), m_moteurDroit(Moteur(pinGaucheMDroite, pinDroiteMDroite, pinPWMMDroite))
{
    
}

void Plateforme::connecteMoteurGauche(int pinGauche, int pinDroite, int pinPWM)
{
    m_moteurGauche = Moteur(pinGauche, pinDroite, pinPWM);
}

void Plateforme::connecteMoteurDroit(int pinGauche, int pinDroite, int pinPWM)
{
    m_moteurDroit = Moteur(pinGauche, pinDroite, pinPWM);
}

void Plateforme::setup()
{
    m_moteurGauche.setup();
    m_moteurDroit.setup();
}

void Plateforme::stop()
{
    m_moteurGauche.stop();
    m_moteurDroit.stop();
}

void Plateforme::avance(unsigned int vitesse) 
{
    m_moteurGauche.tourneVersGauche(vitesse);
    m_moteurDroit.tourneVersDroite(vitesse);
}

void Plateforme::recule(unsigned int vitesse)
{
    m_moteurGauche.tourneVersDroite(vitesse);
    m_moteurDroit.tourneVersGauche(vitesse);
}

void Plateforme::tournerAGauche(unsigned int vitesseEnTournant)
{
    m_moteurGauche.stop();
    m_moteurDroit.tourneVersDroite(vitesseEnTournant);
}

void Plateforme::tournerADroite(unsigned int vitesseEnTournant)
{
    m_moteurGauche.tourneVersGauche(vitesseEnTournant);
    m_moteurDroit.stop();
}

