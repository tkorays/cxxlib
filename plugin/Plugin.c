#include "plugin.h"
#include <stdio.h>

Command g_CmdList[100];
int g_CmdSize = 0;

void CmdExec(const char* name,const char* para_str){
      printf("load %s and run!\n",name);
}
