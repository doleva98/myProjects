#include <stdio.h>
#include <stdlib.h>
#include "ws.h"
#include <string.h>
#include "/home/dolev/git/dolev-arev/include/utils.h"


int main(int argv, char** argc, char** envp) {
	int arr [2][4] = {{1,23,4,5},
			  {3,4,5,6}};
	testsumMatrix();
	testJoesphos();
	printToStdOut();
	
	
	foo(arr, 2);
   	return 0;
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

int Joesphos(int num){
	int num_group = num;
	int i = 0;
	int j = 0;
	int res = -1;
	int* arr = NULL;
	int kill = 0;
	
	arr = (int*)malloc(num*sizeof(int));
	if(!arr){
		return -1;
	}
	
	for(; i < num; ++i){
		arr[i] = i+1;
	}
	
	while(num_group != 1){
		killThem(arr, &num_group, num, &kill);
	}	
	
	for(; j < num; ++j){
		if(arr[j] != -1){
			res = arr[j];
		}
	}
	FREE(arr);
	return res;
}

void killThem(int* arr, int* num_group,int num, int* kill){
	int i = 0;
	int count = 0;
	for(; i < num ;++i){
		if(arr[i] != -1){
			if(*kill == 0){
			
				++count;
				*kill = 1;
			}else{
				arr[i] = -1;
				*kill = 0;
			}
		}else{
			continue;
		}
	}
	*num_group = count;
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

