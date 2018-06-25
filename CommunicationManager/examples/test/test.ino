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
  communicationManager.setup(9600);
  
  
}

void loop()
{
  communicationManager.analyseMessage();
  communicationManager.visualiseMessage();
  float lon;
  int typeRecu = communicationManager.getType();
    if (typeRecu == POSITION)
    {
        communicationManager.recupereLatitude();
        communicationManager.recupereLongitude();
        lon = communicationManager.getLongitude();
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


