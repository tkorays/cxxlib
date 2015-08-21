#include <invoker/plugin/Plugin.h>
#include <stdio.h>

PLUGIN_API test1(void* in,void* out){
	printf("hello\n");
	return PLUGIN_RET_OK;
}
PLUGIN_API test2(void* in, void* out){
	printf("cao nimei\n");
	return PLUGIN_RET_ERR;
}


PLUGIN_ADD_METHOD(3,  "test1", "test2" ,"fuck");