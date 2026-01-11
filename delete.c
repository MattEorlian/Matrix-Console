#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "head.h"
#include "function.h"

status delete(context* idx)
{
	//ÊäÈëÃû³Æ
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;

	//
	matrix* lst = idx->matList;
	int len = idx->matCnt;

	//É¾³ý
	delMat(&lst[pos]);
	int i;
	for (i = pos; i < len - 1; i++)
	{
		uniSwap(&lst[i], &lst[i + 1],sizeof(lst[0]));
	}
	idx->matCnt--;
	return SUCCESS;
}

command cmd_delete = { "del",delete,"delete matrix" };