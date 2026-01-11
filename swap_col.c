#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"

status swapC(context* idx)
{
	//Ñ¡Ôñ¾ØÕó
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//ÊäÈëÁÐ
	int c1, c2;
	puts("col1>>(an integar)");
	if (getInt(&c1) == 0 || c1 <= 0 || c1 > m->c) return INVALID_INPUT;
	puts("col2>>(an integar)");
	if (getInt(&c2) == 0 || c2 <= 0 || c2 > m->c) return INVALID_INPUT;

	//
	if (c1 == c2) return SUCCESS;
	swapCol(m, c1 - 1, c2 - 1);
	return SUCCESS;
}

command cmd_swapC = { "swap_col",swapC,"swap 2 columns in a matrix" };