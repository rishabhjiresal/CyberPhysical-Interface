#ifndef ASSIGNER_MESSAGE_HPP
#define ASSIGNER_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Assigner_Message{
  Assigner_Message(){}
  Assigner_Message(string i_type, double i_value, string i_units)
   :type(i_type), value(i_value), units(i_units){}
    
  	string   type;
  	double  value;
    string units;
};

struct Vector_Assigner_Message {
  Vector_Assigner_Message() {}
  Vector_Assigner_Message(vector<Assigner_Message> i_message) : message(i_message) {}

  vector<Assigner_Message> message;
};


ostream& operator<<(ostream& os, const Assigner_Message& msg);

ostream& operator<<(ostream& os, const Vector_Assigner_Message& msg);


#endif 