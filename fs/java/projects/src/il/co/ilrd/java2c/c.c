#include <stdio.h>
#include <stdlib.h>

typedef struct A A_t;
typedef struct Object Object_t;
typedef struct Class Class_t;
typedef void (*vf_t)(void *);

vf_t Object_vt[] = {(vf_t)ObjectEquals,
                    (vf_t)ObjectToString, (vf_t)ObjectClone, (vf_t)ObjectHashcode, (vf_t)ObjectgetClass};

Class_t ObjectClass = {"Object", sizeof(Object_t), NULL, &Object_vt};

vf_t A_vt[] = {(vf_t)ObjectEquals,
               (vf_t)ObjectToString, (vf_t)ObjectClone, (vf_t)ObjectHashcode, (vf_t)ObjectgetClass};

Class_t AClass = {"A", sizeof(A_t), &ObjectClass, &A_vt};

struct Class
{
    char *Name;
    size_t size;
    Class_t *parent;
    vf_t (*VTable)[];
}

struct Object
{
    Class_t *meta;
}

struct A
{
    Object_t o;
    int i;
}

void
ACtor(A_t *this, int i)
{
    this->i = i;
}

Object_t *Alloc(Class_t *meta)
{
    Object_t *ret = calloc(meta->size);
    ret->meta = meta;
    return ret;
}