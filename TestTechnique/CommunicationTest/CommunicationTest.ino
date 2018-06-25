#include <CommunicationManager.h>
//#include <Coordonnee.h>
#include <Plateforme.h>

#define POSITION 1
#define START 2
#define STOP 3
#define MODE 5
#define MOUVEMENT 8

#define MOTEUR_G_PIN_G      9
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      10
#define MOTEUR_G_PIN_PWM    11
#define MOTEUR_D_PIN_G      4
#define MOTEUR_D_PIN_D      5
#define MOTEUR_D_PIN_PWM    3


Plateforme robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);
CommunicationManager communicationManager(2, 12);
//CoordonneeGPS coordonneeAndroidtest1(-1,-1);


int orderToPlatform;
bool messageR;
int m;
float lon;
float lat;
int mode;
void setup()
{
  Serial.begin(9600);
  communicationManager.setup(9600);
  robot.setup();
  
  
}

void loop()
{

  communicationManager.analyseMessage();
    if (communicationManager.messageAnalyse()){
    int typeRecu = communicationManager.getType();
    switch (typeRecu){

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



      
      case POSITION:
        communicationManager.recupereLatitude();
        communicationManager.recupereLongitude();
        lon = communicationManager.getLongitude();
        lat = communicationManager.getLatitude();
        Serial.print("longitude = ");
        Serial.print(lon, 6);
        Serial.print("  latitude = ");
        Serial.println(lat, 6);
        
  //        coordonneeAndroidtest1.setLatitude(communicationManager.recupereLatitude());
  //        coordonneeAndroidtest1.setLongitude(communicationManager.recupereLongitude());
        break;
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
        robot.tournerADroite(50);
      }
      else if (mouv == "G") {
        robot.tournerAGauche(50);
      }
      else if (mouv == "S") {
        robot.stop();
      }
         
    }
 }
}

