#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status addM(context* idx)
{
	if (idx->matCnt >= MAX_MATRIX - 1) return LIST_FULL;
	//输入矩阵1及倍数
	puts("matrix1>>(name)");
	int p1 = getMatPos(idx->matList, idx->matCnt);
	if (p1 == -1) return DST_NOT_FOUND;
	else if (p1 == -2) return INVALID_INPUT;
	matrix* m1 = &idx->matList[p1];

	frac k1;
	puts("multiplied with>>(fraction)");
	if (getFrac(&k1) == 0) return INVALID_INPUT;
	
	//输入矩阵2及倍数
	puts("matrix2>>(name)");
	int p2 = getMatPos(idx->matList, idx->matCnt);
	if (p2 == -1) return DST_NOT_FOUND;
	else if (p2 == -2) return INVALID_INPUT;
	matrix* m2 = &idx->matList[p2];

	frac k2;
	puts("multiplied with>>(fraction)");
	if (getFrac(&k2) == 0) return INVALID_INPUT;
	
	//
	matrix tmp = { 0 };
	status s = matAdd(&tmp, m1, k1, m2, k2);
	if (s != SUCCESS) return s;
	tmp.name[0] = '\0';
	int len = strCat(tmp.name, MAX_NAME, m1->name);
	if (len == MAX_NAME - 1) return NAME_TOO_LONG;
	strCat(tmp.name, MAX_NAME, "plus");
	strCat(tmp.name, MAX_NAME, m2->name);
	if (searchMat(idx->matList, idx->matCnt, tmp.name) != -1)
	{
		delMat(&tmp);
		return REPEAT_NAME;
	}
	memcpy(&idx->matList[idx->matCnt++], &tmp, sizeof(tmp));
	printf("result saved as %s\n", tmp.name);
	return SUCCESS;
}

command cmd_addM = { "add",addM,"calculate sum of 2 matrix.\n\
The result will be saved as a new matrix" };