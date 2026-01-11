#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"

status swapR(context* idx)
{
	//输入名字
	puts("name>>(matrix name)");
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	removeTailBlk(str);
	if (str[0] == '\0') return INVALID_INPUT;

	//搜索
	int pos = searchMat(idx->matList, idx->matCnt, str);
	if (pos == -1) return DST_NOT_FOUND;
	matrix* m = &idx->matList[pos];

	//输入两行
	int r1, r2;
	puts("row1>>(an integar)");
	if (getInt(&r1) == 0 || r1 <= 0 || r1 > m->r) return INVALID_INPUT;
	puts("row2>>(an integar)");
	if (getInt(&r2) == 0|| r2 <= 0 || r2 > m->r) return INVALID_INPUT;
	
	//
	if (r1 == r2) return SUCCESS;
	swapRow(m, r1 - 1,  r2 - 1);
	return SUCCESS;
}

command cmd_swapR = { "swap_row",swapR,"swap 2 rows in a matrix" };