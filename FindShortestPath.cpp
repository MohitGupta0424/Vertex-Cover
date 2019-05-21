#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <stdlib.h>
#include "FindShortestPath.h"

using namespace std;

FindShortestPath::FindShortestPath(list<int> vertices){
	connection = new list<int>[vertices.size()];
}

void FindShortestPath::get_AdajencyList (list<int> vertices , vector<string> edges){
    int numOfedges = edges.size()-1;
    int eFrom , eTo;
    for (int i=0;i<numOfedges;i++){
        eFrom = atoi(edges[i].c_str());
        eTo = atoi(edges[i+1].c_str());
        connection[eFrom].push_back(eTo);
        connection[eTo].push_back(eFrom);
        i++;
    }
}

void FindShortestPath::get_AllPaths(list<int> vertices , vector<string> edges, int source, int destination){
	get_AdajencyList (vertices , edges);
    int numOfVertices = vertices.size();
    bool *visited = new bool[numOfVertices];
    int *path = new int[numOfVertices]; 
	int path_index = 0;
	for (int i = 0; i < numOfVertices; i++) {
		visited[i] = false;
	}
	FindShortestPath::getAllPathsUtil(source, destination, visited, path, path_index);
}

void FindShortestPath::getAllPathsUtil(int source, int destination, bool visited[], int path[], int path_index){
	visited[source] = true; 
	path[path_index] = source; 
	path_index++; 
	if (source == destination) 
	{ 
		string s="";
		for (int i = 0; i<path_index; i++){
			s = s + to_string(path[i]) +"-"; 
		}
		s = s.substr(0, s.size()-1);
		get_paths.push_back(s);
 	} 
	else
	{  
		list<int>::iterator i; 
		for (i = connection[source].begin(); i != connection[source].end(); ++i) {
			if (!visited[*i]) {
				getAllPathsUtil(*i, destination, visited, path, path_index); 
			}
		} 
	}
	path_index--; 
	visited[source] = false;
}

void FindShortestPath::printShortestPath(){
	int max = 0;
	if(get_paths.size()>0){
		for(unsigned i =0; i < get_paths.size();i++){
			int count =0;
			for(unsigned j =0;j<get_paths[i].length();j++){
				if (get_paths[i][j]=='-'){
					count++;
				}
			}
			if(i==0){
				max = count;
				shortest_path = get_paths[i];
			}	
			if(count<max){
				max = count;
				shortest_path = get_paths[i];
			}
		}
	}
	else{
		cout<<"Error : No Path Found.";
	}
	cout<<shortest_path<<endl;
}