#ifndef SENSOR_MESSAGE_HPP
#define SENSOR_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Sensor_Message{
  Sensor_Message(){}
  Sensor_Message(string i_name, double i_value)
   :name(i_name), value(i_value){}

  	string   name;
  	double  value;
};

istream& operator>> (istream& is, Sensor_Message& msg);

ostream& operator<<(ostream& os, const Sensor_Message& msg);


#endif 