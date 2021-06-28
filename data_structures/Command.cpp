#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Command.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Command_Rx_Status& msg) {
  os << msg.status_check;
  return os;
}
ostream& operator<<(ostream& os, const Command_Rx_Actuator_Message& msg) {
  os  << msg.message;
  return os;
}
ostream& operator<<(ostream& os, const Command_Rx_TypeAndTime& msg) {
  os << msg.type << " " << msg.time_stamp;
  return os;
}

ostream& operator<<(ostream& os, const Command_Tx& msg) {
  os << msg.status_check_response <<  " " << msg.type_and_time_request;
  return os;
}

istream& operator>> (istream& is, Command_Rx_Status& msg) {
  is >> msg.status_check;
  return is;
}

istream& operator>> (istream& is, Command_Rx_Actuator_Message& msg) {
  is >> msg.message;
  return is;
}
istream& operator>> (istream& is, Command_Rx_TypeAndTime& msg) {
  is >> msg.type;
  is >> msg.time_stamp;
  return is;
}