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
   struct command_line_rx : public in_port<Command_Rx> {};

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
      }

      struct state_type {
        Vector_Assigner_Message from_assigner;
        Command_Rx rx;
        Assigner_Message send_to_CS;
        Command_Tx tx;
        Actuator_Message to_IL;
        bool status_check;
        bool woke_up;
        bool busy;
        bool ready_to_send;
        bool send_actuator_command;
        bool send_current_data;
        }; state_type state;

        using input_ports=std::tuple<typename defs::from_data_storage, typename defs::from_informational_layer, typename defs::command_line_rx>;
      	using output_ports=std::tuple<typename defs::actuator_data_out, typename defs::sensor_data_out, typename defs::command_line_tx, typename defs::to_data_storage>;

        void internal_transition (){
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
          state.from_assigner = get_messages<typename SL_Communicator_defs::from_informational_layer>(mbs)[0];
          state.rx = get_messages<typename SL_Communicator_defs::command_line_rx>(mbs);
          if(state.rx[0].status_check == 1 && state.status_check == false) {
            if(!state.busy) {state.status_check = true;}
            state.tx.status_check_response = 1;
            state.tx.type_and_time_request = 1;
            state.woke_up = true;
          }
          if(!state.rx[0].type.empty() && !state.rx[0].time_stamp.empty() && state.woke_up == true) {
            if(state.rx[0].time_stamp.compare("CUR")) {
              state.send_current_data = true;
            }
            else {
            ReadData(state.rx[0].time_stamp, state.rx[0].type, state.send_to_CS); 
            }
            state.busy = true;
            state.ready_to_send = true;
          }
          if(!state.rx[0].message.name.empty() && state.woke_up == true) {
            state.to_IL.name = state.rx[0].message.name;
            state.to_IL.value = state.rx[0].message.value;
            state.send_actuator_command = true;
          }
      		state.active = true;
      	}

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;

        if(state.woke_up == true) {
          get_messages<typename defs::command_line_tx>(bags).push_back(state.tx);
        }
        if(state.woke_up == true && state.ready_to_send == true) {
          get_messages<typename defs::sensor_data_out>(bags).push_back(state.send_to_CS);
        }
        if(state.woke_up == true && state.send_actuator_command == true) {
          get_messages<typename defs::actuator_data_out>(bags).push_back(state.to_IL);
        }
        if(state.woke_up == true && state.send_current_data == true) {
           for(auto i=0;i<state.from_assigner.size();++i){
              get_messages<typename defs::sensor_data_out>(bags).push_back(state.from_assigner[i]);
           }
        }
        return bags;
      }

      TIME time_advance() const {
        if(state.active) {
          return TIME("00:00:02");
        }
        return std::numeric_limits<TIME>::infinity();

      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename SL_Communicator<TIME>::state_type& i) {
                 os << "Sent data to fusion " ;
                 return os;
               }
      };
#endif