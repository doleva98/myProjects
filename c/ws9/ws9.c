#include "ws9.h"



int main() {
	testMemset();
	testMemcpy();
	testMemmove();   

   return 0;
}

static void testMemset()
{
	char str1[50] = "This is library function";
	char str2[50] = "This is library function";
	Memset(str1,'$',17);
	memset(str2,'$',17);
	
	ASSERT(memcmp(str1, str2,50) == 0);
}

static void testMemcpy()
{
	char str1[50] = "This is library function";
	char str2[30] = "Dumbeldore";
	char str3[50] = "This is library function";
	Memcpy(str1,str2, 6);
	memcpy(str3,str2, 6);
	ASSERT(memcmp(str1, str3,50) == 0);
}

static void testMemmove()
{
	char str1[50] = "Dumbeldore";
	char str2[50] = "Dumbeldore";
	Memmove(str2+1,str2, 8);
	memmove(str1+1,str1, 8);
	ASSERT(memcmp(str1, str2,50) == 0);
}

static void *Memset(void *str, int c, size_t n)
{
	size_t j = 0;
	unsigned char toAdd = c & 0xFF;
	void *p = str;
	char bunch [8];
	
	assert(str);
	
	while((size_t)str%sizeof(size_t) != 0)
	{
		
		*(char*)str = toAdd;
		--n;
		str = (char*)str+1;	
		
	}

	for(; j < sizeof(size_t); ++j)
	{
		bunch[j] = toAdd;
	}
	
	while(n > sizeof(size_t))
	{
		*(size_t*)str = *(size_t*)bunch;
		str = (size_t*)str+1;	
		n -= 8;
	}
	
	while(n != 0)
	{
		*(char*)str = toAdd;
		str = (char*)str+1;	
		--n;
	}
	return p;
	
}

static void *Memcpy(void *dest, const void * src, size_t n)
{
	void *p = dest;
		
	while(n > sizeof(size_t))
	{
		*(size_t*)dest = *(size_t*)src;
		dest = (size_t*)dest+1;	
		src = (size_t*)src+1;	
		n -= 8;
	}
	
	while(n != 0)
	{
		*(char*)dest = *(char*)src;
		dest = (char*)dest+1;	
		src = (char*)src+1;	
		--n;
	}
	
	return p;
}

static void *Memmove(void *dest, const void *src, size_t n)
{	
	size_t i =0;
	if(dest > src)
	{
		
		for(; i < n; ++i)
		{
			*((char*)dest+ n - i-1) = *((char*)src + n - i);
		}			
		
	}

	return memcpy(dest, src, n);

}












