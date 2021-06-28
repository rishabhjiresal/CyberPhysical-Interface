#ifndef ACTUATOR_MESSAGE_HPP
#define ACTUATOR_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Actuator_Message{
  Actuator_Message(){}
  Actuator_Message(string i_name, double i_value)
   :name(i_name), value(i_value){}

  	string   name;
  	double  value;
};

istream& operator>> (istream& is, Actuator_Message& msg);

ostream& operator<<(ostream& os, const Actuator_Message& msg);


#endif 