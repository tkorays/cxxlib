#include <iostream>

using namespace std;

#include "PluginManager.h"
using namespace jx::tools;



#define DP_SIZE int
#define DP_BODY void*
#define DP_TYPE int

typedef struct datapack_{
	DP_SIZE size;
	DP_BODY body;
	DP_TYPE type;
} datapack;

typedef int(__stdcall*hehe)(datapack*, datapack*);

int main(int argc, char* argv[]){
	PluginManager* pm = PluginManager::getInstance();
	pm->loadPlugin("mii");


	Plugin p = pm->getPlugin("mii");
	hehe func = (hehe)p.getFunc("_DLLFunc@8");

	datapack a;
	datapack b;
	func(&a, &b);

	pm->unloadPlugin("mii");
	return 0;
}