#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


#include "head.h"
#include "function.h"


status getName(matrix* m)
{
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	if (str[0] == '\0')  return INVALID_INPUT;//用户输入全空格
	removeTailBlk(str);
	if (strlen(str) >= MAX_NAME - 1) return NAME_TOO_LONG;
	strcpy(m->name, str);
	return SUCCESS;
}

status getSize(int* x)
{
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	if (parseInt(buffer, x) == 0) return INVALID_INPUT;
	if (*x <= 0) return INVALID_INPUT;
	if (*x > MAX_ROW) return MAT_SIZE_EXD;
	return SUCCESS;
}

status getMatrix(matrix* m)
{
	m->arr = (frac**)malloc2dArr(m->r, m->c, sizeof(m->arr[0][0]));
	if (m->arr == NULL) return MEMORY_FAIL;
	char buffer[MAX_BUFFER];
	int i;
	for (i = 0; i < m->r; i++)
	{
		getLine(buffer, sizeof(buffer));
		int j;
		char* str = buffer;
		for (j = 0; j < m->c; j++)
		{
			int len = parseFrac(str, &(m->arr[i][j]));
			if (len == 0)
			{
				delMat(m);
				return LACK_INDEX;
			}
			simFrac(&(m->arr[i][j]));
			str += len;
		}
	}
	return SUCCESS;
}

status new_matrix(context* idx)
{
	status s;
	//检查是否还有多余空间
	if (idx->matCnt >= MAX_MATRIX - 1) return MEMORY_FAIL;

	matrix tmp;

	//获取名字
	puts("name>> (string shorter than 104)");
	s = getName(&tmp);
	if (s != SUCCESS) return s;
	if (searchMat(idx->matList, idx->matCnt, tmp.name) != -1)
	{
		//检查是否重名
		return REPEAT_NAME;
	}
	
	//输入行和列
	puts("row>> (integar less than 20)");
	s = getSize(&(tmp.r));
	if (s != SUCCESS)
	{
		return s;
	}

	puts("col>> (integar less than 20)");
	s = getSize(&(tmp.c));
	if (s != SUCCESS)
	{
		return s;
	}

	//输入矩阵
	printf("matrix>> (a %d*%d matrix)\n", tmp.r, tmp.c);
	s = getMatrix(&tmp);
	if (s != SUCCESS)
	{
		return s;
	}

	//最后载入矩阵
	memcpy(&idx->matList[idx->matCnt], &tmp, sizeof(matrix));
	idx->matCnt++;
	return SUCCESS;
}


command cmd_newMatrix = { "new",new_matrix,"create a new matrix in the list.You might input several fractions(integars are also allowed) in one row, in the format of a/b or -a/b\n" };