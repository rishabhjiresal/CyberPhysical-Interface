#include "Rearrange.h"
#include<iostream>

vector<vector<Sensor_Message>> rearrange(vector<Sensor_Message>& values_from_sensor) {
    string tempstring;
        vector<vector<Sensor_Message>> temp1;
        vector<Sensor_Message> temp = values_from_sensor;
        vector<Sensor_Message> temp2;
                //reverse(temp.begin(), temp.end());
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
        //  for(int i=0; i<temp1.size(); i++) // Ensure that you don't access any elements that don't exist
		// for(int p=0; p<temp1[i].size(); p++) // You may not have had 10 in here before, only go to size().
		// cout << temp1[i][p] << " \n";
        return temp1;

}

vector<vector<Sorter_Message>> add_values_to_sorter_message(vector<vector<Sensor_Message>>& sensor_message) {
    vector<vector<Sorter_Message>> sorter_message;
    int tempCounter=1, HumCounter=1, CO2Counter=1, LuxCounter=1, PIRCounter=1;
    for(auto i = 0; i<sensor_message.size();++i) {
        for (auto j = 0; j<sensor_message[i].size();++j) {
            
            if(sensor_message[i][j].name.substr(0,3) == "Tem") {
                sorter_message[i][j].sensor_type = "Temperature";
                sorter_message[i][j].value = sensor_message[i][j].value;
                sorter_message[i][j].number = tempCounter;
                tempCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "Hum") {
                sorter_message[i][j].sensor_type = "Humidity";
                sorter_message[i][j].value = sensor_message[i][j].value;
                sorter_message[i][j].number = HumCounter;
                HumCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "CO2") {
                sorter_message[i][j].sensor_type = "CarbonDioxide";
                sorter_message[i][j].value = sensor_message[i][j].value;
                sorter_message[i][j].number = CO2Counter;
                CO2Counter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "Lux") {
                sorter_message[i][j].sensor_type = "Luminosity";
                sorter_message[i][j].value = sensor_message[i][j].value;
                sorter_message[i][j].number = LuxCounter;
                LuxCounter++;
            }
            if(sensor_message[i][j].name.substr(0,3) == "PIR") {
                sorter_message[i][j].sensor_type = "PIR";
                sorter_message[i][j].value = sensor_message[i][j].value;
                sorter_message[i][j].number = PIRCounter;
                PIRCounter++;
            }
        }
    }
    return sorter_message;
}