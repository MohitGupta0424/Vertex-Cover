#include <iostream>
#include <list>
#include <vector>

using namespace std;

class FindShortestPath{
    public:
    	list<int> *connection;
    	vector<string> get_paths;
    	string shortest_path;
    	FindShortestPath(list<int> vertices);
        void get_AllPaths(list<int> vertices , vector<string> edges,int,int);
        void get_AdajencyList (list<int> vertices , vector<string> edges);
        void getAllPathsUtil(int , int , bool* , int* , int);
        void printShortestPath();
};