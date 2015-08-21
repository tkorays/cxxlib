#include "CmdDispatcher.h"
using namespace jx;

#include <iostream>
#include <vector>
using namespace std;

CmdDispatcher* cd = 0;


void test(vector<string>& p){
	for (vector<string>::iterator it = p.begin(); it != p.end(); it++){
		cout << *it << endl;
	}
}

void help(vector<string>& p){
	cd->Help();
}

int main(int argc,char** argv){
	CmdDispatcher d(argc, argv, false);
	d.Dispatch("test", test);
	cd = &d;
	d.Dispatch("help", help);
	//d.Process();
	d.Listen();
	return 0;
}