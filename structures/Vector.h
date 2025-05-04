#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct{
    void* dato;
    unsigned tam;
}tNodo;

typedef struct{
    tNodo* vec;
    unsigned ce;
    unsigned tam;
}Vector;

int crearVector(Vector* vector, unsigned tamVector);
void destruirVector(Vector*vector);

int redimensionarTDA(Vector* vector,size_t nuevoTamanio);
typedef int (*Cmp)(const void* , const void*);
int insertarOrdenadoTDA(Vector* vector,void*nuevoNodo,Cmp cmp);

/*La funcion para comparar enteros que se utilizo para probar el vector:

int compararInt(const void*a,const void*b){//si a < b retorna 1
    tNodo* dato1 = ((tNodo*)a);
    tNodo* dato2 = ((tNodo*)b);

    int a1 = *(int*)(dato1->dato);
    int b1 = *(int*)(dato2->dato);

    if(a1<b1){
        return 1;
    }else{
        return 0;
    }
}
*/

#endif // VECTOR_H_INCLUDED
