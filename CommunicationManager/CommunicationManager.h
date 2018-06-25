#ifndef CommunicationManager_h
#define CommunicationManager_h

#include <Arduino.h>
#include <SoftwareSerial.h>



class CommunicationManager
{
private:
    SoftwareSerial m_bluetooth;

    //Utilisé pour lire le message via bluetooth
    String messageLu;
    bool messageFini;

    //Utilisé pour traiter le message une fois lu 
    int m_typeMessage;
    String m_corpsMessage;

    String m_tableauCorpsDonnees[10];

    //données qui seront fourni à l'arduino
    float m_latitude;
    float m_longitude;
    int m_mode;
    // référence au type 8 du protocole
    String m_mouvement;

    //même répartition pour les méthodes

    bool debutMessage(char charLu);
    bool finMessage(char charLu);

    //fonctions utiles pour le traitement
    int stringToInt(String value);

    void recupTypeCorps();

public:
    CommunicationManager(int pinTX, int pinRX);

    void setup(int baud);
    void listen();

    void recupereMessage();
    void visualiseMessage();

    int getType();

    void analyseMessage();
    bool messageAnalyse();
    void traiteDonnees();
    void setMessage(String messageTest);

    //passe du corps de message aux données
    //type 1
    void recupereLatitude();
    void recupereLongitude();
    //type 5
    void recupereMode();
    //type 8
    void recupereMouvement();

    float getLatitude();
    float getLongitude();
    int getMode();
    String getMouvement();

    void sendData(unsigned int type, String corps);
    void sendDistance(String distance);
    void sendDistance(int distance);


};

#endif