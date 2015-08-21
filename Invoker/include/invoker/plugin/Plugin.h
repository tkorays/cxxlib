#ifndef __IVK_PLUGIN_H__
#define __IVK_PLUGIN_H__


#define PLUGIN_EXPORT __declspec(dllexport)
#define PLUGIN_IMPORT __declspec(dllimport)
#define PLUGIN_API PLUGIN_EXPORT int __stdcall
typedef int(__stdcall *plugin_func)(void*,void*);

#define PLUGIN_NAME_MAX 16
#define PLUGIN_MODIFY_NAME_MAX 20
#define PLUGIN_STDCALL_PARAM_SIZE 8


#define PLUGIN_ADD_METHOD(cnt,method,...) \
	PLUGIN_EXPORT int METHOD_CNT = cnt; \
	PLUGIN_EXPORT char METHODS[cnt][PLUGIN_NAME_MAX] = { ## method##,##__VA_ARGS__## };

typedef enum{
	PLUGIN_RET_OK,
	PLUGIN_RET_ERR,
	PLUGIN_RET_MERR
}plugin_ret;




#endif // __IVK_PLUGIN_H__