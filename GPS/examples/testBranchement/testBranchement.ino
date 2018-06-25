#include <GPS.h>

GPS gps(6, 255);

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
    
    Serial.println(gps.getLatitude());
    Serial.println(gps.getLongitude());
    
  }
}
