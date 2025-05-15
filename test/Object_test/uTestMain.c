#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../test_utils.h"
#include "../minunit.h"
#include "../../structures/Object.h"

#define MAX_ERROR_MSG 512

MU_TEST(test_object_create){
    char errorMsg[MAX_ERROR_MSG];
    Object o;
    Object* po;
    po = Object_create(&o);

    sprintf(errorMsg, "id %p must be equal to address %p\n",  po->getId(po), &o);

    mu_assert((po->getId(po))==&o, errorMsg);
    po->destroy(po);
}

MU_TEST(test_object_string){
    char errorMsg[MAX_ERROR_MSG];
    char expecterResult[128];
    char buffer[128];
    Object o;
    Object* po;
    sprintf(expecterResult, "My type is Object and my id is %p", &o);


    po = Object_create(&o);
    po->toString(po, buffer);
    sprintf(errorMsg, "to string must be %s and it was %s\n", buffer, buffer);

    mu_assert(strcmp(expecterResult, buffer)==0, errorMsg);
    po->destroy(po);
}


MU_TEST(test_object_type_descriptor){
    char errorMsg[MAX_ERROR_MSG];
    char expecterResult[] = OBJECT_TYPE_DESCRIPTOR;
    char buffer[128];
    Object o;
    Object* po;

    po = Object_create(&o);
    po->getType(po, buffer);
    sprintf(errorMsg, "type descriptor must be %s and it was %s\n", expecterResult, buffer);

    mu_assert(strcmp(expecterResult, buffer)==0, errorMsg);
    po->destroy(po);

}



MU_TEST_SUITE(test_suite) {

    MU_RUN_TEST(test_object_create);
    MU_RUN_TEST(test_object_string);
    MU_RUN_TEST(test_object_type_descriptor);

}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}


