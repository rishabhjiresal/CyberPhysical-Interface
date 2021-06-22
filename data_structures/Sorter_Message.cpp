#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Sorter_Message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Sorter_Message& msg) {
  os << msg.number << " "<< msg.sensor_type << " " << msg.value;
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, Sorter_Message& msg) {
  is >> msg.number;
  is >> msg.sensor_type;
  is >> msg.value;
  return is;
}