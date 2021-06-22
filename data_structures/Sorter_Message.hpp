#ifndef SORTER_MESSAGE_HPP
#define SORTER_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Sorter_Message{
  Sorter_Message(){}
  Sorter_Message(int i_number, string i_sensor_type, double i_value)
   :number(i_number), sensor_type(i_sensor_type), value(i_value){}

    int number;
  	string   sensor_type;
  	double  value;
};

istream& operator>> (istream& is, Sorter_Message& msg);

ostream& operator<<(ostream& os, const Sorter_Message& msg);


#endif 