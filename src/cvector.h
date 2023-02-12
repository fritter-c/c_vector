#ifndef CVECTOR_H
#define CVECTOR_H

#include<stdlib.h>
#include<string.h>

#define VECTOR_API

#define vector_unpack(v) (char**)&(v)->items, &(v)->capacity, &(v)->length, sizeof(*(v)->items)

#define vector(T)struct{T* items; size_t capacity, length;}

#define vector_new(v) memset(v, 0, sizeof(*(v)))

#define vector_reserve(v, n) vector_dynamic_alloca(vactor_unpack(v),n)

#define vector_reset(v) (free((v)->items),vector_new(v))

#define vector_free(v) (free((v)->items), (v)->capacity = 0, (v)->length = 0)

#define vector_clear(v) (v)->length = 0

#define vector_push(v, val) ((((v)->length + 1) > (v)->capacity) ? (vector_expand(vector_unpack(v)) ? -1 :\
	((v)->items[(v)->length++] = (val), 0)) : ((v)->items[(v)->length++] = (val), 0))

#define vector_pop(v) (v)->items[--(v)->length]

#define vector_insert_s(v, val, index) ((((v)->length + 1) > (v)->capacity) ? (vector_expand(vector_unpack(v)) ? -1 :\
    ((index) < ((v)->length)) ? vector_push(v,val),\
    memmove((v)->items + (index) + 1, (v)->items + (index), ((v)->length - (index) - 1) * sizeof(*(v)->items)),\
    (v)->items[index] = (val), 0 : (vector_push(v, val), 0)) :\
    ((index) < ((v)->length)) ? vector_push(v,val),\
    memmove((v)->items + (index) + 1, (v)->items + (index), ((v)->length - (index) - 1) * sizeof(*(v)->items)),\
    (v)->items[index] = (val), 0 : (vector_push(v, val), 0))

#define vector_insert(v, val, index) ((((v)->length + 1) > (v)->capacity) ? (vector_expand(vector_unpack(v)) ? -1 :\
    vector_push(v,val),\
    memmove((v)->items + (index) + 1, (v)->items + (index), ((v)->length - (index) - 1) * sizeof(*(v)->items)),\
    (v)->items[index] = (val),0):\
     vector_push(v,val),\
    memmove((v)->items + (index) + 1, (v)->items + (index), ((v)->length - (index) - 1) * sizeof(*(v)->items)),\
    (v)->items[index] = (val))


#define vector_insertion_sort(v, T)\
for (size_t i = 1; i < (v)->length; ++i){\
	T key = (v)->items[i],\
    int j = i - 1,\
    while ((j > 0) && (v)->items[j] > key){\
	  (v)->items[j + 1] = (v)->items[j],\
       j--,\
	}\
	(v)->items[j + 1] = key}

#define vector_quick_sort(v, fn) (qsort((v)->items, (v)->length, sizeof(*(v)->items), (fn)))

#define vector_delete_s(v, index) (((index) < ((v)->length)) ?\
  memmove((v)->items + (index), (v)->items + (index) + 1, ((v)->length - (index)-1) * sizeof(*(v)->items)),\
  (v)->length-- : vector_pop(v))

#define vector_delete(v, index) \
  (memmove((v)->items + (index), (v)->items + (index) + 1, ((v)->length - (index)-1) * sizeof(*(v)->items)),\
  (v)->length--)


#define vector_find(v, val, index)\
    *(index) = (v)->length;\
    for(size_t i= 0; i < (v)->length; i++){\
		if ((v)->items[i] == val){\
			*(index) = i;\
            break;\
        }\
	}
static VECTOR_API int vector_dynamic_alloca(char** items, 
	 size_t *capacity, size_t *length, int mensz, size_t n) {
	
	(void)length;

	if (n < *capacity) {
		void* ptr = realloc(*items, n * mensz);
		if (ptr == 0) return -1;
		*items = ptr;
		*capacity = n;
	
	}
	return 0;
}

static VECTOR_API int vector_expand(char** items, size_t* capacity, size_t* length, size_t memsz) {
	if (*length + 1 > *capacity) {
		
		size_t n = (*capacity == 0) ? 1 : (*capacity *= 2);
		void* ptr = realloc(*items, n * memsz);
		if (ptr == 0) return -1;
		*capacity = n;
		*items = ptr;

	}
	return 0;
 }

typedef vector(char*) string_vector;

#endif // !CVECTOR_H
