#ifndef IL_OPCOMMANDER_HPP
#define IL_OPCOMMANDER_HPP

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


using namespace cadmium;
using namespace std;



#include "../data_structures/Actuator_Message.hpp"

#include "../drivers/Rearrange.h"
using namespace cadmium;
using namespace std;


struct IL_OPCommander_defs
{
  struct in : public in_port<Actuator_Message>{};

  struct outName : public out_port<string> {};
  struct outValue : public out_port<double> {};
};

template<typename TIME>
class IL_OPCommander
{
  using defs=IL_OPCommander_defs;
  	public:


      IL_OPCommander() noexcept {
        state.active = false;
      }

      struct state_type {
        bool active;
        string name;
        double value;
        }; state_type state;

        using input_ports=std::tuple<typename defs::in>;
      	using output_ports=std::tuple<typename defs::outName, typename defs::outValue>;

        void internal_transition (){
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
          vector<Actuator_Message> temp;
          temp = get_messages<typename IL_OPCommander_defs::in>(mbs);
          state.name = temp[0].name;
          state.value = temp[0].value;
      		state.active = true;
      	}

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;
          get_messages<typename defs::outName>(bags).push_back(state.name);
           get_messages<typename defs::outValue>(bags).push_back(state.value);
        return bags;
      }

      TIME time_advance() const {
        if(state.active) {
          return TIME("00:00:00");
        }
        return std::numeric_limits<TIME>::infinity();

      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename IL_OPCommander<TIME>::state_type& i) {
                 os << "Sent data to CPL Layer " ;
                 return os;
               }
      };
#endif