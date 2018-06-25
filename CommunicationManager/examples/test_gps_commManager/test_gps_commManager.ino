#include <CommunicationManager.h>
//#include <Coordonnee.h>
#include <Plateforme.h>
#include <GPS.h>

//definit les types de protocole possibles
#define POSITION  1
#define START     2
#define STOP      3
#define MODE      5
#define MOUVEMENT 8

//definit les device à écouter
#define READ_SMARTPHONE        0
#define READ_GPS               1

//définit les pin des moteurs
#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

//définit les pin du GPS
#define PIN_TX_GPS          6
#define PIN_RX_GPS          255

//définit les pin du bluetooth
#define PIN_TX_BLUETOOTH    2
#define PIN_RX_BLUETOOTH    12

Plateforme robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);
CommunicationManager communicationManager(PIN_TX_BLUETOOTH, PIN_RX_BLUETOOTH);
GPS gps(PIN_TX_GPS, PIN_RX_GPS);
//CoordonneeGPS coordonneeAndroidtest1(-1,-1);

int deviceListened = READ_SMARTPHONE;

int orderToPlatform;
float lon;
float lat;
int mode;




void setup()
{
  Serial.begin(9600);
  communicationManager.setup(9600);
  robot.setup();
  gps.setup();
  
  
}

void loop()
{
  
  
  if (deviceListened == READ_SMARTPHONE)
  {
    communicationManager.analyseMessage();
    if (communicationManager.messageAnalyse()){
      applyMessageSmartphone();
      deviceListened = READ_GPS;
    }
  }
  else if (deviceListened == READ_GPS)
  {
      gps.listen();
      gps.recupDonnees();
      gps.retrieveData();
      if (gps.recuperationDonneesPossible())
      {
          Serial.println(gps.getLatitude());
          Serial.println(gps.getLongitude());
          deviceListened = READ_SMARTPHONE;
      }
  }
  
  if (mode==0){
    String mouv = communicationManager.getMouvement();
    if (mouv == "H") {
      robot.avance(100);
    }
    else if (mouv == "B") {
      robot.recule(100);
    }
    else if (mouv == "D") {
      robot.tournerADroite();
    }
    else if (mouv == "G") {
      robot.tournerAGauche();
    }
    else if (mouv == "S") {
      robot.stop();
    }
  }
  
}

void applyMessageSmartphone()
{
  int typeRecu = communicationManager.getType();
  switch (typeRecu){
      case POSITION:
        communicationManager.recupereLatitude();
        communicationManager.recupereLongitude();
        lon = communicationManager.getLongitude();
        lat = communicationManager.getLatitude();
        Serial.print("longitude = ");
        Serial.println(lon, 6);
        Serial.print("latitude = ");
        Serial.println(lat, 6);
        Serial.println("out loop 2");
  //        coordonneeAndroidtest1.setLatitude(communicationManager.recupereLatitude());
  //        coordonneeAndroidtest1.setLongitude(communicationManager.recupereLongitude());
      break;

    case START:
      orderToPlatform = START;
    break;

    case STOP:
      orderToPlatform = STOP;
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

