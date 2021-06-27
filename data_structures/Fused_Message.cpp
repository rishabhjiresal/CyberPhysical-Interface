#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Fused_Message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Fused_Message& msg) {
  os << msg.type << " " << msg.value;
  return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, Fused_Message& msg) {
  is >> msg.type;
  is >> msg.value;
  return is;
}

ostream& operator<<(ostream& os, const Vector_Fused_Message& msg) {
  for(auto i=0;i<msg.message.size();++i){
    os<<msg.message[i].type << " " << msg.message[i].value;
    if(i != msg.message.size()-1) {
      os << ", ";
    }
    else {
      os<<" ";
    }
  }
  return os;
}