#include "jest.h"
#include <stdio.h>

JEST_CASE(heh){
	printf("I'm a test case.\n");
	return JEST_PASS;
}
JEST_CASE(xuzhibo){
	printf("i'm xuuzhibo\n");
	return JEST_FAIL;
}
JEST_REGISTER(2) {
	"heh", // _JEST_heh@0
	"xuzhibo" // _JEST_xuzhibo@0
};

