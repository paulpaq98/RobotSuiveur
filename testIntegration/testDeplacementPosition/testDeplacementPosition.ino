
#include <PlateformeIntelligente.h>
#include <GPS.h>
#include <MagneticRead.h>
#include <CommunicationManager.h>
#include <Coordonnee.h>

#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

#define GPS_PIN_TX          6
#define GPS_PIN_RX          7

#define COMM_TX             2
#define COMM_RX             13


#define READ_GPS 0
#define READ_MAG 1 
#define READ_FROM_ANDROID 2
#define WRITE_TO_ANDROID 3
#define MOVE 4

PlateformeIntelligente plateformeIntelligente(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);
MagneticRead mag;

int actionChosen = READ_GPS;
float latPlateforme;
float lonPlateforme;
float latUtilisateur;
float lonUtilisateur;
float heading;

float anglePlateformePoleNord = -1;

int test = millis();

bool firstTimeGPS = true;
bool firstTimeCommManager = true;

GPS gps = GPS(GPS_PIN_TX, GPS_PIN_RX);
CommunicationManager* communicationManager = new CommunicationManager(COMM_TX, COMM_RX);

CoordonneeGPS coordonneeRobot(-1, -1);
CoordonneeGPS coordonneeAndroidtest1(4835.78, -456.892); // haut droite
CoordonneeGPS coordonneeAndroidtest2(-1, -1); // haut gauche
CoordonneeGPS coordonneeAndroidtest3(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mag.setup();
  plateformeIntelligente.setup();

  gps.setup();

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (actionChosen == READ_GPS) 
  {

      gps.read1BitGPS();
      if (gps.foundValue()) {
        Serial.println("coucou");
        Serial.println(gps.getLatitude());
        Serial.println(gps.getLongitude());
        coordonneeRobot.setLatitude(gps.getLatitude());
        coordonneeRobot.setLongitude(gps.getLongitude());
        actionChosen = READ_MAG;
        Serial.println("tempsGPS");
        Serial.println(millis()-test);
      }
    
  }
  else if (actionChosen == READ_MAG)
  {
    anglePlateformePoleNord = mag.getHeadingDeg();
    Serial.println(anglePlateformePoleNord);

    actionChosen = MOVE;
    
  }
//  else if (communicationChosen == READ_FROM_ANDROID)
//  {
//    //coorUtilisateur = Coordonnee(communicationManager.getLatitude(), communicationManager.getLongitude());
//    communicationManager->analyseMessage();
//    Serial.println("1 tour");
//    if (communicationManager->messageAnalyse())
//    {
//      
//      Serial.println("communication");
//      Serial.println(communicationManager->getLongitude());
//      Serial.println(communicationManager->getLatitude());
//      coordonneeAndroidtest1.setLatitude(communicationManager->getLatitude());
//      coordonneeAndroidtest1.setLongitude(communicationManager->getLongitude());
//      communicationChosen = READ_GPS;
//      
//    }
//
//    
//    //..... le reste des actions possibles
//  }
//  else if (communicationChosen == WRITE_TO_ANDROID)
//  {
//    //....ce qu'on doit envoyer
//  }
//
  else if (actionChosen == MOVE)
  {
    float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroidtest1);
    float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroidtest1);

    Serial.println(angleVecteurPoleNord);
    Serial.println(anglePlateformePoleNord);
  
    plateformeIntelligente.rejoindreUtilisateur(anglePlateformePoleNord, angleVecteurPoleNord, distance);
    actionChosen = READ_GPS;
    test = millis();
  }
}
