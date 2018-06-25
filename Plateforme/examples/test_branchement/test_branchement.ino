#include <Plateforme.h>

#define MOTEUR_G_PIN_G      9
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      10
#define MOTEUR_G_PIN_PWM    11
#define MOTEUR_D_PIN_G      4
#define MOTEUR_D_PIN_D      5
#define MOTEUR_D_PIN_PWM    3

Plateforme plateforme(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);


void setup() 
{
  plateforme.setup();

  plateforme.setup();

  plateforme.avance(50);
  delay(5000);

  plateforme.recule(50);
  delay(5000);

  plateforme.tournerAGauche(50);
  delay(5000);

  plateforme.tournerADroite(50);
  delay(5000);

  plateforme.stop();

}

void loop()
{
  
}

