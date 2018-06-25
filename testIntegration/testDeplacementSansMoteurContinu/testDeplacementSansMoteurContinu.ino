
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
CoordonneeGPS coordonneeAndroidtest1(48.214729309082031*Utils::degToRad, -4.34124755859*Utils::degToRad); // banc en face du fablab dans l'herbe
// OFFSET DU GPS TRES IMPORTANT MAIS SYSTEMATIQUE :
// L'angle donné par HMC5883L => Direction selon X (~ pas trop d'offset)
CoordonneeGPS coordonneeAndroidtest2(-1, -1); // haut gauche
CoordonneeGPS coordonneeAndroidtest3(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mag.setup();
  anglePlateformePoleNord = mag.getHeadingDeg();

  gps.setup();

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (gps.recuperationDonneesPossible())
  {
    float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroidtest1);
    float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroidtest1);
    
    Serial.println("angleVecteurPoleNord");
    Serial.println(angleVecteurPoleNord*RAD_TO_DEG);
    Serial.println("anglePlateformePoleNord");
    Serial.println(mag.getHeadingDeg());
    Serial.println("");
    delay(1000);
  }
  
  gps.recupDonnees();
  gps.retrieveData();
  if (gps.recuperationDonneesPossible())
  {
      coordonneeRobot.setLatitude(gps.getLatitudeRad());
      coordonneeRobot.setLongitude(gps.getLongitudeRad());
  }
}

float compareGPSValeur(CoordonneeGPS coor)
{
  
  Serial.print("offset latitude");
  Serial.println(gps.getLatitudeDeg() - coor.getLatDeg());
  Serial.print("offset longitude");
  Serial.println(gps.getLongitudeDeg() - coor.getLonDeg());
}

