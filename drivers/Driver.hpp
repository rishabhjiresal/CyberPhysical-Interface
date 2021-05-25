#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Sensor_Libraries/DHT11.h"
#include "Sensor_Libraries/MQ2.h"
#include "Sensor_Libraries/MS5611.h"
#include "Sensor_Libraries/TextLCD.h"
#include "Sensor_Libraries/VEML7700.h"

namespace drivers {
  class TEMPHUMIDITY_DRIVER {
  private:
    Dht11 dht11;
  public:
    TEMPHUMIDITY_DRIVER(PinName TempPin) : dht11(TempPin) {

    }

    void TempHumidity(int &temp, int &hum) {
        dht11.read();
        temp = dht11.getCelsius();
        hum = dht11.getHumidity();
    }
  };
}
#endif
