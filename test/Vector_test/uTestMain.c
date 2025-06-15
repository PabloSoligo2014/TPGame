#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../test_utils.h"
#include "../../structures/Vector.h"
#include "../minunit.h"

#define TEMPORAL_COMPILE //Quitar luego de arreglar los prototipos

typedef struct
{
    char nom[20];
    int edad;
}t_test;

int sumar(int a, int b){
    return a+b;
}

void sumarEntero(void* a){
   int x = *(int*)a;  //x = a
   x++; // x += 1
   *(int*)a = x;  //a = x
}

void mostrarEntero(const void* a){
   int x = *(int*)a;
   printf("%d ", x);
}

int comp_edad(const void *a,const void *b)
{
    t_test t1 = *(t_test*)a;
    t_test t2 = *(t_test*)b;

    return t1.edad - t2.edad;
}

MU_TEST(test_muestra){
    int expResult = 10;
    char* errorMsg = "Error en la funcion de suma";
    mu_assert( expResult==sumar(5,5), errorMsg);
}

MU_TEST(test_vector_create){

    Vector vector;
    int r;
    r = Vector_create(&vector, 10);
    mu_assert( r==1, "fail creating vector, there is enough memory");

    Vector_destroy(&vector);
}

MU_TEST(test_vector_insert_int){

    Vector vector;
    int valor = 0;
    int i;
    int r;
    int vtest[]             = {3,6,9,15,8,1,16};
    int* pvtest = vtest;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "fail creating vector, there is enough memory");


    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_insertInOrder(&vector, pvtest, sizeof(*pvtest), cmp_int);

        pvtest++;
    }


    qsort(vtest, sizeof(vtest)/sizeof(*vtest), sizeof(*vtest), cmp_int);
    pvtest = vtest;


    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        //Argumentos
        //1.Vector
        //2.Posicion de lo que quiero
        //3.Buffer/posicion de memoria donde dejarme lo que esta en el vector
        //4.Tamanio, eso les va parecer no necesario porque esta en el nodo, si, tiene un poco
        //de razon pero hay casos donde el elemento tiene tamaño variable, ya lo veremos.

        Vector_getByPos(&vector, i, &valor, sizeof(valor));

        //Lo que obtuve del Vector tiene que coincidir perfectamente con el vector de test ordenado

        mu_assert( *pvtest== valor, "write a description of the bug here");
        pvtest++;
    }

    //TODO: manual Memcheck
    Vector_destroy(&vector);
}

MU_TEST(test_vector_getbypos)
{
    Vector vector;
    int pos = 2;
    int pos_fuera=9; //pos fuera del vector
    int i;
    int valor1 = 10;
    int r;
    int vtest[]             = {3,6,9,15,8,2,16};// 2,3,6,8,9,15,16
    int* pvtest = vtest;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "Error de memoria");

    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_insertInOrder(&vector, pvtest, sizeof(*pvtest), cmp_int);
        pvtest++;
    }

    qsort(vtest, sizeof(vtest)/sizeof(*vtest),sizeof(*vtest), cmp_int);
    pvtest = vtest;

    mu_assert(Vector_getByPos(&vector,pos_fuera,&valor1,sizeof(valor1))== -1,"Error, No esta tomando en cuenta las posiciones no validas");

    mu_assert(valor1 == 10,"Error, se esta pisando la variable valor con basura");

    Vector_getByPos(&vector, pos, &valor1, sizeof(valor1));
    mu_assert( 6 == valor1, "Error no coinciden los valores");

    Vector_getByPos(&vector, 0, &valor1, sizeof(valor1));
    mu_assert( 2 == valor1, "Error no coinciden los valores");

    Vector_destroy(&vector);
}

MU_TEST(test_vector_InsertInOrderNoRepeat_struct)
{
    Vector vector;
    t_test valor = {"neumonia",27};
    t_test obtenido;
    int i;
    int r;
    t_test vtest[]                    = {{"esteban",12},
                                        {"juan",2},
                                        {"pikachu",27},
                                        {"charmander",5},
                                        {"rigoberto",8}}; //2,5,8,12,27
    t_test *pvtest = vtest;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "Error de memoria");

    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_insertInOrderNoRepeat(&vector, pvtest, sizeof(*pvtest), comp_edad);
        pvtest++;
    }

    qsort(vtest, sizeof(vtest)/sizeof(*vtest), sizeof(*vtest), comp_edad);
    pvtest = vtest;

    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_getByPos(&vector,i,&obtenido,sizeof(t_test));
        mu_assert((strcmp(obtenido.nom,pvtest->nom)==0) , "Error valores no coinciden");
        pvtest++;
    }

    pvtest = vtest;

    Vector_insertInOrderNoRepeat(&vector, &valor, sizeof(*pvtest), comp_edad);
    Vector_getByPos(&vector,4,&obtenido,sizeof(t_test));

    pvtest += 4;

    mu_assert((strcmp(obtenido.nom , pvtest->nom) != 0 ) , "Error valores coinciden");

    Vector_destroy(&vector);
}

MU_TEST(test_vector_vacio)
{
    Vector vector;
    int valor = 10;
    int r;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "Error de memoria");

    Vector_getByPos(&vector,0,&valor,sizeof(int));

    mu_assert(valor == 10,"Esta tomando valores no validos");

    Vector_destroy(&vector);
}

MU_TEST(test_vector_map){

    Vector vector;
    int valor = 0;
    int i;
    int r;
    int vtest[]             = {3,6,9,15,8,1,16}; //2,3,6,8,9,15,16
    int* pvtest = vtest;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "Error de memoria");

    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_insertInOrder(&vector, pvtest, sizeof(*pvtest), cmp_int);
        pvtest++;
    }

    qsort(vtest, sizeof(vtest)/sizeof(*vtest), sizeof(*vtest), cmp_int);
    pvtest = vtest;

    Vector_map(&vector,(Accion)sumarEntero);

    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        Vector_getByPos(&vector, i, &valor, sizeof(valor));
        mu_assert( (*pvtest + 1) == valor, "Error no coinciden los valores");
        pvtest++;
    }

    Vector_destroy(&vector);
}


MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_muestra);
    MU_RUN_TEST(test_vector_create);
    MU_RUN_TEST(test_vector_insert_int);
    MU_RUN_TEST(test_vector_getbypos);
    MU_RUN_TEST(test_vector_InsertInOrderNoRepeat_struct);
    MU_RUN_TEST(test_vector_map);
    MU_RUN_TEST(test_vector_vacio);
}

int main(int argc, char *argv[])
{

    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}

