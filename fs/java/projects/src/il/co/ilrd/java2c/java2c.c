/* shiraz code reviewed */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int char_buffer = 40;
char ret[40];

typedef struct Object Object_t;
typedef struct Class Class_t;
typedef void *(*vf_t)(void *);

typedef struct Animal Animal_t;
typedef struct Dog Dog_t;
typedef struct Cat Cat_t;
typedef struct LegendaryAnimal LegendaryAnimal_t;

char *ObjectToString(void *this);
void *ObjectFinalize(void *this);

void AnimalPrintOnce();
char *AnimalToString(void *this);
void *AnimalFinalize(void *this);
int AnimalGetNumMasters(Animal_t *this);
static void *AnimalShowCounter(Animal_t *this);
void *AnimalSayHello(Animal_t *this);

void DogPrintOnce();
char *DogToString(void *this);
void *DogFinalize(void *this);
void *DogSayHello(Dog_t *this);

void CatPrintOnce();
void CatCtorStr(Cat_t *this, char *color);
char *CatToString(void *this);
void *CatFinalize(void *this);

void LegendaryAnimalPrintOnce();
void *LegendaryAnimalSayHello(void *this);
void *LegendaryAnimalFinalize(void *this);
char *LegendaryAnimalToString(void *this);

enum
{
	TOSTRING,
	FINALIZE,
	SAYHELLO,
	GETNUMNASTERS
};

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
	snprintf(ret, char_buffer, "%s@%p", ((Object_t *)this)->meta->name, this);
	return ret;
}

void *ObjectFinalize(void *this)
{
	free(this);
	return NULL;
}

/* ********************************************************* */

vf_t Animal_vt[] = {(vf_t)AnimalToString, (vf_t)AnimalFinalize, (vf_t)AnimalSayHello, (vf_t)AnimalGetNumMasters};

static int animal_counter = 0;

struct Animal
{
	Object_t o;
	int num_legs;
	int num_masters;
	int ID;
};

Class_t AnimalClass = {"Animal", sizeof(Animal_t), &ObjectClass, &Animal_vt};

void AnimalCtor(Animal_t *this)
{
	Class_t *curr_class = this->o.meta;
	AnimalPrintOnce();
	printf("Instance initialization block Animal\n");
	printf("Animal Ctor\n");
	this->ID = ++animal_counter;
	this->num_legs = 5;
	this->num_masters = 1;
	(*this->o.meta->VTable)[SAYHELLO](this);						 /* animal sayHello */
	AnimalShowCounter(this);										 /* animal showCounter */
	printf("%s\n", (char *)(*this->o.meta->VTable)[TOSTRING](this)); /* animal toString */
	while (0 != strcmp(curr_class->name, "Animal"))
	{
		curr_class = curr_class->parent;
	}

	/* printf("%s\n", (char *)(*this->o.meta->parent->VTable)[TOSTRING](this)); */
	printf("%s\n", (char *)(*curr_class->parent->VTable)[TOSTRING](this));
}

void AnimalCtorInt(Animal_t *this, int num_masters)
{
	AnimalPrintOnce();
	printf("Instance initialization block Animal\n");
	printf("Animal Ctor int\n");
	this->ID = ++animal_counter;

	this->num_legs = 5;
	this->num_masters = num_masters;
}

void *AnimalSayHello(Animal_t *this)
{
	puts("Animal Hello!");
	printf("I have %d legs\n", this->num_legs);
	return NULL;
}

static void *AnimalShowCounter(Animal_t *this)
{
	printf("%d\n", animal_counter);
	return NULL;
}

int AnimalGetNumMasters(Animal_t *this)
{
	return this->num_masters;
}

char *AnimalToString(void *this)
{
	snprintf(ret, char_buffer, "animal with id %d", ((Animal_t *)this)->ID);
	return ret;
}

void *AnimalFinalize(void *this)
{
	printf("finalize Animal with ID: %d\n", ((Animal_t *)this)->ID);
	(*((Animal_t *)this)->o.meta->parent->VTable)[FINALIZE](this); /* object finalizer */
	free(this);
	return NULL;
}

void AnimalPrintOnce()
{
	static int wasPrinted = 0;
	if (!wasPrinted)
	{
		puts("Static block Animal 1");
		puts("Static block Animal 2");
		wasPrinted = 1;
	}
}

/* ********************************************************* */

vf_t Dog_vt[] = {(vf_t)DogToString, (vf_t)DogFinalize, (vf_t)DogSayHello, (vf_t)AnimalGetNumMasters};

struct Dog
{
	Animal_t animal;
	int num_legs;
};

Class_t DogClass = {"Dog", sizeof(Dog_t), &AnimalClass, &Dog_vt};

void DogCtor(Dog_t *this)
{
	DogPrintOnce();
	AnimalCtorInt(&this->animal, 2);
	printf("Instance initialization block Dog\n");
	puts("Dog Ctor");
	this->num_legs = 4;
}

void *DogSayHello(Dog_t *this)
{
	puts("Dog Hello!");
	printf("I have %d legs\n", this->animal.num_legs);
	return NULL;
}

char *DogToString(void *this)
{
	snprintf(ret, char_buffer, "Dog with id %d", ((Dog_t *)this)->animal.ID);
	return ret;
}

void *DogFinalize(void *this)
{
	printf("finalize Dog with ID: %d\n", ((Dog_t *)this)->animal.ID);
	AnimalFinalize(this);
	free(this);
	return NULL;
}

void DogPrintOnce()
{
	static int wasPrinted = 0;
	if (!wasPrinted)
	{
		puts("Static block Dog");
		wasPrinted = 1;
	}
}

/* ********************************************************* */

vf_t Cat_vt[] = {(vf_t)CatToString, (vf_t)CatFinalize, (vf_t)AnimalSayHello, (vf_t)AnimalGetNumMasters};

struct Cat
{
	Animal_t animal;
	char *color;
	int num_masters;
};

Class_t CatClass = {"Cat", sizeof(Cat_t), &AnimalClass, &Cat_vt};

void CatCtor(Cat_t *this)
{
	CatPrintOnce();
	CatCtorStr(this, "black");
	printf("Cat Ctor\n");
	this->num_masters = 2;
}

void CatCtorStr(Cat_t *this, char *color)
{
	CatPrintOnce();
	AnimalCtor(&this->animal);
	this->color = color;
	this->num_masters = 5;
	printf("Cat Ctor with color: %s\n", this->color);
}

char *CatToString(void *this)
{
	snprintf(ret, char_buffer, "Cat with id %d", ((Cat_t *)this)->animal.ID);
	return ret;
}

void *CatFinalize(void *this)
{
	printf("finalize Cat with ID: %d\n", ((Cat_t *)this)->animal.ID);
	(*((Cat_t *)this)->animal.o.meta->parent->VTable)[FINALIZE](this); /* animal finalizer */
	free(this);
	return NULL;
}

void CatPrintOnce()
{
	static int wasPrinted = 0;
	if (!wasPrinted)
	{
		puts("Static block Cat");
		wasPrinted = 1;
	}
}

/* ********************************************************* */

vf_t LegendaryAnimal_vt[] = {(vf_t)LegendaryAnimalToString, (vf_t)LegendaryAnimalFinalize, (vf_t)LegendaryAnimalSayHello, (vf_t)AnimalGetNumMasters};

struct LegendaryAnimal
{
	Cat_t cat;
};

Class_t LegendaryAnimalClass = {"LegendaryAnimal", sizeof(LegendaryAnimal_t), &CatClass, &LegendaryAnimal_vt};

void LegendaryAnimalCtor(LegendaryAnimal_t *this)
{
	LegendaryAnimalPrintOnce();
	CatCtor(&this->cat);
	printf("Legendary Ctor\n");
}

char *LegendaryAnimalToString(void *this)
{
	snprintf(ret, char_buffer, "LegendaryAnimal with id %d", ((LegendaryAnimal_t *)this)->cat.animal.ID);
	return ret;
}

void *LegendaryAnimalFinalize(void *this)
{
	printf("finalize LegendaryAnimal with ID: %d\n", ((LegendaryAnimal_t *)this)->cat.animal.ID);
	(*((LegendaryAnimal_t *)this)->cat.animal.o.meta->parent->VTable)[FINALIZE](this); /* animal finalizer */
	free(this);
	return NULL;
}

void *LegendaryAnimalSayHello(void *this)
{
	puts("Legendary Hello!");
	return NULL;
}

void LegendaryAnimalPrintOnce()
{
	static int wasPrinted = 0;
	if (!wasPrinted)
	{
		puts("Static block Legendary Animal");
		wasPrinted = 1;
	}
}

/* ********************************************************* */

void foo(Animal_t *animal)
{
	printf("%s\n", (char *)(*animal->o.meta->VTable)[0](animal));
}

int main()
{
	Animal_t *animal = (Animal_t *)Alloc(&AnimalClass);
	Dog_t *dog = (Dog_t *)Alloc(&DogClass);
	Cat_t *cat = (Cat_t *)Alloc(&CatClass);
	LegendaryAnimal_t *la = (LegendaryAnimal_t *)Alloc(&LegendaryAnimalClass);
	Animal_t *array[5];
	size_t i = 0;

	AnimalCtor(animal);

	DogCtor(dog);

	CatCtor(cat);

	LegendaryAnimalCtor(la);

	(*animal->o.meta->VTable)[SAYHELLO](animal);

	printf("%d\n", animal->ID);
	printf("%d\n", dog->animal.ID);
	printf("%d\n", cat->animal.ID);
	printf("%d\n", la->cat.animal.ID);

	array[0] = (Animal_t *)Alloc(&DogClass);
	DogCtor((Dog_t *)array[0]);

	array[1] = (Animal_t *)Alloc(&CatClass);
	CatCtor((Cat_t *)array[1]);

	array[2] = (Animal_t *)Alloc(&CatClass);
	CatCtorStr((Cat_t *)array[2], "white");

	array[3] = (Animal_t *)Alloc(&LegendaryAnimalClass);
	LegendaryAnimalCtor((LegendaryAnimal_t *)array[3]);

	array[4] = (Animal_t *)Alloc(&AnimalClass);
	AnimalCtor(array[4]);

	for (i = 0; i < 5; ++i)
	{
		(*array[i]->o.meta->VTable)[SAYHELLO](array[i]);
		printf("%d\n", (int)(*array[i]->o.meta->VTable)[GETNUMNASTERS]((Animal_t *)array[i]));
	}

	for (i = 0; i < 5; ++i)
	{
		foo(array[i]);
	}

	/* 	for (i = 0; i < 5; ++i)
		{
			(*array[i]->o.meta->VTable)[FINALIZE](array[i]);
		} */
	/* (*array[i]->o.meta->VTable)[FINALIZE](animal); */

	return 0;
}