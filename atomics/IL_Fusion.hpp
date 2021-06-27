#ifndef IL_FUSION_HPP
#define IL_FUSION_HPP

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

#include "../data_structures/Sorter_Message.hpp"
#include "../data_structures/Fused_Message.hpp"

#include "../drivers/Sensor_Fusion_Algorithms/Algorithm.h"


using namespace cadmium;
using namespace std;


struct IL_Fusion_defs
{
  struct in : public in_port<Vector_Vector_Sorter_Message> {};

  struct out : public out_port<Vector_Fused_Message> {};
};

template<typename TIME>
class IL_Fusion
{
  using defs=IL_Fusion_defs;
  	public:
      IL_Fusion() noexcept {
        state.criterion = 0.95;
        state.active = false;
      }

      struct state_type {
        Vector_Vector_Sorter_Message from_sorter;
        vector<double> Fused;
        Vector_Fused_Message ValueToSend;
        string type;
        double value;
        vector<double> sT;
        Fused_Message message;
        double criterion;
        bool multiple_types;
        int number_of_sensors;
        bool active;
        }; state_type state;

        using input_ports=std::tuple<typename defs::in>;
      	using output_ports=std::tuple<typename defs::out>;


        void internal_transition (){
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
         
          int i,p;
          state.from_sorter = get_messages<typename IL_Fusion_defs::in>(mbs)[0];
          if(state.from_sorter.message.size()>1) { //For Mulitple type of sensor inputs
            state.multiple_types = true;
           for(i=0; i<state.from_sorter.message.size(); i++) {
		        for(p=0; p<state.from_sorter.message[i].size(); p++) {
              state.sT.push_back(state.from_sorter.message[i][p].value);
            }
                   state.Fused.push_back( 
                    faulty_sensor_and_sensor_fusion(
                      compute_integrated_support_degree_score(state.sT,
                          compute_alpha(eigen_value_calculation(sdm_calculator(state.sT, state.sT.size()))), 
                              compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(state.sT, state.sT.size()))), state.sT.size()),
                                  sdm_calculator(state.sT, state.sT.size()),
                                  state.criterion, 
                                 state.sT.size()), state.sT, state.criterion, state.sT.size() ));
              
              state.type = state.from_sorter.message[i][p-1].sensor_type;
              state.value = state.Fused[i];
              state.message = Fused_Message(state.type, state.value);
              state.ValueToSend.message.push_back(state.message);

            state.sT.clear();
            state.sT.shrink_to_fit();
           } 
          }
          else { //For single type of sensor input
            state.multiple_types = false;
		        for(p=0; p<state.from_sorter.message[0].size(); p++) {
                  state.sT.push_back(state.from_sorter.message[0][p].value);
            }
               state.Fused.push_back( 
                  faulty_sensor_and_sensor_fusion(
                      compute_integrated_support_degree_score(state.sT,
                          compute_alpha(eigen_value_calculation(sdm_calculator(state.sT, state.sT.size()))), 
                          compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(state.sT, state.sT.size()))), state.sT.size()),
                          sdm_calculator(state.sT, state.sT.size()),
                            state.criterion, 
                                 state.sT.size()), state.sT, state.criterion, state.sT.size() ));

              state.type = state.from_sorter.message[0][p-1].sensor_type;
              state.value = state.Fused[i];
              state.message = Fused_Message(state.type, state.value);
              state.ValueToSend.message.push_back(state.message);

              state.sT.clear();

          }

            state.Fused.clear();
            state.sT.clear();
            state.Fused.shrink_to_fit();
            state.sT.shrink_to_fit();
           state.from_sorter.message.clear();
          state.from_sorter.message.shrink_to_fit();
        //  for(int i=0; i<state.ValueToSend.size(); ++i) // Ensure that you don't access any elements that don't exist
		    //     cout << state.ValueToSend[i] << " \n";

      		state.active = true;
      	}

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;
          get_messages<typename defs::out>(bags).push_back(state.ValueToSend);  
        return bags;
      }

      TIME time_advance() const {
        if(state.active) {
          return TIME("00:00:01");
        }
        return std::numeric_limits<TIME>::infinity();
      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename IL_Fusion<TIME>::state_type& i) {
                 os << "Sent Data by Fusion: " ;
                 return os;
               }
      };
#endif