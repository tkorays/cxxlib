#include <stdio.h>
#include <Windows.h>

typedef int(*testFunc)(void);

int main(){
    HMODULE h = LoadLibraryA("test");
    if(!h){
        printf("load dll error\n");
        return 0;
    }

    int funcCount = *(int*)GetProcAddress(h,"JEST_CaseSize");
    const char* funcNames = (const char*)GetProcAddress(h,"JEST_CaseList");
    char tmp[100];
    for(int i=0;i<funcCount;i++){
        _snprintf(tmp,100,"_JEST_%s@0",funcNames+i*20);
        testFunc f = (testFunc)GetProcAddress(h,tmp);
        int result = f();
        printf("result: %d\n",result);
    }
    return 0;

}

