#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status addR(context* idx)
{
	//ÕÒµ½¾ØÕó
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];

	//
	int r0, r;
	frac k;
	puts("add to>>(row1)");
	if (getInt(&r0) == 0|| r0 < 1 || r0 > m->r) return INVALID_INPUT;
	puts("add>>(row2)");
	if (getInt(&r) == 0 || r<1 || r>m->r) return INVALID_INPUT;
	puts("row 2 multiplied with>>(fraction)");
	if (getFrac(&k) == 0) return INVALID_INPUT;
	simFrac(&k);

	//
	rowAdd(m, r0 - 1, r - 1, k);
	simRow(m, r0);
	return SUCCESS;
}

command cmd_addR = { "add_row",addR, "add (row r)*k to row r0, k is a fraction." };