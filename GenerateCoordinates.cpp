#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "GenerateCoordinates.h"
#include "ValidateCoordinates.h"

using namespace std;

GenerateCoordinates::GenerateCoordinates(){
    streetIncrement = 0;
}

int GenerateCoordinates::generateRand(int minVal,int maxVal)
    {
        if (minVal == maxVal){
            return minVal;
        }
        else{
            std::ifstream urandom("/dev/urandom");

            // check that it did not fail
            if (urandom.fail()) {
                std::cerr << "Error: cannot open /dev/urandom\n";
                return 1;
            }

            // read a random unsigned int
            unsigned int num = 42;
            urandom.read((char*)&num, sizeof(int));

            // close random stream
            urandom.close();
            int numGenerated = minVal + num%(maxVal - minVal);
            return numGenerated;
        }  
    }

vector<int> GenerateCoordinates::getCoordinates(int numOfLines , int coordRange){
    int count = 0;
    vector<int> coordinates;
    ValidateCoordinates valid;
    int numberOfLines = generateRand(1,numOfLines);
    int totalCoord = (numberOfLines+1)*2;
    int limitRand = 0;
        while(true){
            int xCoord = generateRand(coordRange*-1, coordRange);
            int yCoord = generateRand(coordRange*-1, coordRange);
            bool result = valid.samePoint(coordinates, xCoord, yCoord);
            bool result1 = valid.ptInCoords(coordinates, xCoord, yCoord);
            if(result == 1 && result1 == 1){
                coordinates.push_back(xCoord);
                coordinates.push_back(yCoord);
                count+=2;
                limitRand = 0;
            }
            else{
                limitRand++;
            }
            if(count == totalCoord){
                break;
            }
            if (limitRand == 25){
                std::cerr <<"Error: failed to generate valid input for 25 simultaneous attempts" << std::endl;
                exit(1);
            }
        }
    return coordinates;
}

string GenerateCoordinates::getStreetName(){
    string streetName="";
    streetName = "Street"+to_string(streetIncrement);
    streetIncrement++;
    return streetName;
}

vector<string> GenerateCoordinates::makeInput(int numOfStreets, int numOfLines , int coordRange){
    vector<string> removeStreets;
    int numberOfStreets = generateRand(2,numOfStreets);
    for(int i=0; i<numberOfStreets; i++){
        string coordinate = "";
        string output = "";
        vector<int> coordinates = getCoordinates(numOfLines , coordRange);
        for(unsigned j=0;j<coordinates.size()/2;j++){
            coordinate = coordinate+" ("+to_string(coordinates[j])+","+to_string(coordinates[j+1])+")";
        }
        string streetName = getStreetName();
        output = "a \""+streetName+"\""+coordinate;
        removeStreets.push_back(streetName);
        cout<<output<<endl;
    }
    return removeStreets;
}
void GenerateCoordinates::removeStreet(vector<string> removeStreets){
    for(unsigned i =0; i<removeStreets.size();i++){
        string output ="";
        output = "r \""+removeStreets[i]+"\"";
        cout<<output<<endl;
    }

}