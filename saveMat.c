#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

status saveMat(context* idx)
{
	//选择矩阵
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -1) return DST_NOT_FOUND;
	if (pos == -2) return INVALID_INPUT;
	matrix* m = &idx->matList[pos];
	
	//输入地址
	puts("file path>>(path of your file,such as \"D:\\matrix\A.txt\")");
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	removeTailBlk(buffer);
	if (str[0] == '\0')
	{
		return INVALID_INPUT;
	}

	
	//打开文件
	FILE* file = fopen(str, "w");
	if (file == NULL) return FILE_PATH_INVALID;

	fquickPrint(m, file);

	//

	fclose(file);
	printf("Matrix saved.\n");
	return SUCCESS;
}

command cmd_saveMat = { "save",saveMat,"save matrix to your computer" };