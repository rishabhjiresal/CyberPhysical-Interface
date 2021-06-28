#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Actuator_Message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Actuator_Message& msg) {
  os << msg.name << " " << msg.value;
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, Actuator_Message& msg) {
  is >> msg.name;
  is >> msg.value;
  return is;
}