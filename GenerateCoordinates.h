#include <iostream>
#include <vector>

using namespace std;

class GenerateCoordinates{
    public:
        int streetIncrement;
        vector<int> coordinates;
        GenerateCoordinates();
        int generateRand(int, int);
        vector<int> getCoordinates(int, int);
        string getStreetName(void);
        vector<string> makeInput(int, int, int);
        void removeStreet(vector<string>);
};