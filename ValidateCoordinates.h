#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class ValidateCoordinates{
    public:
        bool samePoint(vector<int> coordinates, int, int);
        bool ptInCoords(vector<int> coordinates, int, int);
        double getDistance(int, int, int, int);
        int streetCrossing(vector<int> coordinates);
};