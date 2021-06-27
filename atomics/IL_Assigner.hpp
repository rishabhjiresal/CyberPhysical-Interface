#ifndef IL_ASSIGNER_HPP
#define IL_ASSIGNER_HPP

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
#include "../data_structures/Fused_Message.hpp"

#include "../drivers/Sensor_Fusion_Algorithms/Algorithm.h"


using namespace cadmium;
using namespace std;

struct IL_Assigner_defs
{
  struct in : public in_port<Vector_Fused_Message> {};

  struct out : public out_port<Vector_Assigner_Message> {};
};

template<typename TIME>
class IL_Assigner
{
  using defs=IL_Assigner_defs;
  	public:
      IL_Assigner() noexcept {
        
      }

      struct state_type {
        Vector_Fused_Message from_fusion;
        Vector_Assigner_Message outputData;
        bool active;
        }; state_type state;

        using input_ports=std::tuple<typename defs::in>;
      	using output_ports=std::tuple<typename defs::out>;


        void internal_transition (){
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
          state.from_fusion = get_messages<typename IL_Assigner_defs::in>(mbs)[0];
          state.outputData = add_values_to_assigner_message(state.from_fusion.message);
          state.from_fusion.message.clear();
          state.from_fusion.message.shrink_to_fit();
          for(int i=0; i<state.outputData.message.size(); i++) {
            cout<< state.outputData.message[i] << endl;
            }
        // #ifdef RT_DEVS
        // StoreData(state.outputData);
        // #endif
      		state.active = true;
      	}

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;
          get_messages<typename defs::out>(bags).push_back(state.outputData);  
        return bags;
      }

      TIME time_advance() const {
        if(state.active) {
          return TIME("00:00:01");
        }
        return std::numeric_limits<TIME>::infinity();
      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename IL_Assigner<TIME>::state_type& i) {
                 os << "Sent Data by Assigner: " ;
                 return os;
               }
      };


#endif