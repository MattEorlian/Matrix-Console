#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include "head.h"
#include "function.h"

status clear(context* idx)
{
#ifdef _WIN32
    system("cls");
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(hStdOut, coord);
#else
    system("clear");
    printf("\033[1;1H");
#endif
    fflush(stdout);
    return SUCCESS;
}

command cmd_clear = { "clear",clear,"clear console.(Your data will be saved)" };