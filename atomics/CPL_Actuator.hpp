#ifndef CPL_ACTUATOR_HPP
#define CPL_ACTUATOR_HPP

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

#ifdef RT_ARM_MBED
#include <cadmium/real_time/arm_mbed/embedded_error.hpp>
#include "mbed.h"
#include "../drivers/Driver.hpp"

struct CPL_Actuator_defs
{ 
        struct inName : public in_port<string> {};
        struct inValue : public in_port<double> {};
        struct out : public out_port<double> {};
  };

template<typename TIME>
class CPL_Actuator
{
using defs=CPL_Actuator_defs;
	public:
    CPL_Actuator() noexcept {
      MBED_ASSERT(false);
    }

    		struct state_type {
                double Value;
                string Name;
                bool active;
    			}; state_type state;

    		using input_ports=std::tuple<typename defs::inName, typename defs::inValue>;
    		using output_ports=std::tuple<typename defs::out>;

    		void internal_transition() {
                state.active = false;
    			}

    		void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
                for(const auto &x : get_messages<typename defs::inName>(mbs)) {
                     state.Name = x;
                }
                for(const auto &x : get_messages<typename defs::inValue>(mbs)) {
                     state.Value = x;
                }
                state.active = true;
    }

    		void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
      			internal_transition();
      			external_transition(TIME(), std::move(mbs));
    }

    		typename make_message_bags<output_ports>::type output() const {
    			typename make_message_bags<output_ports>::type bags;
    				get_messages<typename defs::out>(bags).push_back(state.Value);
            return bags;
          }

    		TIME time_advance() const {
    			 if(state.active) {
                     return TIME("00:00:00");
                 }
                 return std::numeric_limits<TIME>::infinity();
   		 }

   		 friend std::ostringstream& operator<<(std::ostringstream& os, const typename CPL_Actuator<TIME>::state_type& i) {
      os << "Temperature Output " << i.outputTemp;
      return os;
    }
  };
  #else
 #include <cadmium/io/oestream.hpp>
  using namespace cadmium;
  using namespace std;

  //Port definition
  struct CPL_Actuator_defs{
      struct in : public in_port<double> {};
  };

  template<typename TIME>
  class CPL_Actuator : public oestream_output<double,TIME, CPL_Actuator_defs>{
    public:
      CPL_Actuator() = default;
      CPL_Actuator(const char* file_path) : oestream_output<double,TIME, CPL_Actuator_defs>(file_path) {}
  };


#endif
#endif