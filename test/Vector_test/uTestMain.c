#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../test_utils.h"
#include "../../structures/Vector.h"
#include "../minunit.h"

#define TEMPORAL_COMPILE //Quitar luego de arreglar los prototipos

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
    int valor = 0;
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

        //TODO: arreglar prototipo quitar macro

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

        mu_assert( *pvtest==valor, "write a description of the bug here");
        pvtest++;
    }



    //TODO: manual Memcheck
    Vector_destroy(&vector);
}

void imprimirInt(const void* dato) {
    printf("%d ", *(int*)dato);
}

void prueba_crear_y_destruir() {
    Vector v;
    if (Vector_create(&v, 5) && v.ce == 0 && v.tam == 5) {
        printf("Vector creado correctamente\n");
    } else {
        printf("No se pudo crear el vector\n");
    }

    Vector_destroy(&v);
    if (v.ce == 0 && v.tam == 0) {
        printf("Vector destruido\n");
    } else {
        printf("No se pudo destruir el vector\n");
    }
}

void prueba_leer_vector_vacio() {
    Vector v;
    Vector_create(&v, 3);
    int valor;
    if (Vector_getByPos(&v, 0, &valor, sizeof(int)) == -1) {
        printf("Lectura de vector vacio correcta\n");
    } else {
        printf("Lectura de vector vacio no funciono\n");
    }
    Vector_destroy(&v);
}

void prueba_insercion_y_ordenamiento() {
    Vector v;
    Vector_create(&v, 2);
    int nums[] = {5, 2, 8, 1};

    for (int i = 0; i < 4; i++) {
        Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);
    }

    int esperado[] = {1, 2, 5, 8};
    int correcto = 1;

    for (int i = 0; i < 4; i++) {
        int valor;
        if (Vector_getByPos(&v, i, &valor, sizeof(int)) != 1 || valor != esperado[i]) {
            correcto = 0;
        }
    }

    if (correcto) {
        printf("Los elementos fueron insertados y ordenados\n");
    } else {
        printf("El orden o insercion de elementos fallo\n");
    }

    Vector_destroy(&v);
}

void prueba_busqueda_binaria() {
    Vector v;
    Vector_create(&v, 5);
    int nums[] = {3, 6, 9};
    for (int i = 0; i < 3; i++)
        Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);

    int clave = 6;
    int* encontrado = (int*)Vector_bsearch(&v, &clave, compararInt);
    if (encontrado && *encontrado == clave) {
        printf("Busqueda binaria encontro el elemento\n");
    } else {
        printf("Busqueda binaria no encontro el elemento\n");
    }

    int noExiste = 10;
    if (Vector_bsearch(&v, &noExiste, compararInt) == NULL) {
        printf("Busqueda binaria no encontro nada\n");
    } else {
        printf("Busqueda binaria encontro un elemento que no deberia existir\n");
    }

    Vector_destroy(&v);
}

void prueba_insertar_no_repetidos() {
    Vector v;
    Vector_create(&v, 2);
    int a = 4;
    int b = 4;

    int res1 = Vector_insertInOrderNoRepeat(&v, &a, sizeof(int), compararInt);
    int res2 = Vector_insertInOrderNoRepeat(&v, &b, sizeof(int), compararInt);

    if (res1 == 1 && res2 == 2 && v.ce == 1) {
        printf("Insercion sin repetidos se realizo y reemplazo el dato duplicado\n");
    } else {
        printf("Insercion sin repetidos no funciono\n");
    }

    Vector_destroy(&v);
}

void prueba_map() {
    Vector v;
    Vector_create(&v, 3);
    int nums[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);

    printf("Contenido del vector (esperado 1 2 3): ");
    Vector_map(&v, imprimirInt);
    printf("\n");

    Vector_destroy(&v);
    printf("Se aplico correctamente la funcion map \n");
}

void prueba_insertar_mas_alla_del_tamanio() {
    Vector v;
    Vector_create(&v, 3);  // Capacidad máxima: 3 elementos
    int nums[] = {1, 2, 3, 4}; // 4 elementos a insertar

    int resultado;
    int band = 1;

    for (int i = 0; i < 4; i++) {
        resultado = Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);

        if (i < 3 && resultado != 1) {
            printf("Error:No se pudo insertar el elemento %d\n", nums[i]);
            band = 0;
        }

        if (i == 3 && resultado != 0) {
            printf("Error: Se inserto un cuarto elemento cuando ya no hay espacio\n");
            band = 0;
        }
    }

    if (band) {
        printf("Control de capacidad correcto\n");
    } else {
        printf("Error al controlar la capacidad del vector\n");
    }

    Vector_destroy(&v);
}

void imprimir_vector(Vector* v) {
    for (int i = 0; i < v->ce; i++) {
        int val;
        Vector_getByPos(v, i, &val, sizeof(int));
        printf("%d ", val);
    }
    printf("\n");
}

void prueba_insertar_elemento_al_principio() {
    Vector v;
    Vector_create(&v, 5);

    int nums[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);
    }

    int prueba = 5;
    Vector_insertInOrder(&v, &prueba, sizeof(int), compararInt);

    int valor;
    Vector_getByPos(&v, 0, &valor, sizeof(int));
    if (valor == 5) {
        printf("Insercion al principio correcta\n");
    } else {
        printf("Error en la insercion al principio\n");
    }
    printf("Vector resultado: ");
    imprimir_vector(&v);

    Vector_destroy(&v);
}

void prueba_insertar_elemento_al_final() {
    Vector v;
    Vector_create(&v, 5);

    int nums[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        Vector_insertInOrder(&v, &nums[i], sizeof(int), compararInt);
    }

    int prueba = 40;
    Vector_insertInOrder(&v, &prueba, sizeof(int), compararInt);

    int valor;
    Vector_getByPos(&v, v.ce - 1, &valor, sizeof(int));
    if (valor == 40) {
        printf("Insercion al final correcta\n");
    } else {
        printf("Error en la insercion al final\n");
    }
    printf("Vector resultado: ");
    imprimir_vector(&v);

    Vector_destroy(&v);
}





MU_TEST_SUITE(test_suite) {

    MU_RUN_TEST(test_muestra);
    MU_RUN_TEST(test_vector_create);
    MU_RUN_TEST(test_vector_insert_int);
    //Mas test aca


}

int main(int argc, char *argv[])
{
    prueba_crear_y_destruir();
    prueba_leer_vector_vacio();
    prueba_insercion_y_ordenamiento();
    prueba_busqueda_binaria();
    prueba_insertar_no_repetidos();
    prueba_map();
    prueba_insertar_mas_alla_del_tamanio();
    prueba_insertar_elemento_al_principio();
    prueba_insertar_elemento_al_final();
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}


