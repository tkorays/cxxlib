#include <stdio.h>

#define FUNC_PROTOTYPE(name,ret,args...) typedef ret(*name)(args)
typedef enum {
    CPT_NULL,
    CPT_DIGIT,
    CPT_STRING
} cmd_para_type;

char g_buf[1024];
int g_buf_pos = 0;

typedef struct {
    char name[20];
    int para_size[10];  // 参数所占内存大小
    char* buf; // 保存解析后的数据
} cmd_info;


int cmd_parse(cmd_info* ci, const char* cmd){
    char buf[255];
    int i,j;
    if(ci==NULL || cmd==NULL){
        return -1;
    }

    // cmdname para[]
    return 0;
}
int cmd_run(cmd_info* ci){
  // 解析参数，全部保存到一个特定的内存，运行时解析
  // 对于所有参数，根据参数类型解析
  // if int,int a = atoi,memcpy;if string,memcpy
  return 0;
}

int test_func(char* c,int* a,int* b){
    printf("%c,%d,%d\n",*c,*a,*b);
    return 0;
}

int main(){
  *(char*)g_buf = 'A';
  *(int*)(g_buf+1) = 200;
  *(int*)(g_buf+5) = 566;
  cmd_info acmd = {
    "test",
    {1,4,4,0},
    (char*)g_buf
  };
  (void)test_func(acmd.buf,acmd.buf+1,acmd.buf+5);

  return 0;
}
