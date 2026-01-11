#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

#include "head.h"
#include "function.h"
#include "cmd.h"

//For debugging.
#define T freopen("test.in","r",stdin)
#define O freopen("ret.out","w",stdout)

commandSet cmdSet = { 20,
	&cmd_exitConsole,
	&cmd_help,
	&cmd_clear,
	&cmd_newMatrix,
	&cmd_copy,
	&cmd_delete,
	&cmd_showMatrix,
	&cmd_showList,
	&cmd_swapR,
	&cmd_swapC,
	&cmd_renameMat,
	&cmd_open,
	&cmd_saveMat,
	&cmd_addR,
	&cmd_addC,
	&cmd_mulR,
	&cmd_mulC,
	&cmd_mul,
	&cmd_mulFrac,
	&cmd_addM
};

context idx;

const frac E = { 1,1 };
const frac Z = { 0,1 };

//功在当代，利在千秋

int main()
{
	//T;
	idx.endFlag = 0;
	idx.cmds =(void*) & cmdSet;
	char buffer[MAX_BUFFER];
	while (idx.endFlag == 0)
	{
		//UI
		puts("--------------MATRIX CONSOLE--------------");
	 
		//
		getLine(buffer, sizeof(buffer));
		char* str = NotBlank(buffer);
		removeTailBlk(str);
		int i;
		for (i = 0; i < cmdSet.size; i++)
		{
			if (strcmp(str, cmdSet.cmd[i]->name) == 0)
			{
				
				status s = (cmdSet.cmd[i]->cmdFunc)(&idx);
				bugReport(s);
				break;
			}
		}
		if (i == cmdSet.size) puts("No such Command.Enter \"help\" for more information.");
	}
	return 0;
}

//Total code length 1848