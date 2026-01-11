#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "head.h"
#include "function.h"
#include "cmd.h"


status showMatrix(context* idx)
{
	//ÓÃ»§ÊäÈë
	puts("show>>(matrix name)");
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	if (str[0] == '\0') return INVALID_INPUT;
	removeTailBlk(str);

	//Ñ°ÕÒ¾ØÕó
	int pos = searchMat(idx->matList, idx->matCnt, str);
	if (pos == -1) return DST_NOT_FOUND;
	
	//Êä³ö¾ØÕó
	//quickPrint(&idx->matList[pos]);
	printMatrix(&idx->matList[pos]);
	return SUCCESS;
}

command cmd_showMatrix = { "show",showMatrix,"print a matrix to console" };