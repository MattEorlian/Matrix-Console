#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status mulR(context* idx)
{
	//寻找矩阵
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//输入行数
	puts("row>>(row)");
	int r;
	if (getInt(&r) == 0 || r < 1 || r > m->r)
	{
		return INVALID_INPUT;
	}

	//输入倍数
	puts("multiply with>>(fraction)");
	frac f;
	if (getFrac(&f) == 0) return INVALID_INPUT;

	//
	rowMul(m, r - 1, f);
	return SUCCESS;
}

command cmd_mulR = { "mul_row",mulR,"multiply a row with a fraction" };