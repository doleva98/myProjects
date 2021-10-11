#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void swap(int* a, int* b){

int temp = *a;
*a = *b;
*b = temp;

}

void copyArray(int a [], int b [], int len){
  int i = 0;

   for(;i < len; i++){
      b[i] = a[i];
   }
}

int StrLen(const char *str){ 
   int result = 0;  
   assert(str);   
   for(;;++result){ /*for is almost empty. why not use while? */
      if(!str[result]){
         return result; /*you have twice return*/
      }
   }
   return result;
}

int StrCmp(const char* str1, const char* str2){ 
   assert(str1);
   assert(str2);
  
   while(*str1){  /*why dont you check (*str1 && *str2)?*/
      if(*str1 != *str2){
         break;
      }
      str1++;
      str2++;
   }
   return *(const unsigned char*) str1 - *(const unsigned char*) str2; /*why do you have to change to unsinged char? you lose information if str1 is less than str2 (in original function it returns a negative value)*/
}


void swapTwoSizeT(size_t* a, size_t* b){
   size_t temp = *a;
   *a = *b;
   *b = temp;
}

void swapTwoSizeTPointers(size_t** a, size_t** b){
   size_t* temp = *a;
   *a = *b;
   *b = temp;
}

void useSwap(size_t** a, size_t** b){
	swapTwoSizeT(*a, *b);
}

int main() {
    	double d = 5;
    	int i = 12;
    	float f = 8/6;
    	unsigned int ui = 2;
    	/*+ i*(ui - i)+((float *)&d - &f )*/
    	i =  ((float *)&d - &f );
    	printf("\n%d\n", i);
    	printf("%lf\n",*(double *)(&f+3));
	
   return 0;
}
