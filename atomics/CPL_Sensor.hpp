#ifndef CPL_SENSOR_HPP
#define CPL_SENSOR_HPP

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

using namespace cadmium;
using namespace std;


#ifdef RT_ARM_MBED
#include <cadmium/real_time/arm_mbed/embedded_error.hpp>
#include "mbed.h"
#include "../drivers/Driver.hpp"

struct CPL_Sensor_defs
{
        struct out : public out_port<Sensor_Message> { };
  };

template<typename TIME>
class CPL_Sensor
{
using defs=CPL_Sensor_defs;
	public:
		TIME pollingRate;
    CPL_Sensor() noexcept {
      MBED_ASSERT(false);
    }
        
	  	CPL_Sensor(PinName Pin, TIME rate, string name) noexcept {
        pollingRate = rate;
        state.name = name;
        state.Sensor = new drivers::TEMPERATURE(Pin);
    		}

      CPL_Sensor(PinName Mosi, PinName Miso, PinName sclk, PinName cs, TIME rate, string name) noexcept {
        pollingRate = rate;
        state.name = name;
      }

      CPL_Sensor(PinName Scl, PinName Sda, TIME rate, string name) noexcept {
        pollingRate = rate;
        state.name = name;
      }

      CPL_Sensor(PinName uart_tx, PinName uart_rx, string mode, TIME rate, string name) noexcept {
        pollingRate = rate;
        state.name = name;
        
      }
    		struct state_type {
    			double output;
          Sensor_Message message;
          string name;
          drivers::TEMPERATURE* Sensor;
    			}; state_type state;

    		using input_ports=std::tuple<>;
    		using output_ports=std::tuple<typename defs::out>;

    		void internal_transition() {
          state.Sensor->getData(state.output);
          state.message.name = state.name;
          state.message.value = state.output;
    			}

    		void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
      			MBED_ASSERT(false);
      //throw std::logic_error("External transition called in a model with no input ports");
    }

    		void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
      			internal_transition();
      			external_transition(TIME(), std::move(mbs));
    }

    		typename make_message_bags<output_ports>::type output() const {
    			typename make_message_bags<output_ports>::type bags;
    				get_messages<typename defs::out>(bags).push_back(state.message);
            return bags;
          }

    		TIME time_advance() const {
    			  return pollingRate;
   		 }

   		 friend std::ostringstream& operator<<(std::ostringstream& os, const typename CPL_Sensor<TIME>::state_type& i) {
      os << "Temperature Output " << i.message;
      return os;
    }
  };
  #else
#include <cadmium/io/iestream.hpp>
    using namespace cadmium;
    using namespace std;

    //Port definition
    struct CPL_Sensor_defs{
      struct out : public out_port<Sensor_Message> {};
    };


    template<typename TIME>
    class CPL_Sensor : public iestream_input<Sensor_Message,TIME, CPL_Sensor_defs>{
      public:
        CPL_Sensor() = default;
        CPL_Sensor(const char* file_path) : iestream_input<Sensor_Message,TIME, CPL_Sensor_defs>(file_path) {}
        CPL_Sensor(const char* file_path, TIME t) : iestream_input<float,Sensor_Message, CPL_Sensor_defs>(file_path) {}
    };

#endif
#endif