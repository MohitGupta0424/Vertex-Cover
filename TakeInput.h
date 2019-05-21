#include <iostream>
#include <list>
#include <vector>

using namespace std;

class TakeInput{
    public:
        void get_Input();
        vector<string> get_Source_des(string);
        list<int> vertices;
        vector<string> edges;
};