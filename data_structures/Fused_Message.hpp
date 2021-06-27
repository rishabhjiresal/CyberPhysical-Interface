#ifndef FUSED_MESSAGE_HPP
#define FUSED_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Fused_Message{
  Fused_Message(){}
  Fused_Message(string i_type, double i_value)
   :type(i_type), value(i_value){}

  	string   type;
  	double  value;
};


struct Vector_Fused_Message {
  Vector_Fused_Message() {}
  Vector_Fused_Message(vector<Fused_Message> i_message) : message(i_message) {}

  vector<Fused_Message> message;
};

istream& operator>> (istream& is, Fused_Message& msg);

ostream& operator<<(ostream& os, const Fused_Message& msg);

ostream& operator<<(ostream& os, const Vector_Fused_Message& msg);

#endif 