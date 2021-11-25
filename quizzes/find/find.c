#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int FindChar(char *str, size_t size, int c)
{
	size_t i = 0;
	for(; i < size && str[i] != c; ++i);
	return i != size;
}

void ShiftLeft(char *arr, size_t size, size_t n)
{	
	char *temp = NULL;
	size_t i;
	
	n %= size;
	
	temp = (char*)malloc(n);
	if(!temp)
	{
		return;
	}
	
	strncpy(temp, arr, n);
	
	for(i = n; i < size; ++i)
	{
		arr[i-n] = arr[i];
	}
	
	for(i = 0; i < n; ++i)
	{
		arr[i + size - n] = temp[i];
	}
	free(temp);
}


int main()
{
	char str [200]= "Hello World how are you??";
	
	if(!(FindChar("hell", 4, 'e') == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(FindChar("hell", 4, 'o') == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	ShiftLeft(str, strlen(str), 4);
	
	if(!(strcmp(str, "o World how are you??Hell") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	return 0;
}
