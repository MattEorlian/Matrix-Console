#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status mulC(context* idx)
{
	//找到矩阵
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//找到列
	puts("column>>(column)");
	int c;
	if (getInt(&c) == 0 || c<1 || c>m->c)
	{
		return INVALID_INPUT;
	}

	//输入倍数
	puts("multiply with>>(fraction)");
	frac f;
	if (getFrac(&f) == 0) return INVALID_INPUT;

	//
	colMul(m, c - 1, f);
	return SUCCESS;
}

command cmd_mulC = {"mul_col",mulC,"multiply a column with a fraction" };