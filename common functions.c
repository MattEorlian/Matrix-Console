#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "head.h"
#include "function.h"

// 定义 max 宏
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

void uniSwap(const void* p1, const void* p2, size_t size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		char byte;
		byte = *((char*)p1 + i);
		*((char*)p1 + i) = *((char*)p2 + i);
		*((char*)p2 + i) = byte;
	}
}

long long gcd(long long a, long long b)
{
	long long temp;
	while (a % b != 0)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
	return b;
}

long long lcm(long long a1, long long b1)
{
	long long temp, a = a1, b = b1;
	while (a % b != 0)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
	return a1 / b * b1;
}

void** malloc2dArr(int row, int col,size_t size)
{
	void** ret;
	ret = (void**)malloc(row * sizeof(void*));
	if (ret == NULL)
	{
		return NULL;
	}
	int i;
	for (i = 0; i < row; i++)
	{
		if ((ret[i] = malloc(col * size)) == NULL)
		{
			int j;
			for (j = 0; j < i; j++) free(ret[j]);
			return NULL;
		}
	}
	return ret;
}

void free2dArr(void** arr, int row)
{
	if (arr == NULL) return;
	int i;
	for (i = 0; i < row; i++)
	{
		if (*(arr + i) != NULL)
		{
			free(*(arr + i));
		}
	}
	free(arr);
}

char* getLine(char* dst, size_t size)
{
	char* ret = fgets(dst, size, stdin);
	int len = strlen(dst);
	if (len == 0) return NULL;
	if (dst[len - 1] == '\n') dst[len - 1] = '\0';
	else//说明输入的字符串超过了缓冲长度，需要清除缓存
	{
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	}
	return ret;
}

char* fgetLine(char* dst, size_t size,FILE* s)
{
	char* ret = fgets(dst, size,s);
	int len = strlen(dst);
	if (len == 0) return NULL;
	if (dst[len - 1] == '\n') dst[len - 1] = '\0';
	else//说明输入的字符串超过了缓冲长度，需要清除缓存
	{
		char ch;
		while ((ch = fgetc(s)) != '\n' && ch != EOF);
	}
	return ret;
}

void bugReport(status s)
{
	switch (s)
	{
	case SUCCESS:
		break;
	case OTHER_ERROR:
		puts("Other Error");
		break;
	case MEMORY_FAIL:
		puts("Memory fail.");
		break;
	case DIV_BY_ZERO:
		puts("Divided by zero.");
		break;
	case INVALID_ADDRESS:
		puts("Invalid pointer used.");
		break;
	case DATA_TYPE_MAXOUT:
		puts("Data maxout.");
		break;
	case DST_NOT_FOUND:
		puts("Cannot find object.");
		break;
	case REPEAT_NAME:
		puts("This name has been used.");
		break;
	case MAT_SIZE_EXD:
		puts("This matrix is too large.");
		break;
	case NAME_TOO_LONG:
		puts("This name is too long.");
		break;
	case LACK_INDEX:
		puts("Lack index.");
		break;
	case INVALID_INPUT:
		puts("Invalid input");
		break;
	case FATAL_ERROR:
		puts("Oops, we've  encountered a fatal error.Please quit the program and try again.");
		break;
	case FILE_PATH_INVALID:
		puts("The file path is invalid.");
		break;
	case INVALID_INDEX:
		puts("Invalid arguments.");
		break;
	case LIST_FULL:
		puts("No space for new matrix.");
		break;
	default:
		puts("Unknown Error.");
	}
}

int parseLL(char* src, ll* dst)//从src开头开始解析一个long long，最后返回这个long long在src中的长度（从src头开始计算，算到long long的最后一个字符）
{
	int i = 0;
	ll sgn = 1;
	while (src[i] != '\0' && src[i] == ' ') i++;
	if (src[i] == '\0') return 0;//解析失败
	if (src[i] == '-')
	{
		i++;
		sgn = -1;
	}
	while (src[i] != '\0' && src[i] == ' ') i++;
	if ('0' <= src[i] && src[i] <= '9')
	{
		if (sscanf(src + i, "%lld", dst) != 1) return 0;
		(*dst) *= sgn;
		while (('0' <= src[i] && src[i] <= '9')) i++;
		return i;
	}
	else return 0;
}

int parseInt(char* src, int* dst)//从src开头开始解析一个int，最后返回这个int在src中的长度（从src头开始计算，算到long long的最后一个字符）
{
	int i = 0;
	int sgn = 1;
	while (src[i] != '\0' && src[i] == ' ') i++;
	if (src[i] == '\0') return 0;//解析失败
	if (src[i] == '-')
	{
		i++;
		sgn = -1;
	}
	while (src[i] != '\0' && src[i] == ' ') i++;
	if ('0' <= src[i] && src[i] <= '9')
	{
		if (sscanf(src + i, "%d", dst) != 1) return 0;
		(*dst) *= sgn;
		while (('0' <= src[i] && src[i] <= '9')) i++;
		return i;
	}
	else return 0;
}

int parseFrac(char* src, frac* dst)//从src开头开始解析一个分数，最后返回这个分数在src中的长度（从src头开始计算，算到分数的最后一个字符）
{	
	int len;
	int i;
	len = i = parseLL(src, &dst->num);
	if (i == 0) return 0;
	//此时src[i]已经到了数字后面一位
	while (src[i] != '\0' && src[i] == ' ') i++;
	if (src[i] != '/')
	{
		dst->den = 1;
		return len;
	}
	else if (src[++i] == '\0')
	{
		dst->den = 1;
		return len;
	}
	else
	{
		int len2 = parseLL(src + i, &dst->den);
		if (dst->den == 0) return 0;
		if (len2 == 0)
		{
			return 0;//输入非法
		}
		else
		{
			return i + len2;
		}
	}
}

int searchMat(matrix* arr, int size, char* str)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (strcmp(arr[i].name, str) == 0)
		{
			return i;
		}
	}
	return -1;
}

void delMat(matrix* m)
{
	m->name[0] = '\0';
	free2dArr((void**)m->arr, m->r);
	m->r = 0;
	m->c = 0;
}

char* NotBlank(char* str)//返回第一个不是空格的指针，全是空格返回NULL
{
	int i = 0;
	while (str[i] != '\0' && str[i] == ' ') i++;
	return str + i;
}

void removeTailBlk(char* str)
{
	int len = strlen(str);
	int i = len - 1;
	while (i>=0 && str[i] == ' ') i--;
	str[i + 1] = '\0';
}

void printFrac(frac* f)
{
	if (f->den == 1) printf("%lld", f->num);
	else
	{
		printf("%lld/%lld", f->num,f->den);
	}
}

void fprintFrac(frac* f, FILE* s)
{
	if (f->den == 1) fprintf(s, "%lld", f->num);
	else
	{
		fprintf(s, "%lld/%lld", f->num, f->den);
	}
}

void quickPrint(matrix* m)
{
	if (m->arr == NULL)
	{
		printf("Invalid request\n");
		return;
	}
	printf("%s\n%d\n%d\n", m->name, m->r, m->c);
	int i;
	for (i = 0; i < m->r; i++)
	{
		if (m->arr[i] == NULL)
		{
			printf("Invalid request\n");
			return;
		}
		int j;
		for (j = 0; j < m->c; j++)
		{
			printFrac(&m->arr[i][j]);
			putchar(' ');
		}
		putchar('\n');
	}

}

void fquickPrint(matrix* m,FILE* s)
{
	if (m->arr == NULL)
	{
		printf("Invalid request\n");
		return;
	}
	fprintf(s,"%s\n%d\n%d\n", m->name, m->r, m->c);
	int i;
	for (i = 0; i < m->r; i++)
	{
		if (m->arr[i] == NULL)
		{
			printf("Invalid request\n");
			return;
		}
		int j;
		for (j = 0; j < m->c; j++)
		{
			fprintFrac(&m->arr[i][j], s);
			fputc(' ', s);
		}
		fputc('\n', s);
	}

}

void simFrac(frac* dst)
{
	if (dst->den == 0) return;
	if (dst->num == 0)
	{
		dst->den = 1;
		return;
	}
	if (dst->den < 0)
	{
		dst->den *= -1LL;
		dst->num *= -1LL;
	}
	ll g = gcd(llabs(dst->num), llabs(dst->den));
	dst->den /= g;
	dst->num /= g;
}

void sprintFrac(char* dst, frac* f)//把分数打印到字符串，并且返回字符串长度
{
	if (f->den == 0)
	{
		sprintf(dst, "nan\0");
		return;
	}
	if (f->den == 1LL)
	{
		sprintf(dst, "%lld\0", f->num);
		return;
	}
	if (f->den == -1LL)
	{
		sprintf(dst, "%lld\0", -f->num);
		return;
	}
	sprintf(dst,"%lld/%lld\0", f->num, f->den);
}

void printMatrix(matrix* m)
{
	if (m == NULL || m->arr == NULL) return;
	printf("name: %s\tsize:%d*%d\n", m->name, m->r, m->c);
	char buffer[MAX_ROW][MAX_COL][MAX_FRAC_LEN];//？
	int i;
	for (i = 0; i < m->r; i++)
	{
		int j;
		for (j = 0; j < m->c; j++)
		{
			sprintFrac(buffer[i][j], &m->arr[i][j]);
		}
	}

	//计算最大列宽
	int width[MAX_COL] = { 0 };
	for (i = 0; i < m->c; i++)
	{
		int j;
		for (j = 0; j < m->r; j++)
		{
			width[i] = max(width[i], strlen(buffer[j][i]));
		}
	}

	//
	for (i = 0; i < m->r; i++)
	{
		int j;
		for (j = 0; j < m->c; j++)
		{
			printf("%*s", width[j] + 2, buffer[i][j]);
		}
		putchar('\n');
	}
}

void swapRow(matrix* m, int r1, int r2)
{
	if (m == NULL||m->arr == NULL) return;
	if (r1 < 0 || r1 >= m->r) return;
	if (r2 < 0 || r2 >= m->r) return;
	if (r1 == r2) return;
	uniSwap(&m->arr[r1], &m->arr[r2], sizeof(void*));
}

void swapCol(matrix* m, int c1, int c2)
{
	if (m == NULL || m->arr == NULL) return;
	if (c1 < 0 || c1 >= m->c) return;
	if (c2 < 0 || c2 >= m->c) return;
	if (c1 == c2) return;
	int i;
	for (i = 0; i < m->r; i++)
	{
		uniSwap(&m->arr[i][c1], &m->arr[i][c2], sizeof(m->arr[0][0]));
	}
}

int getInt(int* p)
{
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	return parseInt(buffer, p);
}

int fgetInt(int* p, FILE* s)
{
	char buffer[MAX_BUFFER];
	fgetLine(buffer, sizeof(buffer), s);
	return parseInt(buffer, p);
}

int getFrac(frac* f)
{
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	return parseFrac(buffer, f);
}

int fgetFrac(frac* f, FILE* s)
{
	char buffer[MAX_BUFFER];
	fgetLine(buffer, sizeof(buffer), s);
	return parseFrac(buffer, f);
}

int getMatPos(matrix* list,int size)//非法输入返回-2，找不到返回-1
{
	char buffer[MAX_BUFFER];
	getLine(buffer, sizeof(buffer));
	char* str = NotBlank(buffer);
	removeTailBlk(str);
	if (str[0] == '\0')
	{
		return -2;//与找不到目标区分
	}
	return searchMat(list, size, str);
}

//分数计算系列

frac Frac(ll num, ll den)
{
	frac f;
	f.num = num;
	f.den = den;
	return f;
}

frac fadd(frac f1, frac f2)
{
	frac f;
	f.den = f1.den * f2.den;
	f.num = f1.num * f2.den + f2.num * f1.den;
	simFrac(&f);
	return f;
}

frac fsub(frac f1, frac f2)
{
	frac f;
	f.den = f1.den * f2.den;
	f.num = f1.num * f2.den - f2.num * f1.den;
	simFrac(&f);
	return f;
}

frac fmul(frac f1, frac f2)
{
	frac f;
	f.den = f1.den * f2.den;
	f.num = f1.num * f2.num;
	simFrac(&f);
	return f;
}

frac minus(frac f)//取相反数
{
	f.num = -f.num;
	simFrac(&f);
	return f;
}

frac opp(frac f)//取倒数
{
	uniSwap(&f.den, &f.num, sizeof(ll));
	simFrac(&f);
	return f;
}

void rowAdd(matrix* m, int r0, int r, frac k)
{
	if (m == NULL || m->arr == NULL) return;
	if (r0 < 0 || r0 >= m->r) return;
	if (r < 0 || r >= m->r) return;
	int i;
	for (i = 0; i < m->c; i++)
	{
		m->arr[r0][i] = fadd(m->arr[r0][i], fmul(m->arr[r][i], k));
		simFrac(&m->arr[r0][i]);
	}
}

void colAdd(matrix* m, int c0, int c, frac k)
{
	if (c0 < 0 || c0 >= m->c) return;
	if (c < 0 || c >= m->c) return;
	if (m == NULL || m->arr == NULL) return;
	int i;
	for (i = 0; i < m->r; i++)
	{
		m->arr[i][c0] = fadd(m->arr[i][c0], fmul(m->arr[i][c], k));
		simFrac(&m->arr[i][c0]);
	}
}

//

void simMat(matrix* m)
{
	if (m == NULL || m->arr == NULL) return;
	int i;
	for (i = 0; i < m->r; i++)
	{
		int j;
		for (j = 0; j < m->c; j++)
		{
			simFrac(&m->arr[i][j]);
		}
	}
}

void simRow(matrix* m,int r)
{
	if (m == NULL || m->arr == NULL) return;
	if (r < 0 || r >= m->r) return;
	int j;
	for (j = 0; j < m->c; j++) simFrac(&m->arr[r][j]);
}

void simCol(matrix* m, int c)
{
	if (m == NULL || m->arr == NULL) return;
	if (c < 0 || c >= m->c) return;
	int j;
	for (j = 0; j < m->r; j++) simFrac(&m->arr[j][c]);
}

int strCpy(char* dst, int max_size, char* src)
{
	int i = 0;
	while (src[i] != '\0' && i < max_size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return i;
}

status matCpy(matrix* dst, matrix* src)
{
	if (strlen(dst->name) == MAX_NAME - 1)
	{
		return NAME_TOO_LONG;
	}

	//复制其余信息
	int len = strCpy(dst->name, MAX_NAME, src->name);
	if (MAX_NAME - len < 6)//strlen("-copy")+'\0'=6
	{
		delMat(dst);
		return NAME_TOO_LONG;
	}
	strCat(dst->name, MAX_NAME, "_copy");
	dst->r = src->r;
	dst->c = src->c;

	//复制数组
	dst->arr = (frac**)malloc2dArr(src->r, src->c, sizeof(src->arr[0][0]));
	if (dst->arr == NULL) return MEMORY_FAIL;
	int i;
	for (i = 0; i < src->r; i++)
	{
		int j;
		for (j = 0; j < src->c; j++)
		{
			dst->arr[i][j] = src->arr[i][j];
		}
	}


	return SUCCESS;
}

void rowMul(matrix* m, int row, frac f)
{
	if (m == NULL || m->arr == NULL) return;
	if (row < 0 || row >= m->r) return;
	int i;
	for (i = 0; i < m->c; i++)
	{
		m->arr[row][i] = fmul(m->arr[row][i], f);
		simFrac(&m->arr[row][i]);
	}
}

void colMul(matrix* m, int col, frac f)
{
	if (m == NULL || m->arr == NULL) return;
	if (col < 0 || col >= m->c) return;
	int i;
	for (i = 0; i < m->r; i++)
	{
		m->arr[i][col] = fmul(m->arr[i][col], f);
		simFrac(&m->arr[i][col]);
	}
}

status matMul(matrix* dst, matrix* a, matrix* b)
{
	if (a == NULL || b == NULL
		|| a->arr == NULL || b->arr == NULL
		||dst==NULL) return INVALID_ADDRESS;
	if (a->c != b->r) return INVALID_INDEX;
	//清空内存
	delMat(dst);

	//申请内存空间
	dst->arr = (frac**)malloc2dArr(a->r, b->c, sizeof(dst->arr[0][0]));
	if (dst->arr == NULL) return MEMORY_FAIL;

	//作矩阵乘法
	dst->r = a->r;
	dst->c = b->c;
	int i;
	for (i = 0; i < a->r; i++)
	{
		int j;
		for (j = 0; j < b->c; j++)
		{
			//计算dst->arr[i][j]
			dst->arr[i][j] = Z;
			int k;
			for (k = 0; k < a->c; k++)
			{
				dst->arr[i][j] = fadd(dst->arr[i][j], fmul(a->arr[i][k], b->arr[k][j]));
				simFrac(&dst->arr[i][j]);
			}
		}
	}
	return SUCCESS;
}

int strCat(char* dst, int max_size, char* src)//更安全的strcat函数，避免了超出缓冲区
{
	int len = strlen(dst);
	int i = len;
	while (src[i - len] != '\0' && i < max_size - 1)//预留一位给结束符
	{
		dst[i] = src[i - len];
		i++;
	}
	dst[i] = '\0';
	return i;//返回新字符串长度
}

status matMulC(matrix* m, frac k)
{
	if (k.den == 0) return INVALID_INDEX;
	int i;
	for (i = 0; i < m->r; i++)
	{
		int j;
		for (j = 0; j < m->c; j++)
		{
			m->arr[i][j] = fmul(m->arr[i][j], k);
			simFrac(&m->arr[i][j]);
		}
	}
	return SUCCESS;
}

status matAdd(matrix* dst, matrix* a, frac ka, matrix* b, frac kb)
{
	if (a == NULL || a->arr == NULL
		|| b == NULL || b->arr == NULL
		|| dst == NULL) return INVALID_ADDRESS;
	if (a->r != b->r
		|| a->c != b->c
		|| ka.den == 0 || kb.den == 0)
	{
		return INVALID_INDEX;
	}
	delMat(dst);
	dst->r = a->r;
	dst->c = a->c;
	dst->arr = (frac**)malloc2dArr(dst->r, dst->c, sizeof(dst->arr[0][0]));
	if (dst->arr == NULL) return MEMORY_FAIL;
	int i;
	for (i = 0; i < dst->r; i++)
	{
		int j;
		for (j = 0; j < dst->c; j++)
		{
			frac f1, f2;
			f1 = fmul(a->arr[i][j], ka);
			f2 = fmul(b->arr[i][j], kb);
			dst->arr[i][j] = fadd(f1, f2);
			simFrac(&dst->arr[i][j]);
		}
	}
	return SUCCESS;
}