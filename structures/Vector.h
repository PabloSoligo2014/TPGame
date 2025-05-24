#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct{
    void* dato;
    unsigned tam;
}tNodo;

typedef struct{
    tNodo* vec;
    unsigned ce;
    unsigned tam;
}Vector;

typedef int (*Cmp)(const void* , const void*);

int Vector_create(Vector*v, unsigned tamVector);
void Vector_destroy(Vector*v);
int _resize(Vector* v,size_t nuevoTamanio);
int Vector_insertInOrder(Vector* v,void*elemento,size_t tamDato,Cmp cmp);
int Vector_insertInOrderNoRepeat(Vector* v, void* elemento, size_t tamDato, Cmp cmp);
int Vector_getByPos(Vector* v, int pos, void * valor, size_t tamValor);
void* Vector_bsearch(Vector *v, void * valor, Cmp cmp);
int compararInt(const void* a, const void* b);
#endif // VECTOR_H_INCLUDED
