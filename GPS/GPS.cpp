#include "GPS.h"

GPS::GPS(int pinTX, int pinRX) :message {'$', 'G', 'P', 'G', 'L', 'L'}, m_donneesUtilesRecuperees(false), valueRetrieved(false),
                            lectureDonneesBrutFini(false), m_recupDonneesBrut(""), m_finLectureDonnees(false),
                            m_gpsConnected(false), m_gpsConnectedOnce(false),
                            m_gps(pinTX, pinRX), m_latPlateformeDeg(-1), m_lonPlateformeDeg(-1)
{

}

void GPS::setup() {
  m_gps.begin(9600);
}

void GPS::listen() {
  m_gps.listen();
}

/* 
 * Les méthodes suivantes sont utilisées pour visualiser ce qu'envoie le GPS
 * Ne pas utiliser d'autres méthodes simultanément !!
 */
void GPS::recupDonneesBrut()
{
  if(m_gps.available())
  {
    char value = m_gps.read();
    m_recupDonneesBrut += value;
  }
  else
  {
    if (m_recupDonneesBrut != "")
    {
      m_recupDonneesBrut = "";
    }
  }
}

bool GPS::lectureTermine()
{
  return lectureDonneesBrutFini;
}

String GPS::getDonneesBrut()
{
  return m_recupDonneesBrut;
}
// fin methodes à utiliser seules

void GPS::recupDonnees()
{
  if(m_gps.available())
  {
    char value = m_gps.read();
    //si on a pas trouvé le message dans la chaine, on compare jusqu'à la trouver
    if (m_chercheIndex < lenDebutMessage)
    {
      if (value == message[m_chercheIndex])
      {
        m_chercheIndex += 1;
        m_donneesUtiles += value;
      }
      else
      {
        m_chercheIndex = 0;
        m_donneesUtiles = "";
      }
    }
    //sinon on vérifie qu'on a pas atteint la fin des donnees que l'on cherche (fini par \n), et on sauvegarde ce qui nous intéresse
    else
    {
      if (value == '\n')
      {
        m_finLectureDonnees = true;
      }
      if (!m_finLectureDonnees)
      {
        m_donneesUtiles += value;
      }
    }
    
  }
  else
  {
    if (m_finLectureDonnees)
    {
      m_sauve = m_donneesUtiles;
      m_donneesUtilesRecuperees = true;
      m_chercheIndex = 0;
      m_finLectureDonnees = false;
      m_donneesUtiles = "";
    }
  }
}

String GPS::messageLu()
{
  return m_sauve;
}

bool GPS::connectedOnce()
{
  return m_gpsConnectedOnce;
}

bool GPS::connected()
{
  return m_gpsConnected;
}

bool GPS::recuperationDonneesPossible()
{
  return valueRetrieved;
}

float GPS::getLatitudeDeg()
{
  return m_latPlateformeDeg;
}

float GPS::getLongitudeDeg()
{
  return m_lonPlateformeDeg;
}

float GPS::getLatitudeRad()
{
    return getLatitudeDeg()*DEG_TO_RAD;
}

float GPS::getLongitudeRad()
{
    return getLongitudeDeg()*DEG_TO_RAD;
}


//return true if the data are correct, false if the gps is not appaired
bool GPS::separeDonneesRecu(String recupDonnees, String* dataReadable) {
  unsigned int field = 0;
  for (unsigned int i =0 ; i < recupDonnees.length();i++) {
      if (recupDonnees[i] == ',') {
        field += 1;
      }
      else {
        dataReadable[field] += recupDonnees[i];
      }
  }
  return(true);
}

void GPS::retrieveData()
{
  if (m_donneesUtilesRecuperees)
  {
    unsigned int longueurDonnees[8];
    String dataReadable[10];

    separeDonneesRecu(m_sauve, dataReadable);

    m_latPlateformeDeg = dataReadable[1].toFloat()/100+m_offsetLatitude;
    m_lonPlateformeDeg = dataReadable[3].toFloat()/100+m_offsetLongitude;
    //on prend l'opposé si on est à l'ouest
    if (dataReadable[4] == "W")
    {
      m_lonPlateformeDeg = Utils::nbModuloN(-1*m_lonPlateformeDeg, 360);
    }
    
    m_donneesValides = dataReadable[6];
    m_donneesUtilesRecuperees = false;

    if (m_donneesValides == "A")
    {
      m_gpsConnected = true;
      m_gpsConnectedOnce = true;
    }
    else if (m_donneesValides == "V")
    {
      m_gpsConnected = false;
    }
    valueRetrieved = true;
  }
}
