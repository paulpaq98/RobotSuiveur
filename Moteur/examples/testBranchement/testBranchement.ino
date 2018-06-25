#include <Moteur.h>

#define PIN_GAUCHE 5
#define PIN_DROITE 4
#define PIN_PWM 3

Moteur moteur(PIN_GAUCHE, PIN_DROITE, PIN_PWM);

void setup() {
  Serial.begin(9600);
  moteur.setup();
  
  moteur.tourneVersGauche(180);
  Serial.println("le moteur devrait tourner vers la gauche");
  delay(5000);
  
  moteur.tourneVersDroite(180);
  Serial.println("le moteur devrait tourner vers la droite");
  delay(5000);
  
  moteur.stop();
  Serial.println("le moteur devrait s'arrêter");
  delay(5000);
}

void loop() {

}
