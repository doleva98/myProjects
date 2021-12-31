#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "dynamic_vector.h"

struct Vector
{
	size_t size;
	size_t type_size;
	size_t capacity;
	size_t reserve;
	void *a;
};

/* Create new vector */
Vector_t *VectorCreate(size_t initial_capacity, size_t type_size)
{

	Vector_t *vector = NULL;

	assert(initial_capacity > 0 && type_size > 0);

	vector = (Vector_t *)calloc(1, sizeof(Vector_t));
	if (!vector)
	{
		return NULL;
	}

	vector->size = 0;
	vector->type_size = type_size;
	vector->capacity = initial_capacity;
	vector->reserve = 0;

	vector->a = (void *)calloc(initial_capacity, type_size);
	if (!vector->a)
	{
		free(vector);
		vector = NULL;
		return NULL;
	}
	return vector;
}

/* Delete the vector */
void VectorDestroy(Vector_t *vector)
{
	assert(vector);
	free(vector->a);
	vector->a = NULL;
	free(vector);
	vector = NULL;
}

/* Add a new element to the end of the vector */
void VectorPushBack(Vector_t *vector, const void *element)
{
	assert(vector && element);
	if (VectorSize(vector) == VectorCapacity(vector))
	{
		VectorReserve(vector, 2 * vector->capacity);
	}
	memcpy((char *)vector->a + vector->size * vector->type_size, element, vector->type_size);
	++vector->size;
}

/* Remove element from the vector*/
void VectorPopBack(Vector_t *vector)
{
	assert(vector && vector->size);
	--vector->size;

	if (vector->size < vector->capacity / 3)
	{
		VectorReserve(vector, vector->capacity / 2);
	}
}

/* Get access to an element */
void *VectorGetAccessToElement(Vector_t *vector, size_t idx)
{
	assert(vector && idx < vector->size);
	return (char *)vector->a + (idx) * (vector->type_size);
}

/* Reallocates memory to store num elements*/
void VectorReserve(Vector_t *vector, size_t num)
{
	void *temp = NULL;
	assert(vector);
	if (num < VectorCapacity(vector) && num < 2 * vector->reserve)
	{
		return;
	}

	if (vector->reserve < num)
	{
		vector->reserve = num;
	}

	temp = (void *)calloc(num, vector->type_size);
	memcpy(temp, vector->a, vector->size*vector->type_size);
	free(vector->a);
	vector->a = temp;
	vector->capacity = num;
}

/* Return number of elements */
size_t VectorSize(Vector_t *vector)
{
	assert(vector);
	return vector->size;
}

/* Return capacity */
size_t VectorCapacity(Vector_t *vector)
{
	assert(vector);
	return vector->capacity;
}
