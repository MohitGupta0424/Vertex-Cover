#include <iostream>
#include "TakeInput.h"
using namespace std;

int main(int argc, char** argv){
	
	try{
		TakeInput inputobj;
    	inputobj.get_Input();
	}
	catch(exception& e){
		std::cerr << "Error: From A2 main\n";
	}
	return 0;
}