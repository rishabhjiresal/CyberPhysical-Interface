#ifndef IL_SORTER_HPP
#define IL_SORTER_HPP

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

#include "../data_structures/Sensor_Message.hpp"
#include "../data_structures/Sorter_Message.hpp"

#include "../drivers/Rearrange.h"
using namespace cadmium;
using namespace std;


struct IL_Sorter_defs
{
  struct s1 : public in_port<Sensor_Message>{};
  struct s2 : public in_port<Sensor_Message>{};
  struct s3 : public in_port<Sensor_Message>{};
  struct s4 : public in_port<Sensor_Message>{};
  struct s5 : public in_port<Sensor_Message>{};
  struct s6 : public in_port<Sensor_Message>{};
  struct s7 : public in_port<Sensor_Message>{};
  struct s8 : public in_port<Sensor_Message>{};

  struct out : public out_port<vector<vector<Sorter_Message>>> {};
};

template<typename TIME>
class IL_Sorter
{
  using defs=IL_Sorter_defs;
  	public:

      static bool compare (const Sensor_Message& a, const Sensor_Message& b) {
          return a.name < b.name;
      }

      IL_Sorter() noexcept {
        state.active = false;
      }

      struct state_type {
        vector<Sensor_Message> values_from_sensors;
        vector<vector<Sorter_Message>> send_to_fusion;
        bool active;
        }; state_type state;

        using input_ports=std::tuple<typename defs::s1, typename defs::s2, typename defs::s3, typename defs::s4, typename defs::s5, typename defs::s6, typename defs::s7, typename defs::s8>;
      	using output_ports=std::tuple<typename defs::out>;

        void internal_transition (){
          state.active = false;
         }

        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s1>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s2>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s3>(mbs)[0]); 
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s4>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s5>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s6>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s7>(mbs)[0]);
          state.values_from_sensors.push_back(get_messages<typename IL_Sorter_defs::s8>(mbs)[0]);

          vector<vector<Sensor_Message>> rearranged_sensor_message;
          sort(state.values_from_sensors.begin(), state.values_from_sensors.end(), compare);
          rearranged_sensor_message = rearrange(state.values_from_sensors);

          state.send_to_fusion = add_values_to_sorter_message(rearranged_sensor_message);
    //       for(int i=0; i<example.size(); i++) // Ensure that you don't access any elements that don't exist
		// for(int p=0; p<example[i].size(); p++) // You may not have had 10 in here before, only go to size().
		// cout << example[i][p] << " \n";
          //Sort(values_from_sensors, values_from_sorter);
      		state.active = true;
      	}

        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
      }

      typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;
          get_messages<typename defs::out>(bags).push_back(state.values_from_sensors);  
        return bags;
      }

      TIME time_advance() const {
        if(state.active) {
          return TIME("00:00:00");
        }
        return std::numeric_limits<TIME>::infinity();

      }

      friend std::ostringstream& operator<<(std::ostringstream& os, const typename IL_Sorter<TIME>::state_type& i) {
                 os << "Sent data to fusion " ;
                 return os;
               }
      };



#endif