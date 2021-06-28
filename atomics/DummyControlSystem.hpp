#ifndef CS_INPUTREADER_HPP
#define CS_INPUTREADER_HPP

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
#include <cadmium/io/iestream.hpp>
#include "../data_structures/Command.hpp"

using namespace cadmium;
using namespace std;

    //Port definition
    struct ControlSystem_inputreader_status_defs{
      struct out : public out_port<Command_Rx_Status> {};
    };


    template<typename TIME>
    class ControlSystem_inputreader_status : public iestream_input<Command_Rx_Status,TIME, ControlSystem_inputreader_status_defs>{
      public:
        ControlSystem_inputreader_status() = default;
        ControlSystem_inputreader_status(const char* file_path) : iestream_input<Command_Rx_Status,TIME, ControlSystem_inputreader_status_defs>(file_path) {}
        ControlSystem_inputreader_status(const char* file_path, TIME t) : iestream_input<float,Command_Rx_Status, ControlSystem_inputreader_status_defs>(file_path) {}
    };


     //Port definition
    struct ControlSystem_inputreader_typeandtime_defs{
      struct out : public out_port<Command_Rx_TypeAndTime> {};
    };


    template<typename TIME>
    class ControlSystem_inputreader_typeandtime : public iestream_input<Command_Rx_TypeAndTime,TIME, ControlSystem_inputreader_typeandtime_defs>{
      public:
        ControlSystem_inputreader_typeandtime() = default;
        ControlSystem_inputreader_typeandtime(const char* file_path) : iestream_input<Command_Rx_TypeAndTime,TIME, ControlSystem_inputreader_typeandtime_defs>(file_path) {}
        ControlSystem_inputreader_typeandtime(const char* file_path, TIME t) : iestream_input<float,Command_Rx_TypeAndTime, ControlSystem_inputreader_typeandtime_defs>(file_path) {}
    };

     //Port definition
    struct ControlSystem_inputreader_actuator_defs{
      struct out : public out_port<Command_Rx_Actuator_Message> {};
    };


    template<typename TIME>
    class ControlSystem_inputreader_actuator : public iestream_input<Command_Rx_Actuator_Message,TIME, ControlSystem_inputreader_actuator_defs>{
      public:
        ControlSystem_inputreader_actuator() = default;
        ControlSystem_inputreader_actuator(const char* file_path) : iestream_input<Command_Rx_Actuator_Message,TIME, ControlSystem_inputreader_actuator_defs>(file_path) {}
        ControlSystem_inputreader_actuator(const char* file_path, TIME t) : iestream_input<float,Command_Rx_Actuator_Message, ControlSystem_inputreader_actuator_defs>(file_path) {}
    };
#endif