#include <CommunicationManager.h>
//#include <Coordonnee.h>

#define POSITION 1
#define START 2
#define STOP 3


CommunicationManager communicationManager(2, 12);
//CoordonneeGPS coordonneeAndroidtest1(-1,-1);

int orderToPlatform;
void setup()
{
  Serial.begin(9600);
  communicationManager.setup(9600);
  
  
}

void loop()
{
  communicationManager.analyseMessage();
  communicationManager.visualiseMessage();
  int typeRecu = communicationManager.getType();
    if (typeRecu == POSITION)
    {
        communicationManager.recupereLatitude();
        communicationManager.recupereLongitude();
        float lon = communicationManager.getLongitude();
        float lat = communicationManager.getLatitude();
        Serial.print("longitude = ");
        Serial.println(lon, 6);
        Serial.print("latitude = ");
        Serial.println(lat, 6);
        Serial.println("out loop 2");
    }
    else if (typeRecu == START)
    {
      orderToPlatform = START;  
    }
    else if (typeRecu == STOP)
    {
      orderToPlatform = STOP;
    }
  

   }


