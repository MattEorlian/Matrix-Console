#pragma once

#define MAX_BUFFER 2005
#define MAX_ROW 20
#define MAX_COL 20
#define MAX_MATRIX 105
#define MAX_COMMAND 55
#define MAX_STEP 10
#define MAX_NAME 105
#define PARSE_FAIL 0
#define MAX_FRAC_LEN 40


typedef long long ll;
typedef unsigned long long ull;

typedef enum FUNCSTATUS
{
	SUCCESS,
	OTHER_ERROR,
	INVALID_INPUT,
	MEMORY_FAIL,
	DIV_BY_ZERO,
	INVALID_ADDRESS,
	DATA_TYPE_MAXOUT,
	DST_NOT_FOUND,
	REPEAT_NAME,
	MAT_SIZE_EXD,
	NAME_TOO_LONG,
	LACK_INDEX,
	FILE_PATH_INVALID,
	FATAL_ERROR,
	INVALID_INDEX,
	LIST_FULL,
}status;//函数的返回值，用于生成报错信息

typedef struct FRACTION
{
	ll num;
	ll den;
}frac;//矩阵的元素——分数

typedef struct MATRIX
{
	char name[MAX_NAME];
	int r;
	int c;
	frac** arr;
}matrix;


typedef struct CONTEXT
{
	matrix* dst;//操作单个矩阵的指针
	int matCnt;//矩阵数量
	matrix matList[MAX_MATRIX];//矩阵列表
	int endFlag;//退出信号
	void* cmds;//指令集的指针，主要用于输出帮助文本
}context;//参数集

typedef struct COMMAND
{
	char* name;
	status (*cmdFunc)(context* idx);
	char* help;//帮助信息
}command;//命令

typedef struct COMMAND_LIST
{
	int size;
	command* cmd[MAX_COMMAND];
}commandSet;//命令集（存储命令指针）

extern const frac E;
extern const frac Z;