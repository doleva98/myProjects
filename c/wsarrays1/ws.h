#ifndef WSARRAYS1_H
#define WSARRAYS1_H

void sumMatrix(int r, int c, int* mat, int* res);
void testsumMatrix();

void testJoesphos();
int Joesphos(int num);
int killThem(int* arr, int* num_group, int num, int* kill);

void printToStdOut();
void foo(int (*a)[4], int r);

void CopyEnvp(char** envp);
char* StrCpyEnvp(char* destination, const char* source);
char *StrDupEnvp(const char *str);
int sizeOfArray(char** arr);
void freeAll(char** buffer);

#endif
