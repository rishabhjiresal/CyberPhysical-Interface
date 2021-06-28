#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../data_structures/Assigner_Message.hpp"
#include "DataToStorage.h"

#ifdef RT_ARM_MBED
#include "mbed.h"
void StoreData(Vector_Assigner_Message message) {
            int i;
            time_t seconds = time(NULL);
 
            for(auto i=0;i<message.size();++i){
            char buf[40];
            strftime(buf,40, "%Y-%m-%dT%H:%M:%SZ,", localtime(&seconds));
            printf("%s", buf);
             cout<<message[i].type << " " << message[i].value<< " " << message[i].units <<endl ;
                }
}
#else
void StoreData(Vector_Assigner_Message message) {
    fstream fout;
     time_t seconds = time(NULL);
    fout.open("../DataStorage.csv", ios::out | ios::app);

   for(auto i=0;i<message.message.size();++i){
            char buf[40];
            strftime(buf,40, "%Y-%m-%dT%H:%M:%SZ, ", localtime(&seconds));
            fout<< buf;
             fout<<message.message[i].type << ", " << message.message[i].value<< ", " << message.message[i].units <<endl ;
                }
    
    
}

void ReadData(string time_stamp, string type, Assigner_Message& message) {
    fstream fin;
    fin.open("../DataStorage.csv", ios::in);

    vector<string> row;
    string line, word, temp;
  
    while (fin >> temp) {
  
        row.clear();

        getline(fin, line);

        stringstream s(line);
  
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if(row[0].compare(time_stamp) && row[1].compare(type)) {
            message.type = row[1];
            message.value = stod(row[2]);
            message.units = row[3];
            break;
        }
    }

}
#endif