#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include "test_utils.h"
#include "structures/Vector.h"
#include "minunit.h"

int sumar(int a, int b){
    return a+b;
}

MU_TEST(test_muestra){
    int expResult = 10;
    char* errorMsg = "Error en la funcion de suma";
    mu_assert( expResult==sumar(5,5), errorMsg);
}

MU_TEST(test_vector_create){
    //char* errorMsg = "Error en la funcion de suma";
    Vector vector;
    int r;
    r = Vector_create(&vector, 10);
    mu_assert( r==1, "fail creating vector, there is enough memory");


    //TODO: manual Memcheck
    Vector_destroy(&vector);
}


MU_TEST(test_vector_insert_int){
    //char* errorMsg = "Error en la funcion de suma";
    Vector vector;
    int valor;
    int i;
    int r;
    int vtest[]             = {3,6,9,15,8,1,16};
    int* pvtest = vtest;

    r = Vector_create(&vector, 10);
    mu_assert( r==1, "fail creating vector, there is enough memory");

    //Tiene que funcionar con cualquier tipo de dato
    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        //Lo pongo en español: El prototipo de la funcion deberia ser asi
        //el usuario de Vector no tiene ni idea de que es un nodo, no le importa
        //solo quiere guardar y recuperar cosas. En este test, son simples enteros
        //Asi que de entrada hay que arreglar esto,

        //TODO: arreglar prototipo y descomentar!
        Vector_insertInOrder(&vector, pvtest, sizeof(*pvtest), cmp_int);

        pvtest++;
        //Aca hay mas controles que hacer en test previos...
    }

    //Ya esta todo insertardo, ahora ordeno mediante una funcion que se que anda bien
    //mi vector de test
    qsort(vtest, sizeof(vtest)/sizeof(*vtest), sizeof(*vtest), cmp_int);
    pvtest = vtest;//Lo vuelvo a apuntar al vector de test


    //Mi vector de test esta ordenado (qsort) funciona. ¿El TDA Vector inserto ordenadamente?
    for(i=0;i<sizeof(vtest)/sizeof(*vtest);i++){
        //Argumentos
        //1.Vector
        //2.Posicion de lo que quiero
        //3.Buffer/posicion de memoria donde dejarme lo que esta en el vector
        //4.Tamanio, eso les va parecer no necesario porque esta en el nodo, si, tiene un poco
        //de razon pero hay casos donde el elemento tiene tamaño variable, ya lo veremos.

        Vector_getByPos(&vector, i, &valor, sizeof(valor));

        //Lo que obtuve del Vector tiene que coincidir perfectamente con el vector de test ordenado

        mu_assert( *pvtest==valor, "Post a description of the bug here");
        pvtest++;
    }



    //TODO: manual Memcheck
    Vector_destroy(&vector);
}




MU_TEST_SUITE(test_suite) {

    MU_RUN_TEST(test_muestra);
    MU_RUN_TEST(test_vector_create);
    MU_RUN_TEST(test_vector_insert_int);
    //Mas test aca


}

int main(int argc, char *argv[])
{


    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}


