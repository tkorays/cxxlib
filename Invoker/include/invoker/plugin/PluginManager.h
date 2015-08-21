#ifndef __IVK_PLUGINMANAGER_H__
#define __IVK_PLUGINMANAGER_H__

#include <string>
#include <vector>


namespace invoker{
	namespace plugin{

		typedef struct {
			char name[16];
			void* handle;
		}plugin_info;

		class PluginManager{
		private:
			static PluginManager* pInstance;
			PluginManager(){};
			PluginManager(const PluginManager&);
			PluginManager& operator=(const PluginManager&);
		public:
			static PluginManager& getInstance();
			std::vector<plugin_info> plugins;
			void load(const char* name);
			void unload(const char* name);
			int call(const char* name, const char* func, void* in, void* out);
		};
	}
}

#endif // __IVK_PLUGINMANAGER_H__