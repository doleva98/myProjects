#include <stdio.h>
#include <stdlib.h>
#include "ws.h"
#include <string.h>
#include <ctype.h>
#include "/home/dolev/git/dolev-arev/include/utils.h"
#include <assert.h>

int main(int argv, char** argc, char** envp) {
	int arr [2][4] = {{1,23,4,5},
			  {3,4,5,6}};
	testsumMatrix();
	testJoesphos();
	printToStdOut();
	foo(arr, 2);
	CopyEnvp(envp);
	
	
   	return 0;
}

void CopyEnvp(char** envp){
	char** buffer = NULL;
	char** start_buffer = NULL;
	assert(envp);
	
	buffer = (char**)calloc(sizeOfArray(envp)+1, sizeof(char*));
	if(!buffer){
		return;
	}
	
	start_buffer = buffer;
	while(*envp){
		*buffer = StrDupEnvp(*envp);
		++buffer;
		++envp;
	}
	freeAll(start_buffer);
}	

void freeAll(char** buffer){
	char** start = NULL;
	assert(buffer);
	
	start = buffer;
	while(*buffer){
		FREE(*buffer);
		buffer++;
	}
	FREE(start);
}

char* StrCpyEnvp(char* destination, const char* source)
{
	char *result = destination;
	assert(destination != NULL && source != NULL);
	
	while(*source)
	{
		*destination = tolower(*source);
		source++;
		destination++;
	}
	
	*destination = '\0';
	
	return result;
}


char *StrDupEnvp(const char *str){
	
	char* result = NULL; 
	assert(str != NULL);
	
	result = (char*)malloc(strlen(str) + 1);
	if(result == NULL){
		return NULL;
	}
	
	StrCpyEnvp(result, str);
	printf("%s\n", result);
	return result;
	
}

int sizeOfArray(char** arr){
	int size = 0;
	assert(arr);
	
	while(*arr){
		++size;
		++arr;
	}
	return size;
}

void foo(int (*a)[4], int r){
	int i,j;
	for(i = 0; i < r; ++i){
		
		for(j = 0; j < 4; ++j){
			printf("%d ", a[i][j]);
		}	
		printf("\n");
		
	}
}

void printToStdOut(){
	fprintf(stdout, "the size of %s is %lu\n", "char", sizeof(char));
	fprintf(stdout, "the size of %s is %lu\n", "int", sizeof(int));
	fprintf(stdout, "the size of %s is %lu\n", "float", sizeof(float));
	fprintf(stdout, "the size of %s is %lu\n", "unsigned long int", sizeof(unsigned long int));
}

void testJoesphos(){
	ASSERT(37 == Joesphos(50));
	ASSERT(7 == Joesphos(35));
	ASSERT(5 == Joesphos(10));
}

int Joesphos(int num){ /* many num in code. should be more indicative */
	int res = -1;
	int* arr = NULL;
	int kill = 0;
	int num_group = 0;
	if(num <= 0){
		return -1;
	}
	num_group = num; /* hard to understand what this int means */
	
	
	arr = (int*)calloc(num,sizeof(int)); /* why not using calloc? */
	if(!arr){
		return -1;
	}
		
	while(num_group != 1){
		res = killThem(arr, &num_group, num, &kill);
	}	
	
	FREE(arr);
	return res;
}

int killThem(int* arr, int* num_group,int num, int* kill){
	int i = 0;
	int count = 0;
	int ret = 0;
	for(; i < num ;++i){
		if(arr[i] != -1){ 
			if(*kill == 0){
				ret = i + 1;
				++count; 
				*kill = 1;
			}else{
				arr[i] = -1;
				*kill = 0;
			}
		}
	}
	*num_group = count;
	return ret;
}




void testsumMatrix(){
	int a [2][3] = {{1,4,3},
			{1,2,4}};
			
	int* b = (int*)calloc(2,sizeof(int));
	if(!b){
		return;
	}
	
	sumMatrix(2,3,&a[0][0], b);
	ASSERT(b[0] == 8);
	ASSERT(b[1] == 7);
	
	FREE(b);
}

void sumMatrix(int r, int c, int* mat, int* res){
	int i = 0;
	int j;
	
	for(; i < r; ++i){
	
		for(j = 0; j < c; ++j){
			res[i] += *(mat+(i*c)+j);
		}
		
	}

}

