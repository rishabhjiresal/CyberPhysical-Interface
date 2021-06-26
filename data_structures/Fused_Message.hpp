#ifndef FUSED_MESSAGE_HPP
#define FUSED_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Fused_Message{
  Fused_Message(){}
  Fused_Message(string i_type, double i_value)
   :type(i_type), value(i_value){}

  	string   type;
  	double  value;
};

istream& operator>> (istream& is, Fused_Message& msg);

ostream& operator<<(ostream& os, const Fused_Message& msg);


#endif 