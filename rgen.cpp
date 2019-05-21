#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include "GenerateCoordinates.h"
using namespace std;

int main (int argc, char **argv)
{
    int numberOfStreets = 10;
    int numberOfLines = 5;
    int wait = 5;
    int coordRange = 20;
    string numberOfStreetsStr;
    string numberOfLinesStr;
    string waitStr;
    string coordRangeStr;
    bool street_flag = false;
    vector<string> streets={};
    int m;
    GenerateCoordinates generateInput;
    // expected options are '-s', '-n', '-l' and '-c value'
    while ((m = getopt (argc, argv, "s:n:l:c:")) != -1){
        switch (m)
        {
        case 's':
            numberOfStreetsStr = optarg;
            numberOfStreets = atoi(numberOfStreetsStr.c_str());
            if(numberOfStreets < 2){
               std::cerr << "Error: option -" << optopt << " is below 2." << std::endl;
               return 1;
            }
            break;
        case 'n':
            numberOfLinesStr = optarg;
            numberOfLines = atoi(numberOfLinesStr.c_str());
            if(numberOfLines < 1){
               std::cerr << "Error: option -" << optopt << " is below 1." << std::endl;
               return 1;
            }
            break;
        case 'l':
            waitStr = optarg;
            wait = atoi(waitStr.c_str());
            if(wait < 5){
               std::cerr << "Error: option -" << optopt << " is below 5." << std::endl;
               return 1;
            }
            break;
        case 'c':
            coordRangeStr = optarg;
            coordRange = atoi(coordRangeStr.c_str());
            if (coordRange < 1){
                std::cerr << "Error: option -" << optopt << " is below 5." << std::endl;
                return 1;
            }
            break;    
        case '?':
            if (optopt == 'c' || optopt == 'l' || optopt == 'n' || optopt == 's')
                std::cerr << "Error: option -" << optopt << " requires an argument." << std::endl;
            else
                std::cerr << "Error: unknown option: " << optopt << std::endl;
            return 1;
        default:
            return 0;
        }
    }
        wait = generateInput.generateRand(5,wait);
    while(true){
        if(street_flag){
            generateInput.removeStreet(streets);
        }
        streets = generateInput.makeInput(numberOfStreets, numberOfLines, coordRange);
        cout<<"g"<<endl;
        street_flag = true;
        sleep(wait);
    }
    return 0;
}
