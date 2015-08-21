#include <windows.h>
#include <invoker/plugin/PluginManager.h>
#include <invoker/plugin/Plugin.h>

using namespace invoker::plugin;
using namespace std;

int plugin_get_modify_name(const char* orgname, char modname[]){
	int len = 0;
	if (NULL == orgname || NULL == modname){
		return PLUGIN_RET_MERR;
	}
	len = strlen(orgname);
	_snprintf(modname, len + 4, "%c%s%c%c", '_', orgname, '@', '0' + PLUGIN_STDCALL_PARAM_SIZE);
	return PLUGIN_RET_OK;
}

void PluginManager::load(const char* name){
	if (NULL == name){
		return;
	}
	HMODULE hLib = LoadLibraryA(name);
	if (!hLib){
		return;
	}
	plugin_info info;
	memcpy(info.name, name, strlen(name) + 1);
	info.handle = hLib;
	this->plugins.push_back(info);
}

void PluginManager::unload(const char* name){
	if (NULL == name){
		return;
	}
	vector<plugin_info>::iterator it = this->plugins.begin();
	while (it != this->plugins.end()){
		if (memcmp(name, it->name, strlen(name))==0){
			FreeLibrary((HMODULE)it->handle);
			this->plugins.erase(it);
			break;
		}
		it++;
	}
}

vector<plugin_info>::const_iterator find_plugin(PluginManager* plg, const char* name){
	vector<plugin_info>::const_iterator it = plg->plugins.cbegin();
	while (it != plg->plugins.cend()){
		if (memcmp(name, it->name, strlen(name)) == 0){
			break;
		}
		it++;
	}
	return it;
}

int PluginManager::call(const char*name, const char* func, void* in, void* out){
	vector<plugin_info>::const_iterator it = find_plugin(this, name);
	if (it == this->plugins.cend()){
		return -1;
	}
	char modname[PLUGIN_MODIFY_NAME_MAX];
	plugin_get_modify_name(func, modname);
	plugin_func hFunc = (plugin_func)GetProcAddress((HMODULE)it->handle, modname);
	if (NULL == hFunc){
		return -1;
	}
	return hFunc(in, out);
}
PluginManager* PluginManager::pInstance = nullptr;
PluginManager& PluginManager::getInstance(){
	if (NULL == pInstance){
		pInstance = new PluginManager;
	}
	return *pInstance;
}


