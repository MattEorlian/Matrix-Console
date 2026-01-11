#include "head.h"
#include "function.h"
#include<stdio.h>
#include<string.h>

status help(context* idx)
{
	puts("help with ?>> (function name) or (\"all\" for all information.)");
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));

	//用户输入，我们需要去除头部空格
	char* str = buffer;
	while (*str == ' ') str++;//这样我们就找出了第一个非空格的位置
	removeTailBlk(str);

	if (str[0] == '\0') return INVALID_INPUT;

	commandSet* cs = (commandSet*)idx->cmds;

	//如果输入all
	if (strcmp(str, "all") == 0)
	{
		puts("Name\t|\tDescription");
		int i;
		for (i = 0; i < cs->size; i++)
		{
			puts("-------------------------------------");
			printf("%s\t|\t%s\n", cs->cmd[i]->name, cs->cmd[i]->help);
		}
		return SUCCESS;
	}

	int i;
	for (i = 0; i < cs->size; i++)
	{
		if (strcmp(cs->cmd[i]->name, str) == 0)
		{
			puts(cs->cmd[i]->help);
			break;
		}
	}
	if (i == cs->size)
	{
		return DST_NOT_FOUND;
	}
	return SUCCESS;
}

command cmd_help = { "help",help,"get help with any functions" };