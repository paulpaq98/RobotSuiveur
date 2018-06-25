#include <Plateforme.h>

#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

Plateforme plateforme(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);


void setup() 
{
  plateforme.setup();

  delay(15000);
  

  plateforme.avance(220);
  delay(15000);
  plateforme.stop();
  delay(60000);

  plateforme.avance(180);
  delay(15000);
  plateforme.stop();
  delay(60000);

  plateforme.avance(140);
  delay(15000);
  plateforme.stop();
  delay(60000);

  plateforme.avance(100);
  delay(15000);
  plateforme.stop();
  delay(60000);

}

void loop()
{
  
}

