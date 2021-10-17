#ifndef MYSTRING_H
#define MYSTRING_H

int StrCmp(const char* str1, const char* str2);
void testStrCmp();

size_t StrLen(const char *str);
void testStrLen();

char* StrCpy(char* destination, const char* source);
void testStrCpy();

char *StrnCpy(char *destination, const char *source, size_t n);
void testStrnCpy();

int StrCaseCmp(const char *str1, const char *str2);
void testStrCaseCmp();

char *StrChr(const char *str, int c);
void testStrChr();

char *StrDup(const char *str);
void testStrDup();


char *StrCat(char *destination, const char *source);
void testStrCat();

char* StrnCat (char* destination, const char* source, size_t num );
void testStrnCat();

char *StrStr(const char *haystack, const char *needle);
void testStrStr();

size_t StrSpn(const char *str1, const char *str2);
void testStrSpn();


int Palindrome (char* str);
void testPalindrome();

void SevenBoom(int start, int finish);
void testSevenBoom();

void swap(int* a, int* b);
void copyArray(int a [], int b [], int len);
void swapTwoSizeT(size_t* a, size_t* b);
void swapTwoSizeTPointers(size_t** a, size_t** b);
void useSwap(size_t** a, size_t** b);
void testDeBug();

#endif
