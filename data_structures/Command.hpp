#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "../data_structures/Actuator_Message.hpp"

using namespace std;

struct Command_Rx{
  Command_Rx(){}
  Command_Rx(int i_status_check, string i_type, string i_time_stamp, Actuator_Message i_message)
   :status_check(i_status_check), type(i_type), time_stamp(i_time_stamp), message(i_message) {}

    int status_check;
    string type;
    string time_stamp;
    Actuator_Message message;

};

struct Command_Tx{
  Command_Tx(){}
  Command_Tx(int i_status_check_response, int i_type_and_time_request )
   :status_check_response(i_status_check_response), type_and_time_request(i_type_and_time_request){}

    int status_check_response;
    int type_and_time_request;

};


ostream& operator<<(ostream& os, const Command_Rx& msg);


#endif 