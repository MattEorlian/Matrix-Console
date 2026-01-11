#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status mul(context* idx)
{
	//¼ì²éÊ£Óà¿Õ¼ä
	if (idx->matCnt >= MAX_MATRIX - 1) return LIST_FULL;
	

	//ÊäÈë¾ØÕó
	puts("left matrix>>(name)");
	int p1 = getMatPos(idx->matList, idx->matCnt);
	if (p1 == -1) return DST_NOT_FOUND;
	else if (p1 == -2) return INVALID_INPUT;
	matrix* m1 = &idx->matList[p1];

	puts("right matrix>>(name)");
	int p2 = getMatPos(idx->matList, idx->matCnt);
	if (p2 == -1) return DST_NOT_FOUND;
	else if (p2 == -2) return INVALID_INPUT;
	matrix* m2 = &idx->matList[p2];


	//¼ì²éÃüÃû¿Õ¼ä
	if (strlen(m1->name) + strlen(m2->name) + 1 >= MAX_NAME - 1)
	{
		return NAME_TOO_LONG;
	}

	//
	matrix tmp = { 0 };
	status s = matMul(&tmp, m1, m2);
	if (s != SUCCESS) return s;

	tmp.name[0] = '\0';
	int len = strCat(tmp.name, MAX_NAME, m1->name);
	if (len == MAX_NAME - 1) return NAME_TOO_LONG;
	tmp.name[len++] = '*';
	tmp.name[len] = '\0';
	strCat(tmp.name, MAX_NAME, m2->name);
	if (searchMat(idx->matList, idx->matCnt, tmp.name) != -1)
	{
		delMat(&tmp);
		return REPEAT_NAME;
	}
	memcpy(&idx->matList[idx->matCnt++], &tmp, sizeof(tmp));
	printf("the result saved as %s\n", tmp.name);
	return SUCCESS;
}

command cmd_mul = { "mul",mul,"get the product of two matrix.The result will be saved in a new_matrix.\n\
Note:If there is a\"name too long\",you'd better rename one matrix with a shorter name." };