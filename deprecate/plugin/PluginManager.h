#ifndef __PLUGIN_MANAGER_INCLUDE_H__
#define __PLUGIN_MANAGER_INCLUDE_H__

#include <string>
#include <vector>


namespace jx{
	namespace tools{
		using namespace std;


		typedef int (__stdcall *dllfunc)();
		
		class Plugin{
		private:
			string name;
			void* module = nullptr;
		public:
			Plugin(string, void*);
			void set(string, void*);
			string getName();
			void* getModule();
			dllfunc getFunc(string n);
			bool isValid();
		};
		

		class PluginManager{
		private:
			vector<Plugin> plugins;
			PluginManager(){}
			PluginManager(const PluginManager&);
			PluginManager& operator=(const PluginManager&);


			static PluginManager* pInstance;
		public:
			static PluginManager* getInstance();
			void setDirectory(string name);

			int size();
			Plugin loadPlugin(string name);
			void unloadPlugin(string name);
			Plugin getPlugin(string name);
		};
		
	}
}
#endif // __PLUGIN_MANAGER_INCLUDE_H__