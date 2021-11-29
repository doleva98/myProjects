#include <stdio.h>
#include "uid.h"
#include <time.h>
#include <sys/types.h>
#include <unistd.h>


/* aka BADUID */
const unique_id_t uid_null_uid={0,0,0}; 

/* generate a unique identifier */ 
unique_id_t UIDGenerate(void)
{	
	static size_t counter = 0;
	unique_id_t uid;
	
	++counter;
	uid.counter = counter;
	uid.timestamp = time(NULL);
	uid.pid = getpid();
	return uid;
}

/* check two UIDs for equality */
int UIDIsEqual(unique_id_t uid1, unique_id_t uid2)
{
	return uid1.pid == uid2.pid && uid1.counter == uid2.counter && uid1.timestamp == uid2.timestamp;

}

size_t getCounter(unique_id_t uid)
{
	return uid.counter;
}

size_t getTime(unique_id_t uid)
{
	return (size_t)uid.timestamp;
}

size_t getPid(unique_id_t uid)
{
	return (size_t)uid.pid;
}
/*
void setPlusTime(size_t more){
	uid.timestamp += (time_t)more;
}*/

