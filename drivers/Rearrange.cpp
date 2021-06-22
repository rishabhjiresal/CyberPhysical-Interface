#include "Rearrange.h"
#include<iostream>

vector<vector<Sensor_Message>> rearrange(vector<Sensor_Message>& values_from_sensor) {
    string tempstring;
        vector<vector<Sensor_Message>> temp1;
        vector<Sensor_Message> temp = values_from_sensor;
        vector<Sensor_Message> temp2;
        int counter = 0;
        tempstring = values_from_sensor[0].name;
        tempstring.resize(3);
        for(auto i=0;i<temp.size();++i)
        {
        if(tempstring == temp[i].name.substr(0,3)){
            temp2.push_back(temp[i]);
        }
        else {
            counter++;
            tempstring = values_from_sensor[i].name;
            tempstring.resize(3);
            --i;
            }

        if(counter>0) {
            temp1.push_back(temp2);
            temp2.clear();
            counter = 0;
        }  
        }
        if(counter == 0) {
            temp1.push_back(temp2);
            temp2.clear();
        }
        return temp1;

}

vector<vector<Sorter_Message>> add_values_to_sorter_message(vector<vector<Sensor_Message>>& sensor_message) {
    vector<vector<Sorter_Message>> sorter_message;
    vector<Sorter_Message> temperature, humidity, co2, lux, pir;
    int tempCounter=1, HumCounter=1, CO2Counter=1, LuxCounter=1, PIRCounter=1;
    for(int i = 0; i<sensor_message.size();i++) {
        for (int j = 0; j<sensor_message[i].size();j++) {
            
            if(sensor_message[i][j].name.substr(0,3) == "Tem") {
                Sorter_Message temp(tempCounter, "Temperature", sensor_message[i][j].value);
                temperature.push_back(temp);
                tempCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "Hum") {
                Sorter_Message temp(HumCounter, "Humidity", sensor_message[i][j].value);
                humidity.push_back(temp);
                HumCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "CO2") {
                Sorter_Message temp(CO2Counter, "CarbonDioxide", sensor_message[i][j].value);
                co2.push_back(temp);
                CO2Counter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "Lux") {
                Sorter_Message temp(LuxCounter, "Luminosity", sensor_message[i][j].value);
                lux.push_back(temp);
                LuxCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "PIR") {
                Sorter_Message temp(PIRCounter, "PIR", sensor_message[i][j].value);
                pir.push_back(temp);
                PIRCounter++;
            }
        }
        if(tempCounter>1) {sorter_message.push_back(temperature); tempCounter = 1;}
        if(HumCounter>1) {sorter_message.push_back(humidity);HumCounter = 1;}
        if(CO2Counter>1) {sorter_message.push_back(co2);CO2Counter = 1;}
        if(LuxCounter>1) {sorter_message.push_back(lux);LuxCounter = 1;}
        if(PIRCounter>1) {sorter_message.push_back(pir);PIRCounter = 1;}
    }
    return sorter_message;
}