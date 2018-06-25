#ifndef GPS_h
#define GPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include "Utils.h"

class GPS
{
private:

    //utilise pour stocker le message dans la methoderecupDonnesBrut
    String m_recupDonneesBrut;
    bool lectureDonneesBrutFini;

    String m_recupDonnees;
    String m_donnees;
    String m_donneesUtiles;
    bool m_recupDonneesTerminee;
    unsigned int m_chercheIndex;
    bool m_finLectureDonnees;

    bool m_donneesUtilesRecuperees;
    String m_sauve;

    String m_donneesValides;

    bool valueRetrieved;
    bool m_gpsConnected;
    bool m_gpsConnectedOnce;

    const char message[6];
    int lenDebutMessage = 6;

    int lastNbCharLu;

    SoftwareSerial m_gps;

    //offset sur les valeurs de latitude et longitude reçu
    float m_offsetLatitude = 0.14287069091 -0.00028610 +0.0005012;
    float m_offsetLongitude = -0.22775244141 + 0.45532226-0.000036187;

    float m_latPlateformeDeg;
    float m_lonPlateformeDeg;

    bool separeDonneesRecu(String recupDonnees, String* dataReadable);


public:
    //public pour test, mettre private après 
    // récupère la ligne voulu
    void recupDonnees();
    void traiteDonnees();

    GPS(int pinTX, int pinRX);

    void setup();
    void listen();

    /* 
    * Les méthodes suivantes sont utilisées pour visualiser ce qu'envoie le GPS
    * Ne pas utiliser d'autres méthodes simultanément !!
    */
    void recupDonneesBrut();
    bool lectureTermine();
    String getDonneesBrut();
    //fin des méthodes à utiliser seules

    //vaut faux si le gps n'est pas appairé
    bool recuperationDonneesPossible();
    bool connected();
    bool connectedOnce();
    void recupEtTraiteDonnees();

    String messageLu();

    void retrieveData();

    //getter
    float getLatitudeDeg();
    float getLongitudeDeg();
    float getLatitudeRad();
    float getLongitudeRad();

};

#endif
