#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Command.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const Command_Rx& msg) {
  os << msg.status_check << " " << msg.type << " " << msg.time_stamp << " " << msg.message;
  return os;
}

ostream& operator<<(ostream& os, const Command_Tx& msg) {
  os << msg.status_check_response <<  " " << msg.type_and_time_request;
  return os;
}
