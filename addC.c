#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status addC(context* idx)
{
	//ÕÒµ½¾ØÕó
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//
	int c0, c;
	frac k;
	puts("add to>>(column 1)");
	if (getInt(&c0) == 0 || c0 < 1 || c0 > m->c) return INVALID_INPUT;
	puts("add>>(column 2)");
	if (getInt(&c) == 0 || c < 1 || c > m->c) return INVALID_INPUT;
	puts("column 2 multiplied with>>(fraction)");
	if (getFrac(&k) == 0) return INVALID_INPUT;
	simFrac(&k);

	//
	colAdd(m, c0 - 1, c - 1, k);
	simCol(m, c0);
	return SUCCESS;
}

command cmd_addC = { "add_col",addC, "add (column c)*k to column c0. k is a fraction." };