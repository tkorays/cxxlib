#include "plugin.h"
#include <stdio.h>

void TestHello(){
  printf("hello\n");
}

Command LoadCmd(){
    Command cmd = {
      "test",
      {CPT_DIGIT,CPT_DIGIT,CPT_NULL},
      TestHello
    };
    return cmd;
}


int main(){
  Command cmd =  LoadCmd();
  CmdExec("test","abc addd 123");
  return 0;
}
