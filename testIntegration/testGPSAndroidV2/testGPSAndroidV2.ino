
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

#define POSITION 1
#define START 2
#define STOP 3
#define MODE 5
#define MOUVEMENT 8

bool enFonctionnement;
int mode;

#define READ_GPS 0
#define READ_MAG 1 
#define READ_FROM_ANDROID 2
#define WRITE_TO_ANDROID 3
#define MOVE 4

GPS gps = GPS(GPS_PIN_TX, GPS_PIN_RX);
CommunicationManager communicationManager(2, 12);

int actionChosen = READ_FROM_ANDROID;
float latPlateforme;
float lonPlateforme;
float latUtilisateur;
float lonUtilisateur;
float heading;

float repartitionCommDevice = 0;

CoordonneeGPS coordonneeRobot(-1, -1);
CoordonneeGPS coordonneeAndroid(-1, -1);
CoordonneeGPS coordonneeAndroidtest1(48.214729309082031*Utils::degToRad, -4.34124755859*Utils::degToRad); // banc en face du fablab dans l'herbe
// OFFSET DU GPS TRES IMPORTANT MAIS SYSTEMATIQUE :
// L'angle donné par HMC5883L => Direction selon X (~ pas trop d'offset)
CoordonneeGPS coordonneeAndroidtest2(-1, -1); // haut gauche
CoordonneeGPS coordonneeAndroidtest3(-1, -1);
CoordonneeGPS coordonneeAndroidtest4(-1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  communicationManager.setup(9600);
  gps.setup();

  communicationManager.listen();

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //si le bluetooth est déconnecté, le robot s'arrête
  if (digitalRead(A0) == LOW)
  {
    Serial.print("diode allumée");
    Serial.println("");
  }
  else
  {
    if (gps.recuperationDonneesPossible())
    {
  
      float distance = coordonneeRobot.longueurArcCercleTerrestre(coordonneeAndroid);
      
    }
  
    //lit Android pendant 5 secondes 
    if (millis() - repartitionCommDevice > 5000 && actionChosen == READ_FROM_ANDROID)
    {
      Serial.print("coordonnee longitude : ");
      Serial.println(coordonneeAndroid.getLonDeg());
      actionChosen = READ_GPS;
      gps.listen();
  
      Serial.println("lecture du gps");
      
    }
  
    //utilise GPS
    if (actionChosen == READ_GPS)
    {
      gps.recupDonnees();
      gps.retrieveData();
      if (gps.recuperationDonneesPossible())
      {
          if (!gps.connected())
          {
            actionChosen = READ_FROM_ANDROID;
            communicationManager.listen();
            repartitionCommDevice = millis();
          }
          else
          {
            coordonneeRobot.setLatitude(gps.getLatitudeRad());
            coordonneeRobot.setLongitude(gps.getLongitudeRad());
            float angleVecteurPoleNord = coordonneeRobot.geoBearing(coordonneeAndroidtest1);
            Serial.println("angleVecteurPoleNord");
            Serial.println(angleVecteurPoleNord*RAD_TO_DEG);
            actionChosen = READ_FROM_ANDROID;
            communicationManager.listen();
            repartitionCommDevice = millis();
          }
      }
    }
  
    //utilise Android
    else if (actionChosen == READ_FROM_ANDROID)
    {
      litAndroid();
    }
  }
}

void litAndroid()
{
    float lonAndroid;
    float latAndroid;
    communicationManager.analyseMessage();
    if (communicationManager.messageAnalyse()){
      int typeRecu = communicationManager.getType();
      switch (typeRecu){
              
        case POSITION:
          communicationManager.recupereLatitude();
          communicationManager.recupereLongitude();
          //false car donnees en radian
          coordonneeAndroid.setLatitude(communicationManager.getLatitude(), false);
          coordonneeAndroid.setLongitude(communicationManager.getLongitude(), false);
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
