#include "Coordonnee.h"

CoordonneeGPS::CoordonneeGPS()
{
  m_latRad = -1;
  m_lonRad = -1;
}

CoordonneeGPS::CoordonneeGPS(float latRad, float lonRad, bool argInRad)
{
  setLatitude(latRad, argInRad);
  setLongitude(lonRad, argInRad);
}

float CoordonneeGPS::getLatRad() const
{
  return m_latRad;
}

float CoordonneeGPS::getLonRad() const
{
  return m_lonRad;
}

float CoordonneeGPS::getLatDeg() const
{
  return m_latRad*RAD_TO_DEG;
}

float CoordonneeGPS::getLonDeg() const
{
  return m_lonRad*RAD_TO_DEG;
}

void CoordonneeGPS::setLatitude(float latRad, bool argInRad)
{
  if (!argInRad)
  {
    latRad = latRad*DEG_TO_RAD;
  }

  m_latRad = Utils::nbModulo2PI(latRad);
}

void CoordonneeGPS::setLongitude(float lonRad, bool argInRad)
{
  if (!argInRad)
  {
    lonRad = lonRad*DEG_TO_RAD;
  }

  m_lonRad = Utils::nbModulo2PI(lonRad);
}

bool CoordonneeGPS::initSuccess()
{
  return (m_latRad >= 0 && m_lonRad >= 0);
}

float CoordonneeGPS::longueurArcCercleTerrestre(CoordonneeGPS const& c2)
{
  float result = -1;
  if (initSuccess())
  {
    float lat1 = this->m_latRad;
    float lat2 = c2.m_latRad;
    float diffLat = c2.m_latRad-this->m_latRad;
    float diffLon = c2.m_lonRad-this->m_lonRad;

    float x = sin(diffLat/2) * sin(diffLat/2) + cos(lat1) * cos(lat2) * sin(diffLon/2) * sin(diffLon/2);
    float y = 2 * atan2(sqrt(x), sqrt(1-x));

    result = y * Utils::rayonTerrestre;
  }

  return result;
}

float CoordonneeGPS::geoBearing(CoordonneeGPS const& b) 
{
  float result = -1;
  Serial.print("latitude dans geobearing : ");
  Serial.println(this->getLatDeg(), 15);
  Serial.print("longitude dans geobearing : ");
  Serial.println(this->getLonDeg(), 15);
  
  if (initSuccess())
  {
    float y = sin(b.m_lonRad-this->m_lonRad) * cos(b.m_latRad);
    float x = cos(this->m_latRad)*sin(b.m_latRad) - sin(this->m_latRad)*cos(b.m_latRad)*cos(b.m_lonRad-this->m_lonRad);
    result = atan2(y, x);
  }

  return Utils::nbModulo2PI(result);
}