#include <iostream>
#include <algorithm>
#include "TakeInput.h"
#include "FindShortestPath.h"
#include <sstream>
#include <string>

using namespace std;

void TakeInput::get_Input(){
        while(true){
            string userInput = "";
            getline(cin, userInput);
            if (userInput[0] == 'V'){
            	vertices.clear();
				cout<<userInput<<endl;
                int range = atoi(userInput.substr(2,userInput.length()).c_str());
                list<int>::iterator it;
                for (int i =0; i<range; i++){
                    vertices.push_back(i);
                    }
                edges.clear();    
                }
            else if (userInput[0] == 'E' && userInput[1] == ' '){
				cout<<userInput<<endl;
            	if (vertices.size()>1  && edges.size()==0){ 
	                bool flag = false;
	                for (unsigned i =0; i < userInput.length();i++){
	                    if (userInput[i] == '<'){
	                        string str = "";
	                        while (userInput[i] != '>'){
	                            if (userInput[i] != ','){
	                                str = str+userInput[i];
	                                i++;
	                                }
	                            else{
	                                str = str.substr(1,str.length());
	                                int value = atoi(str.c_str());
	                                list<int>::iterator it;
	                                it = std::find(vertices.begin(), vertices.end(), value);
	                                if(it == vertices.end()){
									   std::cerr << "Error: Edges wrongly input.\n";
	                                   edges.push_back(str);
	                                   flag = true;
	                                   vertices.clear();
	                                   break;
	                                }
	                                else{
	                                edges.push_back(str);
	                                }
	                                i++;
	                                str = "";
	                            }
	                        }
	                        if (flag == true){
	                            break;
	                        }
	                        else{
	                            int value = atoi(str.c_str());
	                            list<int>::iterator it;
	                            it = find(vertices.begin(), vertices.end(), value);
	                            if(it == vertices.end()){
	                                std::cerr << "Error: Edges wrongly input.\n";
	                                flag = true;
	                                vertices.clear();
	                                break;
	                            }
	                            else{
	                                edges.push_back(str);
	                            }
	                        }
	                    }
                	}
                }
				else{
					vertices.clear();
				}
			}
	        else if (userInput[0] == 's'){
	          	if (edges.size()>=1 && vertices.size()>1){
	          		vector<string> elements = get_Source_des(userInput);
		           	int source = atoi(elements[1].c_str());
		          	int destination = atoi(elements[2].c_str());
	          		list<int>::iterator itsource;
	                itsource = std::find(vertices.begin(), vertices.end(), source);
	                list<int>::iterator itdest;
	                itdest = std::find(vertices.begin(), vertices.end(), destination);
	                if(itsource == vertices.end() || itdest == vertices.end()){
						std::cerr << "Error: From s commond source or destination not found in vertices.\n";
	                }
	                else{
	                FindShortestPath shortobj(vertices);
		            shortobj.get_AllPaths(vertices,edges,source,destination);
		            shortobj.printShortestPath();
		            shortobj.get_paths.clear();
					}
				}
	           	else{
					std::cerr << "Error: From s commond No edges or vertices found for the given input.\n";
	            	vertices.clear();
				}
			}
            else if (!cin || userInput == ""){
            	if (cin.eof()) {
            		break;
				}
				else{
					break;	
				} 
            }
            else{
                std::cerr << "Error: Invalid Input.\n";              
            }
        }
}
        
vector<string> TakeInput::get_Source_des(string input){
	vector<string> output;
	istringstream iss(input);
    while(iss)
    {
        string subs;
        iss >> subs;
        output.push_back(subs);
    }
    return output;
}