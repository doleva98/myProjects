
	b = (char*)malloc(strlen(a)+1);
	if(NULL == b){
		return;
	}
	
	d = (char*)malloc(strlen(a)+1);
	if(NULL == d){
		return;
	}

	c = StrCpy(b, a);
	e = strcpy(d, a);
	ASSERT(StrCmp(c,e) == 0);
	ASSERT(StrCmp(b,d) == 0);
	FREE(b);
	FREE(d);
}

void testStrnCpy()
{
	char *a = "Hello World!";
	char *d = NULL;
	char *b = NULL;
	char *c = NULL;
	char *e = NULL;
	
	b = (char*)calloc(10,1);
	if(NULL == b){
		return;
	}
	
	c = StrnCpy(b, a, 9);
	
	d = (char*)calloc(10,1);
	if(NULL == d){
		return;
	}
	
	e = strncpy(d, a, 9);
	
	ASSERT(StrCmp(c,e) == 0);
	
	ASSERT(StrCmp(c,"Hello Wor") == 0);
	
	ASSERT(StrCmp(b,d) == 0);
		
	FREE(b);
	FREE(d);
}

void testStrCaseCmp(){

	char *a = "ZZZZZwow wwww!!! ";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	if(strcasecmp(a,b) < 0){
		ASSERT(StrCaseCmp(a,b) < 0);
	}else {
		
		if (strcasecmp(a,b) == 0){
		ASSERT(StrCaseCmp(a,b) == 0);	
		}else{
		ASSERT(StrCaseCmp(a,b) > 0);
		}
	}
	ASSERT(StrCaseCmp(a,"zzzzzwow wwww!!! ") == 0);
}

void testStrChr(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrChr(a, 'w');
	char* c = strchr(a, 'w');
	char* z = "wow wwww!!! ";
	ASSERT(b == c);
	ASSERT(StrCmp(b,z) == 0);
}

void testStrDup(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrDup(a);
	char* c = NULL;
	c = (char*)strdup(a);
	ASSERT(StrCmp(b,c) == 0);
	FREE(b);
	FREE(c);
}

void testStrCat(){
	char a [1000]= "ZZZZZwow wwww!!! fdsdf";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	char c [1000]= "ZZZZZwow wwww!!! fdsdf";
	StrCat(a,b);
	strcat(c,b);
	ASSERT(StrCmp(StrCat(a,b), strcat(c,b))  == 0 );
}

void testStrnCat(){

	char a [1000]= "ZZZZZwow wwww!!! fdsdf";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	char c [1000]= "ZZZZZwow wwww!!! fdsdf";
	StrnCat(a,b, 1);
	strncat(c,b, 1);
	ASSERT(StrCmp(StrnCat(a,b, 7), strncat(c,b, 7)) == 0 );

}

void testStrStr(){
	
	char* a = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";	
	char* b ="!!";
	ASSERT(StrCmp(StrStr(a,b), strstr(a,b)) == 0);
}

void testStrSpn(){

	char* a = "!ZwwT ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";	
	char* b ="w!!ZT";
	printf("%lu\n", StrSpn(a,b));
	printf("%lu\n", strspn(a,b));
	

}










