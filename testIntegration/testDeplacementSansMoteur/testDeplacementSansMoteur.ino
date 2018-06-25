
#include <PlateformeIntelligente.h>
#include <GPS.h>
#include <MagneticRead.h>
#include <CommunicationManager.h>
#include <Coordonnee.h>
#include <Utils.h>

#define GPS_PIN_TX          6
#define GPS_PIN_RX          7

#define COMM_TX             2
#define COMM_RX             13


#define READ_GPS 0
#define READ_MAG 1 
#define READ_FROM_ANDROID 2
#define WRITE_TO_ANDROID 3
#define MOVE 4

MagneticRead mag;

int actionChosen = READ_GPS;
float latPlateforme;
float lonPlateforme;
float latUtilisateur;
float lonUtilisateur;
float heading;

float anglePlateformePoleNord = -1;
float timer = 0;

GPS gps = GPS(GPS_PIN_TX, GPS_PIN_RX);

CoordonneeGPS coordonneeRobot(-1, -1);
CoordonneeGPS coordonneeAndroidtest1(4835.78/100*Utils::degToRad, -456.900/100*Utils::degToRad); // haut droite
CoordonneeGPS coordonneeAndroidtest2(-1, -1); // haut gauche
CoordonneeGPS coordonneeAndroidtest3(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mag.setup();
  gps.setup();

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (actionChosen) {
    case READ_GPS:
    {
        gps.recupDonnees();
        gps.retrieveData();
        if (gps.recuperationDonneesPossible())
        {
            coordonneeRobot.setLatitude(gps.getLatitude());
            coordonneeRobot.setLongitude(gps.getLongitude());
            actionChosen = READ_MAG;
                    Serial.println("en cours de lecture");
           
        }
        break;
    }
    
    case READ_MAG:
    {
      anglePlateformePoleNord = mag.getHeadingDeg();
      actionChosen = MOVE;
      break;
    }
  
    case MOVE:
    {
      float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroidtest1);
      float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroidtest1);
  
      Serial.println("angleVecteurPoleNord");
      Serial.println(angleVecteurPoleNord);
      Serial.println("anglePlateformePoleNord");
      Serial.println(anglePlateformePoleNord);
      Serial.println("");
      delay(1000);
      actionChosen = READ_GPS;
    }
  }
}
