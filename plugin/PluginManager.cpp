#include "PluginManager.h"
using namespace jx::tools;

#include <Windows.h>

#include <iostream>
using namespace std;

Plugin::Plugin(string name,void* m){
	this->name = name;
	this->module = m;
}
void Plugin::set(string name,void* m){
	this->name = name;
	this->module = m;
}
bool Plugin::isValid(){
	return this->name.length() != 0 && this->module != nullptr;
}
string Plugin::getName(){
	return this->name;
}
void* Plugin::getModule(){
	return this->module;
}
dllfunc Plugin::getFunc(string n){
	return (dllfunc)GetProcAddress((HMODULE)this->module,n.c_str());
}

PluginManager* PluginManager::pInstance = nullptr;

PluginManager* PluginManager::getInstance(){
	if (pInstance == nullptr){
		pInstance = new PluginManager();
	}
	return pInstance;
}

void PluginManager::setDirectory(string name){
	if (name.length() > 0){
		SetDllDirectoryA(name.c_str());
	}
}

int PluginManager::size(){
	return this->plugins.size();
}

Plugin PluginManager::loadPlugin(string name){
	Plugin pl("",nullptr);
	HMODULE hm = LoadLibraryA(name.c_str());
	if (!hm){
		return pl; // return a invalid plugin
	}
	pl.set(name,  hm);
	plugins.push_back(pl);
	return pl;
}

void PluginManager::unloadPlugin(string name){
	vector<Plugin>::iterator it = plugins.begin();
	while (it != plugins.end()){
		if ((*it).getName() == name){
			FreeLibrary((HMODULE)(*it).getModule());
			plugins.erase(it);
			return;
		}
		it++;
	}
}

Plugin PluginManager::getPlugin(string name){
	vector<Plugin>::iterator it = plugins.begin();
	while (it != plugins.end()){
		if ((*it).getName() == name){
			return (*it);
		}
		it++;
	}
	Plugin a("",nullptr);
	return a;
}