#include <stdio.h>
#include <string.h>

void print_hello()
{
   printf("\x22\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x21\x22");
}

int pow_ten(int n)
{
   int i = 0;
   int result = 1;
   for(; i < n; i++){
      result = result*10;
   }

   return result;
}

int flip(int n)
{
   int result = 0;
   int input = n;
   while (n != 0)
   {
      result = result*10 + n%10;
      n = n/10;
   }
   printf("%d", result);
   return result;
   
}

void swap(int* var_one, int* var_two){
   int temp = *var_one;
   *var_one = *var_two;
   *var_two = *var_one;
}




int main()
{

  int a = 1, b = 1 ,c = 2;

   printf("%d", a);
   return 0;
}

