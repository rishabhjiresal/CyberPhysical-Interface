#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Assigner_Message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Assigner_Message& msg) {
  os << msg.type << " " << msg.value << " "<<msg.units;
  return os;
}

ostream& operator<<(ostream& os, const Vector_Assigner_Message& msg) {
  for(auto i=0;i<msg.message.size();++i){
    os<<msg.message[i].type << " " << msg.message[i].value<< " " << msg.message[i].units ;
    if(i != msg.message.size()-1) {
      os << ", ";
    }
    else {
      os<<" ";
    }
  }
  return os;
}
