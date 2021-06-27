#ifndef Rearrange_h
#define Rearrange_h

#include <vector>
#include <algorithm>
#include "../data_structures/Sensor_Message.hpp"
#include "../data_structures/Sorter_Message.hpp"
#include "../data_structures/Assigner_Message.hpp"
#include "../data_structures/Fused_Message.hpp"
using namespace std;

vector<vector<Sensor_Message>> rearrange(vector<Sensor_Message>&);

vector<vector<Sorter_Message>> add_values_to_sorter_message(vector<vector<Sensor_Message>>&);

vector<Assigner_Message> add_values_to_assigner_message(vector<Fused_Message>&);

#endif