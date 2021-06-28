#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>
#include <ctime>


#include <cadmium/modeling/coupling.hpp>
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/concept/coupled_model_assert.hpp>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/modeling/dynamic_atomic.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/tuple_to_ostream.hpp>
#include <cadmium/logger/common_loggers.hpp>
#include <cadmium/io/iestream.hpp>

#include "../atomics/CPL_Sensor.hpp"
#include "../atomics/IL_Sorter.hpp"
#include "../atomics/IL_Fusion.hpp"
#include "../atomics/IL_Assigner.hpp"
#include <NDTime.hpp>

const char* t1_IN = "./inputs/Temperature_Sensor_Values1_copy.txt";
const char* t2_IN = "./inputs/Temperature_Sensor_Values2_copy.txt";
const char* t3_IN = "./inputs/Temperature_Sensor_Values3_copy.txt";
const char* t4_IN = "./inputs/Temperature_Sensor_Values4_copy.txt";
const char* t5_IN = "./inputs/Temperature_Sensor_Values5_copy.txt";
// const char* t6_IN = "./inputs/Temperature_Sensor_Values6_copy.txt";
// const char* t7_IN = "./inputs/Temperature_Sensor_Values7_copy.txt";
// const char* t8_IN = "./inputs/Temperature_Sensor_Values8_copy.txt";
// const char* t9_IN = "./inputs/Temperature_Sensor_Values9 copy.txt";
// const char* t10_IN = "./inputs/Temperature_Sensor_Values10 copy.txt";

using namespace std;

using hclock=chrono::high_resolution_clock;
using TIME = NDTime;

int main(int argc, char ** argv) {
  //This will end the main thread and create a new one with more stack.
  #ifdef RT_ARM_MBED
    //Logging is done over cout in RT_ARM_MBED
    struct oss_sink_provider{
      static std::ostream& sink(){
        return cout;
      }
    };
  #else
    // all simulation timing and I/O streams are ommited when running embedded

    auto start = hclock::now(); //to measure simulation execution time

    /*************** Loggers *******************/

    static std::ofstream out_data("CPS_Interface_Cadmium_output.txt");
    struct oss_sink_provider{
      static std::ostream& sink(){
        return out_data;
      }
    };
  #endif


  using info=cadmium::logger::logger<cadmium::logger::logger_info, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using debug=cadmium::logger::logger<cadmium::logger::logger_debug, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using state=cadmium::logger::logger<cadmium::logger::logger_state, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using log_messages=cadmium::logger::logger<cadmium::logger::logger_messages, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using routing=cadmium::logger::logger<cadmium::logger::logger_message_routing, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using global_time=cadmium::logger::logger<cadmium::logger::logger_global_time, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using local_time=cadmium::logger::logger<cadmium::logger::logger_local_time, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
  using log_all=cadmium::logger::multilogger<info, debug, state, log_messages, routing, global_time, local_time>;
  using logger_top=cadmium::logger::multilogger<log_messages, global_time>;

  using AtomicModelPtr=std::shared_ptr<cadmium::dynamic::modeling::model>;
  using CoupledModelPtr=std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>>;

  AtomicModelPtr CPL_Sensor1 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor1", t1_IN);
  AtomicModelPtr CPL_Sensor2 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor2", t2_IN);
  AtomicModelPtr CPL_Sensor3 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor3", t3_IN);
  AtomicModelPtr CPL_Sensor4 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor4", t4_IN);
  AtomicModelPtr CPL_Sensor5 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor5", t5_IN);
  // AtomicModelPtr CPL_Sensor6 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor6", t6_IN);
  // AtomicModelPtr CPL_Sensor7 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor7", t7_IN);
  // AtomicModelPtr CPL_Sensor8 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor8", t8_IN);
  // AtomicModelPtr CPL_Sensor9 = cadmium::dynamic::translate::make_dynamic_atomic_model<CPL_Sensor, TIME>("CPL_Sensor9", t9_IN);
  AtomicModelPtr IL_Sorter1 = cadmium::dynamic::translate::make_dynamic_atomic_model<IL_Sorter, TIME>("IL_Sorter1");
  AtomicModelPtr IL_Fusion1 = cadmium::dynamic::translate::make_dynamic_atomic_model<IL_Fusion, TIME>("IL_Fusion1");
  AtomicModelPtr IL_Assigner1 = cadmium::dynamic::translate::make_dynamic_atomic_model<IL_Assigner, TIME>("IL_Assigner1");

  cadmium::dynamic::modeling::Ports iports_TOP = {};
  cadmium::dynamic::modeling::Ports oports_TOP = {};

  cadmium::dynamic::modeling::Models submodels_TOP = {CPL_Sensor1, CPL_Sensor2, CPL_Sensor3, CPL_Sensor4, CPL_Sensor5/*, CPL_Sensor6, CPL_Sensor7, CPL_Sensor8*/, IL_Sorter1, IL_Fusion1, IL_Assigner1};

cadmium::dynamic::modeling::EICs eics_TOP = {};
cadmium::dynamic::modeling::EOCs eocs_TOP = {};

cadmium::dynamic::modeling::ICs ics_TOP = {

cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s1>("CPL_Sensor1","IL_Sorter1"),

  cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s2>("CPL_Sensor2","IL_Sorter1"),

  cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s3>("CPL_Sensor3","IL_Sorter1"),

  cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s4>("CPL_Sensor4","IL_Sorter1"),

   cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s5>("CPL_Sensor5","IL_Sorter1"),

  // cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s6>("CPL_Sensor6","IL_Sorter1"),

  // cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s7>("CPL_Sensor7","IL_Sorter1"),

  // cadmium::dynamic::translate::make_IC<CPL_Sensor_defs::out, IL_Sorter_defs::s8>("CPL_Sensor8","IL_Sorter1"),

  cadmium::dynamic::translate::make_IC<IL_Sorter_defs::out, IL_Fusion_defs::in>("IL_Sorter1", "IL_Fusion1"),

  cadmium::dynamic::translate::make_IC<IL_Fusion_defs::out, IL_Assigner_defs::in>("IL_Fusion1", "IL_Assigner1")


};
CoupledModelPtr TOP = std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
    "TOP",
    submodels_TOP,
    iports_TOP,
    oports_TOP,
    eics_TOP,
    eocs_TOP,
    ics_TOP
    );
#ifdef RT_ARM_MBED
   // cadmium::dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});

      cadmium::dynamic::engine::runner<NDTime, cadmium::logger::not_logger> r(TOP, {0});
#else

 // cadmium::dynamic::engine::runner<NDTime, log_all> r(TOP, {0});
    cadmium::dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
#endif

r.run_until(NDTime("100:00:00:000"));
#ifndef RT_ARM_MBED
return 0;
#endif

}
