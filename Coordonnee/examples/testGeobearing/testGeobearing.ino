#include <Coordonnee.h>


CoordonneeGPS test1CoorPlateforme = CoordonneeGPS(24*Utils::degToRad, Utils::nbModulo2PI(12*Utils::degToRad));
CoordonneeGPS test1CoorUser = CoordonneeGPS(15*Utils::degToRad, Utils::nbModulo2PI(35*Utils::degToRad));

CoordonneeGPS test2CoorPlateforme = CoordonneeGPS(15*Utils::degToRad, Utils::nbModulo2PI(5*Utils::degToRad));
CoordonneeGPS test2CoorUser = CoordonneeGPS(-5*Utils::degToRad, Utils::nbModulo2PI(-12*Utils::degToRad));

void setup() {
// put your main code here, to run repeatedly:
  Serial.begin(9600);

  Serial.println("test1");
  Serial.println(Utils::nbModulo2PI(test1CoorPlateforme.geoBearing(test1CoorUser))*Utils::radToDegree);

  Serial.println("test2");
  Serial.println(Utils::nbModulo2PI(test2CoorUser.geoBearing(test2CoorPlateforme))*Utils::radToDegree);
  Serial.println(Utils::nbModulo2PI(test2CoorPlateforme.geoBearing(test2CoorUser))*Utils::radToDegree);
    //..... le reste des actions possibles
}

void loop() {
  
 

}
