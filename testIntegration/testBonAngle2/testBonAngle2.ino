
#include <PlateformeIntelligente.h>
#include <GPS.h>
#include <MagneticRead.h>
#include <CommunicationManager.h>
#include <Coordonnee.h>
#include <Utils.h>

#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

MagneticRead mag;
PlateformeIntelligente robot(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.setup();
  mag.setup();

//doees not work if not in the end
  delay(20000);

  //va à l'angle 0 (au nord)
  robot.rejoindreUtilisateur(mag.getHeadingRad(), 0, 1);
  delay(20000);

  //va a l'angle 180 (au sud)
  robot.rejoindreUtilisateur(mag.getHeadingRad(), 180*DEG_TO_RAD, 1);
  delay(20000);

  //va a l'angle 90 (à l'est)
  robot.rejoindreUtilisateur(mag.getHeadingRad(), 90*DEG_TO_RAD, 1);
  delay(20000);

  //va a l'angle 270 (à l'ouest)
  robot.rejoindreUtilisateur(mag.getHeadingRad(), 270*DEG_TO_RAD, 1);
  delay(20000);
  
}

void loop() {
  // put your main code here, to run repeatedly
  
  

}

