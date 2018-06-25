
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

#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

#define READ_GPS 0
#define READ_MAG 1 
#define READ_FROM_ANDROID 2
#define WRITE_TO_ANDROID 3
#define MOVE 4

MagneticRead mag;
GPS gps = GPS(GPS_PIN_TX, GPS_PIN_RX);
PlateformeIntelligente robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);

int actionChosen = READ_GPS;
float latPlateforme;
float lonPlateforme;
float latUtilisateur;
float lonUtilisateur;
float heading;

float anglePlateformePoleNord = -1;
float timer = 0;
float tempsEntre = 0;

CoordonneeGPS coordonneeRobot(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.setup();
  gps.setup();
  mag.setup();
  anglePlateformePoleNord = mag.getHeadingDeg();

//doees not work if not in the end
  
}

CoordonneeGPS coordonneeAndroid(48.3577*DEG_TO_RAD, -4.5694*DEG_TO_RAD);

void loop() {
  // put your main code here, to run repeatedly:

  
  if (gps.connectedOnce())
  {
    float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroid);
    float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroid);
    
    Serial.println("angleVecteurPoleNord");
    Serial.println(angleVecteurPoleNord*RAD_TO_DEG);
    Serial.println("anglePlateformePoleNord");
    Serial.println(mag.getHeadingDeg());
    Serial.println("");

    robot.rejoindreUtilisateur(mag.getHeadingRad(), angleVecteurPoleNord, distance);
    Serial.print("temps Avant update");
    Serial.println(millis() - tempsEntre);
    actionChosen = READ_GPS;
    tempsEntre = millis();
  }

  gps.recupDonnees();
  gps.retrieveData();
  if (gps.connectedOnce())
  {
      coordonneeRobot.setLatitude(gps.getLatitudeRad());
      coordonneeRobot.setLongitude(gps.getLongitudeRad());
      actionChosen = READ_MAG;
  }
}

