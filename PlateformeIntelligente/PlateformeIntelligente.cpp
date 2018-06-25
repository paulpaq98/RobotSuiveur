#include "PlateformeIntelligente.h"

int PlateformeIntelligente::PWMMaxEnTournant = 150;
int PlateformeIntelligente::PWMMinEnTournant = 40;

PlateformeIntelligente::PlateformeIntelligente(int pinGaucheMGauche, int pinDroiteMGauche, int pinPWMMGauche, int pinGaucheMDroite, int pinDroiteMDroite, int pinPWMMDroite) : Plateforme(pinGaucheMGauche, pinDroiteMGauche, pinPWMMGauche, pinGaucheMDroite, pinDroiteMDroite, pinPWMMDroite)
{

}

//cette fonction ne doit être lancé que après avoir trouvé le bon angle
void PlateformeIntelligente::avancerJusque(int distance)
{
  if (distance < 0)
  {
    stop();
  }
  if (distance>50)// (ouais mais une fonction continue c'est mieux) l'idée ici est d' adapter la vitesse à la distance à l'utilisateur (imagine une voiture qui roule à 100 et qui décide de s'arreter à un feu alors qu'il est à 10 metres de celui ci
  {
    avance(100);
  }
  else if (50 > distance && distance>10)
  {
    avance(80);
  }
  else
  {
    stop();
  }
}

//argument en radian
void PlateformeIntelligente::tournerJusque(double angle,double angleCible, int distance)
{
  Serial.print("angle actuel : ");
  Serial.print(angle*RAD_TO_DEG);
  Serial.print(" angle ciblé : ");
  Serial.print(angleCible*RAD_TO_DEG);
  double angleBis= Utils::nbModuloN(angleCible - angle, 2*M_PI)*RAD_TO_DEG;
  Serial.print(" angle calculé : ");
  Serial.println(angleBis);
  if (15 < angleBis && angleBis <= 180) //tourner à droite // ici on dit que pour 2 degrés on accepte d'aller tout droit
  {
    tournerADroite(80);
  }
  else if (180 < angleBis && angleBis <= 345) //tourner à gauche
  {
    tournerAGauche(80);
  }
  else
  {
      avancerJusque(distance);
  }
}

void PlateformeIntelligente::adapterVitesse(long distanceObjet)
{

}

void PlateformeIntelligente::rejoindreUtilisateur(double anglePlateformeAvecNord, double angleCible, int distance)
{
    tournerJusque(anglePlateformeAvecNord, angleCible, distance);
}