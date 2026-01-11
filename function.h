#pragma once

#include<stdio.h>
#include "head.h"

extern void uniSwap(const void* pointer_1, const void* pointer_2, size_t size_of_element);
extern long long gcd(long long a, long long b);
extern long long lcm(long long a, long long b);
extern void** malloc2dArr(int row, int col, size_t size);
extern void free2dArr(void** arr, int row);
extern char* getLine(char* dst, size_t size);
extern char* fgetLine(char* dst, size_t size, FILE* file);
extern void bugReport(status s);
extern int parseLL(char* src, ll* dst);
extern int parseInt(char* src, int* dst);
extern int parseFrac(char* src, frac* dst);
extern int searchMat(matrix* arr, int size, char* str);
extern void delMat(matrix* m);
extern char* NotBlank(char* str);
extern void removeTailBlk(char* str);
extern void quickPrint(matrix* m);
extern void fquickPrint(matrix* m, FILE* s);
extern void printFrac(frac* f);
extern void fprintFrac(frac* f, FILE* s);
extern void simFrac(frac* dst);
extern void sprintFrac(char* dst, frac* f);
extern void printMatrix(matrix* m);
extern void swapRow(matrix* m, int r1, int r2);
extern void swapCol(matrix* m, int c1, int c2);
extern int getInt(int* p);
extern int fgetInt(int* p, FILE* file);
extern int getFrac(frac* f);
extern int fgetFrac(frac* f, FILE* file);
extern int getMatPos(matrix* list, int size);//用户输入矩阵我们返回矩阵位置，集成度较高
extern frac fadd(frac f1, frac f2);
extern frac fsub(frac f1, frac f2);
extern frac fmul(frac f1, frac f2);
extern frac minus(frac f);
extern frac opp(frac f);
extern void rowAdd(matrix* m, int r0, int r, frac k);
extern void colAdd(matrix* m, int c0, int c, frac k);
extern void simMat(matrix* m);
extern void simRow(matrix* m, int r);
extern void simCol(matrix* m, int c);
extern status matCpy(matrix* dst, matrix* src);
extern void rowMul(matrix* m, int row, frac f);
extern void colMul(matrix* m, int col, frac f);
status matMul(matrix* dst, matrix* a, matrix* b);
extern int strCat(char* dst, int size, char* src);
extern status matMulC(matrix* m, frac k);
extern status matAdd(matrix* dst, matrix* a, frac ka, matrix* b, frac kb);