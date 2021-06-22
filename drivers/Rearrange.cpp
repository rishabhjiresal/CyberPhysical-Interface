#include "Rearrange.h"
#include<iostream>

void rearrange(vector<Sensor_Message>& values_from_sensor, vector<Sorter_Message>& values_from_sorter) {
    string tempstring;
        vector<Sensor_Message> temp = values_from_sensor;
        reverse(temp.begin(), temp.end());
        tempstring = values_from_sensor[0].name;
        tempstring.resize(4);
        while(!values_from_sensor.empty())
        {
        if(tempstring == temp[0].name.substr(0,3)){
            add_value_to_sorter_message(values_from_sorter, temp[0].name.substr(0,3));
            temp.pop_back();
        }
        else {
            tempstring = values_from_sensor[0].name;
            tempstring.resize(4);
        }  
        }

}

void add_value_to_sorter_message(vector<Sorter_Message>& values_from_sorter, string initals) {

}