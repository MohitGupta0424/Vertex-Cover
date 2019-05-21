#include <iostream>
#include "TakeInput.h"
using namespace std;

int main(){
	
	try{
		TakeInput inputobj;
    	inputobj.get_Input();
	}
	catch(exception& e){
		cerr<<"Error: "<<endl;
	}
	return 0;
}