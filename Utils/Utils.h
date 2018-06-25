#ifndef Utils_h
#define Utils_h

#include <Arduino.h>

class Utils
{
public:
    static float rayonTerrestre; //m
    static float vitesseSonAir; // en m/s

    static float radToDegree;
    static float degToRad;

    static float byteToFloat(unsigned char intBit[64], unsigned int longueurIntBit);
    static float nbModuloN(float nb, float modulo);
    static float nbModulo2PI(float nb);

};

#endif