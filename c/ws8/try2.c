#include "/home/dolev/git/dolev-arev/include/utils.h"

union members
{
	int i;
	float f;
	double d;
};

struct X
{
	int i;
	char c;
	double d;
	short s;
};

struct card
{
	unsigned int suit : 2;
	unsigned int face_value : 31;
};

int main() {

    printf("%lu\n", sizeof(struct card));

   return 0;
}
