#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"


status renameMat(context* idx)
{
	puts("name>>(matrix name)");
	int pos = getMatPos(idx->matList, idx->matCnt);
	if (pos == -2) return INVALID_INPUT;
	if (pos == -1) return DST_NOT_FOUND;
	
	puts("new name>>(string shorter than 104)");
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	removeTailBlk(str);
	if (str[0] == '\0') return INVALID_INPUT;
	if (strlen(str) >= MAX_NAME - 1) return NAME_TOO_LONG;
	if (searchMat(idx->matList, idx->matCnt, str) != -1) return REPEAT_NAME;
	strcpy(&idx->matList[pos].name, str);
	return SUCCESS;
}

command cmd_renameMat = { "rename",renameMat,"change name of a matrix" };