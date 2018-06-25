
#include <PlateformeIntelligente.h>
#include <GPS.h>
#include <MagneticRead.h>
#include <CommunicationManager.h>
#include <Coordonnee.h>
#include <Utils.h>

#define MOTEUR_G_PIN_G      9
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      10
#define MOTEUR_G_PIN_PWM    11
#define MOTEUR_D_PIN_G      4
#define MOTEUR_D_PIN_D      5
#define MOTEUR_D_PIN_PWM    3

MagneticRead mag;
PlateformeIntelligente robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);
CommunicationManager communicationManager(2, 12);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.setup();
  mag.setup();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //va à l'angle 0 (au nord)
  robot.rejoindreUtilisateur(mag.getHeadingRad(), 180*DEG_TO_RAD, 12);
}

