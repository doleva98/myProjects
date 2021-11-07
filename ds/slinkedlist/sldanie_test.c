

#include "singly_list.h"
 #include <stdio.h> 
 
 int main() { 
 	slist_t* list = SListCreate(); 	
 	int x = 4; 	
 	printf("&x:%p\n", &x); 	
 	SListInsert(SListBegin(list), &x); 	
 	printf("%d\n", *(int*)SListIterGetData(SListBegin(list))); 	
 	return 0; 
 	}


