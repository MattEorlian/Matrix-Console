#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status mulFrac(context* idx)
{
	//
	puts("name>>(name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//
	puts("multiply with>>(fraction)");
	frac k;
	if (getFrac(&k) == 0)
	{
		return INVALID_INPUT;
	}

	status s = matMulC(m, k);
	if (s != SUCCESS) return s;
	return SUCCESS;
}

command cmd_mulFrac = { "mul_frac",mulFrac,"multiply matrix with a fraction" };