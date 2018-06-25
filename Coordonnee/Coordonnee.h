#ifndef Coordonnee_h
#define Coordonnee_h

#include <math.h>
#include <Arduino.h>
//Cette classe ne doit contenir que des radians !!

#include "Utils.h" 

class CoordonneeGPS
{
private:
    float m_latRad;
    float m_lonRad;
    
public:

    CoordonneeGPS();
    CoordonneeGPS(float latRad, float lonRad, bool argInRad = true);

    float getLatRad() const;
    float getLonRad() const;

    float getLatDeg() const;
    float getLonDeg() const;

    void setLatitude(float latitude, bool argInRad = true);
    void setLongitude(float longitude, bool argInRad = true);

    //renvoie vrai si les attribut ont été initialisés
    bool initSuccess();

    //calcule la longueur entre 2 coordonnée le long du rayon terrestre (suppose que la Terre est ronde)
    float longueurArcCercleTerrestre(CoordonneeGPS const& c2);
    
    float geoBearing(CoordonneeGPS const& b);
    
};

#endif