
#include <PlateformeIntelligente.h>
#include <GPS.h>
#include <MagneticRead.h>
#include <CommunicationManager.h>
#include <Coordonnee.h>
#include <Utils.h>

#define GPS_PIN_TX          6
#define GPS_PIN_RX          7

#define COMM_TX             2
#define COMM_RX             12

#define MOTEUR_G_PIN_G      9
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      10
#define MOTEUR_G_PIN_PWM    11
#define MOTEUR_D_PIN_G      4
#define MOTEUR_D_PIN_D      5
#define MOTEUR_D_PIN_PWM    3

#define POSITION 1
#define START 2
#define STOP 3
#define MODE 5
#define MOUVEMENT 8

#define LIBRE 1
#define CONTROLE 0

#define READ_GPS 0
#define READ_MAG 1 
#define READ_FROM_ANDROID 2
#define WRITE_TO_ANDROID 3
#define MOVE 4

MagneticRead mag;
GPS gps = GPS(GPS_PIN_TX, GPS_PIN_RX);
CommunicationManager communicationManager(2, 12);
PlateformeIntelligente robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);

bool enFonctionnement = true;
int mode = LIBRE;

int actionChosen = READ_FROM_ANDROID;


float latPlateforme;
float lonPlateforme;
float latUtilisateur;
float lonUtilisateur;
float heading;

float repartitionCommDevice = 0;

CoordonneeGPS coordonneeRobot(-1, -1);
CoordonneeGPS coordonneeAndroid(-1, -1);

// OFFSET DU GPS TRES IMPORTANT MAIS SYSTEMATIQUE :
// L'angle donné par HMC5883L => Direction selon X (~ pas trop d'offset)
CoordonneeGPS coordonneeAndroidtest2(48.35776281*DEG_TO_RAD, -4.56902511*DEG_TO_RAD); // haut gauche
CoordonneeGPS coordonneeAndroidtest3(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mag.setup();
  communicationManager.setup(9600);
  gps.setup();

  communicationManager.listen();

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //bouge seulement si start appuyé
  if (enFonctionnement)
  {
    if (mode == LIBRE)
    {
      
      if (gps.connectedOnce())
      {
        float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroid);
        float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroid);

        Serial.print("magnetometre : ");
        Serial.print(mag.getHeadingRad());
        Serial.print(" geobearing : ");
        Serial.print(angleVecteurPoleNord);
        Serial.print(" distance : ");
        Serial.println(distance);
        robot.rejoindreUtilisateur(mag.getHeadingRad(), angleVecteurPoleNord, distance);
        
      }
    }
    else if (mode == CONTROLE)
    {
      String mouv = communicationManager.getMouvement();
      if (mouv == "H") {
        robot.avance(100);
      }
      else if (mouv == "B") {
        robot.recule(100);
      }
      else if (mouv == "D") {
        robot.tournerADroite(100);
      }
      else if (mouv == "G") {
        robot.tournerAGauche(100);
      }
      else if (mouv == "S") {
        robot.stop();
      }
    }
  }
  else
  {
    robot.stop();
  }

  //lit Android pendant 5 secondes 
  if (millis() - repartitionCommDevice > 3000 && actionChosen == READ_FROM_ANDROID && mode == LIBRE)
  {
    actionChosen = READ_GPS;
    gps.listen();
    Serial.print("changement GPS ");
  }

  //utilise GPS
  if (actionChosen == READ_GPS)
  {
    gps.recupDonnees();
    gps.retrieveData();
    if (gps.recuperationDonneesPossible())
    {
        if (gps.connectedOnce())
        {
          coordonneeRobot.setLatitude(gps.getLatitudeRad());
          coordonneeRobot.setLongitude(gps.getLongitudeRad());
        }
        actionChosen = READ_FROM_ANDROID;
        communicationManager.listen();
        repartitionCommDevice = millis();
        Serial.print("action choisi : ");
        Serial.println(actionChosen);
        Serial.print(" gps connected once : ");
        Serial.println(gps.connectedOnce());
        delay(10);
    }
  }

  //utilise Android
  else if (actionChosen == READ_FROM_ANDROID)
  {
    litAndroid();
  }
}

void litAndroid()
{
    float lonAndroid;
    float latAndroid;
    communicationManager.analyseMessage();
    if (communicationManager.messageAnalyse()){
      int typeRecu = communicationManager.getType();
      communicationManager.visualiseMessage();
      Serial.print("millis : ");
      Serial.print(millis());
      Serial.print("   temps précédent : ");
      Serial.print(repartitionCommDevice);
      Serial.print("   en fonctionnement : ");
      Serial.print(enFonctionnement);
      Serial.print("   mode : ");
      Serial.println(mode);
      delay(10);
      switch (typeRecu){
              
        case POSITION:
          communicationManager.recupereLatitude();
          communicationManager.recupereLongitude();
          //false car donnees en radian
          coordonneeAndroid.setLatitude(communicationManager.getLatitude(), false);
          coordonneeAndroid.setLongitude(communicationManager.getLongitude(), false);
          Serial.print("coordonneeAndroid : ");
          Serial.println(coordonneeAndroid.getLonRad());
        break;
    
        case START:
          enFonctionnement = true;
        break;
    
        case STOP:
          enFonctionnement = false;
        break;
    
        case MODE:
          communicationManager.recupereMode();
          mode = communicationManager.getMode();
        break;
    
        case MOUVEMENT:
          communicationManager.recupereMouvement();
        break;
    
      } 
  }
}
