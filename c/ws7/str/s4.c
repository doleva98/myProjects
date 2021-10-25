int StrCaseCmp(const char *str1, const char *str2)
{
	assert(str1 != NULL && str2 != NULL);
  
   	while(*str1){  /*why dont you check (*str1 && *str2)?*/
      		if(tolower(*str1) != tolower(*str2))
      	{
         	break;
      	}
      		str1++;
      		str2++;
   	}
   	return tolower(*str1) - tolower(*str2);

}

char *StrChr(const char* str, int c)
{
	char* current= (char *)str;
	
	assert(str != NULL);

	while(*current != '\0')
	{
		if(*current == c)
		{
			return current;
		}
		current++;
	}
	return NULL;

}

char *StrDup(const char *str){
	
	char* result = (char*)malloc(StrLen(str) + 1);
	assert(str != NULL);
	if(result == NULL){
		return NULL;
	}
	StrCpy(result, str);
	return result;
	
}

char *StrCat(char *destination, const char *source){
	
	int i = 0;
	int dest_len = StrLen(destination);
	assert(destination != NULL && source != NULL);
	for(; source[i] != '\0'; ++i){
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';
	
	return destination;
	
}

char* StrnCat (char* destination, const char* source, size_t num ){

	size_t i = 0;
	int dest_len = StrLen(destination);
	assert(destination != NULL && source != NULL);
	for(; '\0' != source[i] && i < num; ++i){
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';
	
	return destination;
	
}

char *StrStr(const char *haystack, const char *needle){
	size_t i = 0;
	size_t j = 0;
	assert(haystack != NULL && needle != NULL);
	for(; i < StrLen(haystack) - StrLen(needle); ++i){
	
		if(needle[0] == haystack[i]){
		
			for(; j < StrLen(needle); ++j){
				if(haystack[i+j] != needle[j]){
					break;
				}
			}
			return (char *)haystack + i;
			
		}
	
	}
	return NULL;
}

size_t StrSpn(const char *str1, const char *str2){

	char* start = (char*)str2;
	int count = 0;
	assert(str1 != NULL && str2 != NULL);
	
	while(*str1){
		str2 = start;
		while(*str2){
			
			if(*str1 == *str2){
				
				count++;
				break;	
			}
			str2++;
		}
			
		if(!*str2){
			return count;
		}
		str1++;
	}
	return count;
}

int Palindrome (char* str)
{
	size_t i = 0;
	assert(str);
	for(; i < StrLen(str)/2; i++){
		if(str[i] != str[StrLen(str) - i - 1]){
			return 0;
		}
	}
	
	return 1;
}


int isSeven(int current){
	int temp = current;
	if(current%7 == 0){
		return 1;
	}
	
	while(temp != 0){
		if(temp%10 == 7){
			return 1;
		}
		else{
			temp = temp/10;
		}
	}
	return 0;
	
}

void SevenBoom(int start, int finish){
	int i = start;
	
	if(start < finish){
		
		for(; i < finish; ++i){
			if(isSeven(i)){
				printf("BOOM\n");
			}
			else{
				printf("%d\n", i);
			}
		} 	
		
	}
	else{
		for(; i > finish; --i){
			if(isSeven(i)){
				printf("BOOM\n");
			}
			else{
				printf("%d\n", i);
			}
		}
	}
	
	
	
}
