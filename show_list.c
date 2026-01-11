#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "function.h"

status showList(context* idx)
{
	if (idx->matCnt == 0)
	{
		puts("Empty.");
		return SUCCESS;
	}
	printf("%d matrix in total\n", idx->matCnt);
	int i;
	puts("name\t|\tsize");
	for (i = 0; i < idx->matCnt; i++)
	{
		puts("---------------------------------------");
		printf("%s\t|%d*%d\n", idx->matList[i].name, idx->matList[i].r, idx->matList[i].c);
	}
	return SUCCESS;
}

command cmd_showList = { "show_list",showList,"show all matrix in the list\n" };