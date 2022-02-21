#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Object Object_t;
typedef struct Class Class_t;
typedef void *(*vf_t)(void *);

typedef struct Animal Animal_t;
typedef struct Dog Dog_t;
typedef struct Cat Cat_t;

char *ObjectToString(void *this);
void *ObjectFinalize(void *this);

char *AnimalToString(void *this);
void *AnimalFinalize(void *this);
int AnimalGetNumMasters(Animal_t *this);
void *AnimalShowCounter(Animal_t *this);
void *AnimalSayHello(Animal_t *this);

char *DogToString(void *this);
void *DogFinalize(void *this);
void *DogSayHello(Dog_t *this);

void CatCtorStr(Cat_t *this, char *color);
char *CatToString(void *this);
void *CatFinalize(void *this);

struct Class
{
	char *name;
	size_t size;
	Class_t *parent;
	vf_t (*VTable)[];
};

struct Object
{
	Class_t *meta;
};

vf_t Object_vt[] = {(vf_t)ObjectToString, ObjectFinalize};

Class_t ObjectClass = {"Object", sizeof(Object_t), NULL, &Object_vt};

Object_t *Alloc(Class_t *meta)
{
	Object_t *ret = calloc(meta->size, 1);
	ret->meta = meta;
	return ret;
}

char *ObjectToString(void *this)
{
	int char_buffer = 40;
	char *ret = (char *)malloc(char_buffer);
	snprintf(ret, char_buffer, "%s@%p", ((Object_t *)this)->meta->name, this);
	return ret;
}

void *ObjectFinalize(void *this)
{
	(void)this;
	return NULL;
}

/* ********************************************************* */

vf_t Animal_vt[] = {(vf_t)AnimalToString, (vf_t)AnimalFinalize, (vf_t)AnimalSayHello, (vf_t)AnimalShowCounter, (vf_t)AnimalGetNumMasters};

static int animal_counter = 0;

struct Animal
{
	Object_t o;
	int num_legs;
	int counter;
	int num_masters;
	int ID;
};

Class_t AnimalClass = {"Animal", sizeof(Animal_t), &ObjectClass, &Animal_vt};

void AnimalCtor(Animal_t *this)
{
	printf("Instance initialization block Animal\n");
	printf("Animal Ctor\n");
	this->ID = ++animal_counter;
	this->counter = animal_counter;
	this->num_legs = 5;
	this->num_masters = 1;
	(*this->o.meta->VTable)[2](this);								  /* animal sayHello */
	(*this->o.meta->VTable)[3](this);								  /* animal showCounter */
	printf("%s\n", (char *)(*this->o.meta->VTable)[0](this));		  /* animal toString */
	printf("%s\n", (char *)(*this->o.meta->parent->VTable)[0](this)); /* animal toString */
}

void AnimalCtorInt(Animal_t *this, int num_masters)
{
	printf("Instance initialization block Animal\n");
	printf("Animal Ctor int\n");
	this->ID = ++animal_counter;
	this->counter = animal_counter;

	this->num_legs = 5;
	this->num_masters = num_masters;
}

void *AnimalSayHello(Animal_t *this)
{
	puts("Animal Hello!");
	printf("I have %d legs\n", this->num_legs);
	return NULL;
}

void *AnimalShowCounter(Animal_t *this)
{
	printf("%d\n", this->counter);
	return NULL;
}

int AnimalGetNumMasters(Animal_t *this)
{
	return this->num_masters;
}

char *AnimalToString(void *this)
{
	int char_buffer = 40;
	char *ret = (char *)malloc(char_buffer);
	snprintf(ret, char_buffer, "animal with id %d", ((Animal_t *)this)->ID);
	return ret;
}

void *AnimalFinalize(void *this)
{
	printf("finalize Animal with ID: %d\n", ((Animal_t *)this)->ID);
	(*((Animal_t *)this)->o.meta->parent->VTable)[1](this); /* object finalizer */
	return NULL;
}

/* ********************************************************* */

vf_t Dog_vt[] = {(vf_t)DogToString, (vf_t)DogFinalize, (vf_t)DogSayHello, (vf_t)AnimalShowCounter, (vf_t)AnimalGetNumMasters};

struct Dog
{
	Animal_t animal;
};

Class_t DogClass = {"Dog", sizeof(Dog_t), &AnimalClass, &Dog_vt};

void DogCtor(Dog_t *this)
{
	AnimalCtorInt(&this->animal, 2);
	printf("Instance initialization block Dog\n");
	this->animal.num_legs = 4;
}

void *DogSayHello(Dog_t *this)
{
	puts("Dog Hello!");
	printf("I have %d legs\n", this->animal.num_legs);
	return NULL;
}

char *DogToString(void *this)
{
	int char_buffer = 40;
	char *ret = (char *)malloc(char_buffer);
	snprintf(ret, char_buffer, "Dog with id %d", ((Dog_t *)this)->animal.ID);
	return ret;
}

void *DogFinalize(void *this)
{
	printf("finalize Dog with ID: %d\n", ((Dog_t *)this)->animal.ID);
	(*((Dog_t *)this)->animal.o.meta->parent->VTable)[1](this); /* animal finalizer */
	return NULL;
}

/* ********************************************************* */

vf_t Cat_vt[] = {(vf_t)CatToString, (vf_t)CatFinalize, (vf_t)AnimalSayHello, (vf_t)AnimalShowCounter, (vf_t)AnimalGetNumMasters};

struct Cat
{
	Animal_t animal;
	char *color;
};

Class_t CatClass = {"Cat", sizeof(Cat_t), &AnimalClass, &Cat_vt};

void CatCtor(Cat_t *this)
{
	CatCtorStr(this, "black");
	printf("Cat Ctor\n");
	this->animal.num_masters = 2;
}

void CatCtorStr(Cat_t *this, char *color)
{
	this->color = color;
	this->animal.num_masters = 2;
	printf("Cat Ctor with color: %s\n", this->color);
}

char *CatToString(void *this)
{
	int char_buffer = 40;
	char *ret = (char *)malloc(char_buffer);
	snprintf(ret, char_buffer, "Cat with id %d", ((Cat_t *)this)->animal.ID);
	return ret;
}

void *CatFinalize(void *this)
{
	printf("finalize Cat with ID: %d\n", ((Cat_t *)this)->animal.ID);
	(*((Cat_t *)this)->animal.o.meta->parent->VTable)[1](this); /* animal finalizer */
	return NULL;
}

/* ********************************************************* */



/* ********************************************************* */

int main()
{
	Object_t *animal_o = Alloc(&AnimalClass);
	Object_t *Dog_o = Alloc(&DogClass);
	Object_t *Cat_o = Alloc(&CatClass);

	puts("Static block Animal 1");
	puts("Static block Animal 2");

	AnimalCtor((Animal_t *)animal_o);

	puts("Static block Dog");

	DogCtor((Dog_t *)Dog_o);

	puts("Static block Cat");

	CatCtor((Cat_t *)Cat_o);

	/* (*((Dog_t *)Dog_o)->animal.o.meta->VTable)[2](Dog_o); */
	return 0;
}