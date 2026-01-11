#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status copy(context* idx)
{
	//寻找矩阵
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;

	//检查是否有多余空间
	if (idx->matCnt >= MAX_MATRIX - 1)
	{
		return MEMORY_FAIL;
	}

	//复制
	status s;
	if ((s = matCpy(&idx->matList[idx->matCnt++], &idx->matList[pos]))
		!= SUCCESS)
	{
		return s;
	}
	printf("%s copied as \"%s\"\n", idx->matList[pos].name, idx->matList[idx->matCnt - 1].name);
	return SUCCESS;
}

command cmd_copy = { "copy",copy,"Make a new copy of matrix.If you copy A, you will get A_copy.\n\
If there is \"name is too long\"message, you'd better rename the matrix with a shorter name." };