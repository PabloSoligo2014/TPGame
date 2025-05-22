#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../test_utils.h"
#include "../minunit.h"
#include "../../structures/Object.h"
#include "../../structures/GameObject.h"
#define MAX_MESSAGE 2048
#define SHORT_MESSAGE 512

MU_TEST(test_object_create){
    char errorMsg[MAX_MESSAGE];
    Object o;
    Object* po;
    po = Object_create(&o);

    sprintf(errorMsg, "id %p must be equal to address %p\n",  getId(po), &o);

    mu_assert((getId(po))==&o, errorMsg);
    destroy(po);
}

MU_TEST(test_object_string){
    char errorMsg[MAX_MESSAGE];
    char expecterResult[128];
    char buffer[128];
    Object o;
    Object* po;
    sprintf(expecterResult, "My type is Object and my id is %p", &o);


    po = Object_create(&o);
    toString(po, buffer);
    sprintf(errorMsg, "to string must be %s and it was %s\n", expecterResult, buffer);

    mu_assert(strcmp(expecterResult, buffer)==0, errorMsg);
    destroy(po);
}


MU_TEST(test_object_type_descriptor){
    char errorMsg[MAX_MESSAGE];
    char expecterResult[] = "Object";
    char buffer[SHORT_MESSAGE];
    Object o;
    Object* po;

    po = Object_create(&o);
    getType(po, buffer);

    sprintf(errorMsg, "type descriptor must be %s and it was %s\n", expecterResult, buffer);

    mu_assert(strcmp(expecterResult, buffer)==0, errorMsg);
    destroy(po);
}

MU_TEST(test_game_object_overriding){
    //El metodo toString esta sobre escrito, debe llamar al metodo de la
    //clase instanciada, no la referenciada
    char errorMsg[MAX_MESSAGE];
    char expecterResult[SHORT_MESSAGE];
    char buffer[SHORT_MESSAGE];
    GameObject o;
    Object* po;
    po = GameObject_create(&o);

    //overriding toString test
    toString(po, buffer);
    sprintf(expecterResult, "(Testing overriding GameObject) -> My type is GameObject and my id is %p", getId(po));

    //Error message
    sprintf(errorMsg, "toString must be %s and it was %s\n", expecterResult, buffer);

    mu_assert(strcmp(expecterResult, buffer)==0, errorMsg);
    destroy(po);
}


MU_TEST(test_game_object_base_method){
    //El metodo toString esta sobre escrito, debe llamar al metodo de la
    //clase instanciada, no la referenciada
    char errorMsg[MAX_MESSAGE];
    void* id;

    GameObject o;
    GameObject* po;
    po = GameObject_create(&o);

    //It must be call parent method...
    id = getId((Object*)po);

    sprintf(errorMsg, "getId should return the address %p and return %p\n", po, id);

    mu_assert(po==id, errorMsg);
    destroy((Object*)po);
}





MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_object_create);
    MU_RUN_TEST(test_object_string);
    MU_RUN_TEST(test_object_type_descriptor);
    MU_RUN_TEST(test_game_object_overriding);
    MU_RUN_TEST(test_game_object_base_method);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}


