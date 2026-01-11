#include "head.h"
#include<stdio.h>

status exitConsole(context* idx)
{
	idx->endFlag = 1;
	return SUCCESS;
}

command cmd_exitConsole = { "exit" ,exitConsole,"Enter \"exit\" to quit the program" };