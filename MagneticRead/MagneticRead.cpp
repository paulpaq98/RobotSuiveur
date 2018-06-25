#include "MagneticRead.h"

float offset = -190*DEG_TO_RAD;



float valMaxRad = 2*M_PI;
float valMinRad = 0;

MagneticRead::MagneticRead() 
{
    mag = Adafruit_HMC5883_Unified(12345);
}

void MagneticRead::setup()
{
    mag.begin();
}

float MagneticRead::getHeadingRad() 
{

    sensors_event_t event;
    mag.getEvent(&event);
  
    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    double heading  = atan2(event.magnetic.y, event.magnetic.x);
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = -0.01745329252;

    heading += declinationAngle;
    Serial.print("heading : ");
    Serial.print(heading*RAD_TO_DEG);
    heading += M_PI;
    Serial.print(" normalisé :");
    Serial.print(heading*RAD_TO_DEG);
    //heading = ((heading-valMinRad)/(valMaxRad-valMinRad))*(M_PI*2);
    //Serial.print(" normalisé :");
    //Serial.print(heading*RAD_TO_DEG);
    heading += offset;
    Serial.print("  + offset :");
    Serial.print(heading*RAD_TO_DEG);
    heading = Utils::nbModulo2PI(heading);
    Serial.print("  modulo :");
    Serial.print(heading*RAD_TO_DEG);
    Serial.print("  heading final en radians : ");
    return heading;
}

float MagneticRead::getHeadingDeg() 
{
    float heading = getHeadingRad()*RAD_TO_DEG;
    return heading;
}
