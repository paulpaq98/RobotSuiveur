#include <GPS.h>
#include <Coordonnee.h>

GPS gps(6, 7);
CoordonneeGPS coordonneeAndroid(48.35786*DEG_TO_RAD, -4.56904*DEG_TO_RAD);

void setup() {
  Serial.begin(9600);
  Serial.println("bonjour");
  
  gps.setup();
}

void loop() {
  gps.recupDonnees();
  gps.retrieveData();
  if (gps.recuperationDonneesPossible())
  {
    
    compareGPSValeur(coordonneeAndroid);
    
  }
}

float compareGPSValeur(CoordonneeGPS coor)
{
  
  Serial.print("offset latitude gps - coor : ");
  Serial.println(gps.getLatitudeDeg() - coor.getLatDeg(), 8);//-0.00028610

  Serial.print("offset longitude : ");
  Serial.println(gps.getLongitudeDeg() - coor.getLonDeg(), 8); //0.45532226

}
