#include "plugin.h"
#include <stdio.h>

int TestHello(int a,int b){
  printf("hello%d,%d\n",a,b);
  return 1;
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

  FUNC_PROTOTYPE(int,sb,int,int);
  sb = &TestHello;
  sb(2,3);
  return 0;
}
