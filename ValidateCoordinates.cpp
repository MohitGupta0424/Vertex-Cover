#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "ValidateCoordinates.h"

using namespace std;

bool ValidateCoordinates::samePoint(vector<int> coordinates, int xCoord, int yCoord){
    if(coordinates.size()>=2){
        for(unsigned i = 0; i<=(coordinates.size()-1); i++){
                if((coordinates[i] == xCoord) && (coordinates[i+1] == yCoord)){
                    return false;
                }
            i++;
        }
    }
    return true;
}

bool ValidateCoordinates::ptInCoords(vector<int> coordinates, int xCoord, int yCoord){
    if(coordinates.size()>=6){
        for(unsigned i = 0; i<=(coordinates.size())-1; i++){
            double distance = std::floor((getDistance(coordinates[i], coordinates[i+1], coordinates[i+2], coordinates[i+3]) * 100)) / 100;
            double distance1 = std::floor((getDistance(coordinates[i], coordinates[i+1], xCoord, yCoord) * 100)) / 100;
            double distance2 = std::floor((getDistance( xCoord, yCoord, coordinates[i+2], coordinates[i+3]) * 100)) / 100;
                if(distance1 + distance2 == distance){
                    return false;
                }
            i++;
        }
    }
    return true;
}

double ValidateCoordinates::getDistance(int pointx1, int pointy1, int pointx2, int pointy2){
    double distancex = (pointx2 - pointx1) * (pointx2 - pointx1);
    double distancey = (pointy2 - pointy1) * (pointy2 - pointy1);
    double distance = sqrt(distancex + distancey);
    return distance;
}