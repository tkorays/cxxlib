#include <invoker/plugin/PluginManager.h>

#include <stdio.h>

using namespace invoker::plugin;

int main(){
	PluginManager& pm = PluginManager::getInstance();
	pm.load("test_plugin");
	pm.call("test_plugin", "test1", 0, 0);
	pm.call("test_plugin", "test2", 0, 0);
	pm.unload("test_plugin");
	return 0;
}