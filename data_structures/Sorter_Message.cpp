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

ostream& operator<<(ostream& os, const Vector_Vector_Sorter_Message& msg) {
    for(int i=0; i<msg.message.size(); i++) { // Ensure that you don't access any elements that don't exist
		for(int p=0; p<msg.message[i].size(); p++) { // You may not have had 10 in here before, only go to size().
		os << msg.message[i][p];
    if(p != msg.message[i].size()-1) {
    os << ", ";
    }
    }
    if(i != msg.message.size()-1) {
    os << ", ";
    }
    else {
      os<<" ";
    }
    }
    return os;
}