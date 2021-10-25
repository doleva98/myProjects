
void testPalindrome(){

	char* s = "ssss1s";
	char* a = "ss1ss1ss";
	ASSERT(Palindrome(s) == 0);

	ASSERT(Palindrome(a) == 1);

}

void testSevenBoom(){
	SevenBoom(1,41);
}


void testDeBug(){
	while(1){
	
	}
}

/*****************************END OF TESTS*******************************************/

void swap(int* a, int* b)
{

int temp = *a;
*a = *b;
*b = temp;

}

void copyArray(int a [], int b [], int len)
{
  int i = 0;

   for(;i < len; i++)
   {
      b[i] = a[i];
   }
}

size_t StrLen(const char *str)
{ 
   int result = 0;  
   assert(str);   
   while(str[result]){
   	result++;
   	
   }
   return result;
}

int StrCmp(const char* str1, const char* str2)
{ 
   assert(str1);
   assert(str2);
  
   while(*str1){ 
      if(*str1 != *str2)
      {
         break;
      }
      str1++;
      str2++;
   }
   return *str1 - *str2;
}


void swapTwoSizeT(size_t* a, size_t* b)
{

   size_t temp = *a;
   *a = *b;
   *b = temp;
}

void swapTwoSizeTPointers(size_t** a, size_t** b)
{
   size_t* temp = *a;
   *a = *b;
   *b = temp;
}

void useSwap(size_t** a, size_t** b)
{
	swapTwoSizeT(*a, *b);
}

/*ex2*/

char* StrCpy(char* destination, const char* source)
{
	char *result = destination;
	assert(destination != NULL && source != NULL);
	
	while(1)
	{
		*destination = *source;
		
		if( *source == '\0'){
			break;
		}
		
		source++;
		destination++;
	}
	
	return result;
}

char *StrnCpy(char *destination, const char *source, size_t n)
{
	size_t i = 0;
	char *result = destination;
	assert(destination != NULL && source != NULL);
  
	
	assert(destination != NULL && source != NULL);
	
	for(;i < n ; ++i)
	{
		
		destination[i] = source[i];
		if(source[i] == '\0')
		{
			return result;
		}
		
	}
	destination[i] = '\0';
	return result;
	
}



