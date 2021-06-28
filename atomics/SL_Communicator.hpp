#ifndef SL_COMMUNICATOR_HPP
#define SL_COMMUNICATOR_HPP

#include <stdio.h>
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <limits>
#include <math.h>
#include <assert.h>
#include <memory>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <limits>
#include <random>

#include "../data_structures/Assigner_Message.hpp"
#include "../data_structures/Actuator_Message.hpp"
#include "../data_structures/Command.hpp"

using namespace cadmium;
using namespace std;


struct SL_Communicator_defs
{
   struct from_informational_layer : public in_port<Vector_Assigner_Message> {};
   struct command_line_rx_status : public in_port<Command_Rx_Status> {};
   struct command_line_rx_typeandtime : public in_port<Command_Rx_TypeAndTime> {};
   struct command_line_rx_message : public in_port<Command_Rx_Actuator_Message> {};

   struct actuator_data_out : public out_port<Actuator_Message> {};
   struct sensor_data_out : public out_port<Assigner_Message> {};
   struct command_line_tx : public out_port<Command_Tx> {};
};

template<typename TIME>
class SL_Communicator
{
  using defs=SL_Communicator_defs;
  	public:

      SL_Communicator() noexcept {
        state.busy = false;
        state.active = false;
        state.woke_up = false;
        state.send_current_data = false;
      }

      struct state_type {
        Vector_Assigner_Message from_assigner;
        Assigner_Message send_to_CS;
        Command_Tx tx;
        Actuator_Message to_IL;
        bool status_check;
        bool woke_up;
        bool busy;
        bool ready_to_send;
        bool send_actuator_command;
        bool send_current_data;
        bool active;
        }; state_type state;

        using input_ports=std::tuple<typename defs::from_informational_layer, typename defs::command_line_rx_status, typename defs::command_line_rx_message, typename defs::command_line_rx_typeandtime>;
      	using output_ports=std::tuple<typename defs::actuator_data_out, typename defs::sensor_data_out, typename defs::command_line_tx>;

        void internal_transition (){
          state.busy = false;
          state.send_current_data = false;
          state.ready_to_send = false;
          state.send_actuator_command = false;
          state.status_check = false;
          state.to_IL.name = "\0";
          state.to_IL.value = 0;
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
           vector<Command_Rx_TypeAndTime> typeandtime;
           vector<Command_Rx_Status> status;
           vector<Command_Rx_Actuator_Message> message;
           status = get_messages<typename SL_Communicator_defs::command_line_rx_status>(mbs);
           typeandtime = get_messages<typename SL_Communicator_defs::command_line_rx_typeandtime>(mbs);
           message = get_messages<typename SL_Communicator_defs::command_line_rx_message>(mbs);
          if(status.size() >= 1){
          if(status[0].status_check == 1 && state.status_check == false && state.woke_up == false) {
            if(!state.busy) {state.status_check = true;}
            state.tx.status_check_response = 1;
            state.tx.type_and_time_request = 1;
            state.woke_up = true;
          }
          }
          
          if(typeandtime.size() >= 1){
          if(!typeandtime[0].type.empty() && !typeandtime[0].time_stamp.empty() && state.woke_up == true) {
            if(!typeandtime[0].time_stamp.compare("CUR")) {
              state.send_current_data = true;
              state.from_assigner = get_messages<typename SL_Communicator_defs::from_informational_layer>(mbs)[0];
            }
            else {
            ReadData(typeandtime[0].time_stamp, typeandtime[0].type, state.send_to_CS); 
            }
            state.busy = true;
            state.ready_to_send = true;
          }
          }

          if(message.size()>=1) {
          if(!message[0].message.name.empty() && state.woke_up == true) {
            state.to_IL.name = message[0].message.name;
            state.to_IL.value = message[0].message.value;
            state.send_actuator_command = true;
            state.busy = true;
          }
          }
      	 	state.active = true;
      	 }

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;

        if(state.woke_up == true && !state.busy) {
          get_messages<typename defs::command_line_tx>(bags).push_back(state.tx);
        }
        if(state.woke_up == true && state.ready_to_send == true) {
          get_messages<typename defs::sensor_data_out>(bags).push_back(state.send_to_CS);
        }
        if(state.woke_up == true && state.send_actuator_command == true) {
          get_messages<typename defs::actuator_data_out>(bags).push_back(state.to_IL);
        }
        if(state.woke_up == true && state.send_current_data == true) {
           for(auto i=0;i<state.from_assigner.message.size();++i){
              get_messages<typename defs::sensor_data_out>(bags).push_back(state.from_assigner.message[i]);
           }
       }
        return bags;
      }

      TIME time_advance() const {
        if(state.active && state.woke_up) {
          return TIME("00:00:00");
        }
        if(state.active && state.woke_up && state.ready_to_send){
          return TIME("00:00:02");
        }
        if(state.active && state.woke_up && state.send_actuator_command) {
          return TIME("00:00:01");
        }
        if(state.active && state.woke_up && state.send_current_data) {
          return TIME("00:00:01");
        }
        return std::numeric_limits<TIME>::infinity();

      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename SL_Communicator<TIME>::state_type& i) {
                 os << "Sent data to fusion " ;
                 return os;
               }
      };
#endif