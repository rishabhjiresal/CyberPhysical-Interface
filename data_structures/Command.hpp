#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "../data_structures/Actuator_Message.hpp"

using namespace std;

struct Command_Rx_Status{
  Command_Rx_Status(){}
  Command_Rx_Status(int i_status_check) : status_check(i_status_check) {}
    int status_check;
};

struct Command_Rx_TypeAndTime{
    Command_Rx_TypeAndTime(){}
    Command_Rx_TypeAndTime(string i_type, string i_time_stamp) : type(i_type), time_stamp(i_time_stamp) {}
    string type;
    string time_stamp;
};

struct Command_Rx_Actuator_Message { 
    Command_Rx_Actuator_Message(){}
    Command_Rx_Actuator_Message(Actuator_Message i_message) : message(i_message) {}
    Actuator_Message message;
};

struct Command_Tx{
  Command_Tx(){}
  Command_Tx(int i_status_check_response, int i_type_and_time_request )
   :status_check_response(i_status_check_response), type_and_time_request(i_type_and_time_request){}

    int status_check_response;
    int type_and_time_request;

};


ostream& operator<<(ostream& os, const Command_Rx_Status& msg);
ostream& operator<<(ostream& os, const Command_Rx_TypeAndTime& msg);
ostream& operator<<(ostream& os, const Command_Rx_Actuator_Message& msg);


ostream& operator<<(ostream& os, const Command_Tx& msg);

istream& operator>> (istream& is, Command_Rx_Status& msg);
istream& operator>> (istream& is, Command_Rx_TypeAndTime& msg);
istream& operator>> (istream& is, Command_Rx_Actuator_Message& msg);

#endif 