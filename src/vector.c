#include "../include/vector.h"

Vector *new_vec()
{
	Vector *v = malloc(sizeof(Vector));

	if (v == NULL)
		error("memory allocation error in new_vec()");

	v->capacity = 16;
	v->length   = 0;
	v->data     = malloc(sizeof(void *) * v->capacity);

	if (v == NULL)
		error("memory allocation error in new_vec()");

	return v;
}

void vec_push(Vector *v, void *elem)
{
	if (v->length + 1 >= v->capacity)
	{
		v->capacity *= 2;
		v->data      = realloc(v->data, sizeof(void *) * v->capacity);

		if (v->data == NULL)
			error("memory allocation error in vec_push()");
	}
	v->data[v->length++] = elem;
}
