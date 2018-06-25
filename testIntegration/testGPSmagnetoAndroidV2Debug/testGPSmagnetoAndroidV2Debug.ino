
#include <PlateformeIntelligente.h>
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

MagneticRead mag;
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
  mag.setup();
  communicationManager.setup(9600);

//doees not work if not in the end
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  //utilise Android
  if (actionChosen == READ_FROM_ANDROID)
  {
    litAndroid();
  }
}

void litAndroid()
{
    float lonAndroid;
    float latAndroid;
    communicationManager.analyseMessage();
          communicationManager.visualiseMessage();
    if (communicationManager.messageAnalyse()){
      int typeRecu = communicationManager.getType();
            Serial.println(typeRecu);
      switch (typeRecu){
              
        case POSITION:
          communicationManager.recupereLatitude();
          communicationManager.recupereLongitude();
          //false car donnees en radian
          coordonneeAndroid.setLatitude(communicationManager.getLatitude(), false);
          coordonneeAndroid.setLongitude(communicationManager.getLongitude(), false);
          Serial.print("latitude");
          Serial.println(communicationManager.getLatitude());
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
