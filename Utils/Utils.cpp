#include "Utils.h"

float Utils::rayonTerrestre = 6371000;
float Utils::vitesseSonAir = 340.0;

float Utils::byteToFloat(unsigned char intBit[64], unsigned int longueurIntBit) {

  //trouve l'index du point
  unsigned int indexComa = 0;
  int valueInt = 0;
  while (intBit[indexComa] != '.' && indexComa < longueurIntBit) {
    indexComa += 1;
  }

  //calcule la partie entière
  int puissance10 = 1;
  for (int index =0; index<indexComa;index++) {
    valueInt += (int(intBit[indexComa-1-index])-48)*puissance10;
    puissance10 *= 10;
  }
  puissance10 = 10;

  //calcule la partie décimale
  float valueDecimal = 0;
  for (unsigned int index = indexComa+1; index<longueurIntBit; index ++)
  {
    valueDecimal += (float(intBit[index])-48)/puissance10;
    puissance10 *= 10;
  }
  return valueInt + valueDecimal;
}

float Utils::nbModuloN(float nb, float modulo)
{
    // Correct for when signs are reversed.
    while(nb < 0)
    { 
      nb += modulo;
    }
      
    // Check for wrap due to addition of declination.
    while (nb >= modulo) {
        nb -= modulo;
    }
    return nb;
}

float Utils::nbModulo2PI(float nb)
{
  return nbModuloN(nb, 2*M_PI);
}