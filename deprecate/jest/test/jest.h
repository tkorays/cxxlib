#ifndef __JEST_INCLUDE_H__
#define __JEST_INCLUDE_H__

#include <assert.h>



// 将测试函数导出，便于外部调用测试
#ifdef __cplusplus
#define JEST_API extern "C" __declspec(dllexport) int __stdcall
#define JEST_VAL extern "C" __declspec(dllexport) 
#else
#define JEST_API __declspec(dllexport) int __stdcall
#define JEST_VAL __declspec(dllexport) 
#endif



#define JEST_RET int
#define JEST_SUC 1
#define JEST_ERR 0
#define JEST_PASS 1
#define JEST_FAIL 0

#ifdef assert
#undef assert
#endif

#define JEST_MAX_CASES 20
#define JEST_CASE_NAME_SIZE 20

#define JEST_CASE(CaseName) JEST_API JEST_##CaseName(void)
#define JEST_RUN(CaseName) JEST_##CaseName()
#define JEST_REGISTER(n) JEST_VAL int JEST_CaseSize = n;JEST_VAL char JEST_CaseList[][JEST_CASE_NAME_SIZE] =




#endif // __JEST_INCLUDE_H__
