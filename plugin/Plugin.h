#ifndef __JX_PLUGIN__
#define __JX_PLUGIN__

#define MAX_CMD_NAME_SIZE 20
#define MAX_CMD_NAME_LEN 19
#define MAX_PARA_NUM 9+1

extern Command g_CmdList[100];
extern int g_CmdSize;


typedef enum {
    CPT_NULL,
    CPT_DIGIT,
    CPT_STRING
} CMD_PARA_TYPE;

typedef struct {
    char name[MAX_CMD_NAME_SIZE];
    CMD_PARA_TYPE para_type[MAX_PARA_NUM];
    void* handler;
} Command;

void CmdExec(const char* name,const char* para_str);


#endif // __JX_PLUGIN__
