#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Sensor_Libraries/DHT11.h"
#include "Sensor_Libraries/CO2.h"
#include "Sensor_Libraries/MS5611.h"
#include "Sensor_Libraries/TextLCD.h"
#include "Sensor_Libraries/VEML7700.h"

namespace drivers {
  class TEMPERATURE_HUMIDITY {
  private:
    Dht11 dht11;
  public:
    TEMPERATURE_HUMIDITY(PinName TempPin) : dht11(TempPin) {

    }

    void Temp(double &temp) {
        dht11.read();
        temp = dht11.getCelsius();
    }

    void Humidity(double &hum) {
      dht11.read();
      hum = dht11.getHumidity();
    }
  };

  class CO2_Driver {
    private:
    CO2 co2;
    float CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};
    public:
      CO2_Driver(PinName CO2Pin) : co2(CO2Pin) {

      }

      void getCO2LevelsinPPM(int &level) {
        int percent;
        float volts;
        volts = co2.MGRead();
             //cout<<"SEN0159 "<<volts<<"V  "<<endl;
             percent = co2.MGGetPercentage(volts,CO2Curve);
             if (percent == -1) {
               level = 350;
              } else {
                level = percent;
              }
              }
  };
}
#endif
