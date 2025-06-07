#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Object.h"
#include "../test/test_utils.h"
#define OBJECT_TYPE_DESCRIPTOR "Object"

int cmp_method(const void* a, const void* b){
    return strcmp(((TMethod*)a)->methodName, ((TMethod*)b)->methodName);
}



void* Object_create(Object* self){
    static const char dtype[DTYPE_LENGTH] = OBJECT_TYPE_DESCRIPTOR;
    self->dtype = dtype;
    self->id = self;

    //Direcciones de metodos, asignacion de metodos para simplificar uso
    TMethod methods[] = {
        {"getId", 0, "Object_getId", Object_getId},
        {"toString", 1, "Object_toString", Object_toString},
        {"getType", 1, "Object_getType",Object_getType},
        {"destroy", 0, "Object_destroy",Object_destroy}
    };

    Vector_create(&self->vtable, 10);
    self->pvtable = &self->vtable;

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));


    return self;
}


void* _getMethod(Object* self, const char* methodName){
    TMethod method;
    TMethod* result;
    strcpy(method.methodName, methodName);
    result = Vector_bsearch(&self->vtable, &method, cmp_method);
    if (result!=NULL)
        return result->method;
    else
        return result;
}

/*
void* Invoke(Object* obj, const char* method, ...){
    void* result = NULL;
    va_list args;
    va_start(args, method);
    //
    result = Vector_bsearch(&obj->vtable, method, cmp_method);
    if(!result){
        //Assert change to error handling
        fprintf(stderr, "Method %s not found\n", method);
        va_end(args);
        return NULL;
    }
    va_end(args);
    return NULL;
}
*/

void* Object_getId(Object* self){
    return self->id;
}

char* Object_toString(Object* self, char* buffer){
    sprintf(buffer, "My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

char* Object_getType(Object* self, char* buffer){
    strcpy(buffer, self->dtype);
    return buffer;


}

void Object_destroy(Object* self){
    //Nothing to do, only static or stack memory
    return;
}


void _method_assign(Vector* v, TMethod* methods, unsigned methodCount){

    for(int i = 0; i < methodCount; i++){
        Vector_insertInOrder(v, &methods[i], sizeof(TMethod), cmp_method);
    }
}

//Metodos virtuales

void* getId(Object* self){
    void* m = _getMethod(self, "getId");
    if(m == NULL){
        return NULL;
    }
    return ((void*(*)(Object*))m)(self);
}
char* toString(Object* self, char* buffer){
    void* m = _getMethod(self, "toString");
    if(m == NULL){
        return NULL;
    }
    return ((char*(*)(Object*, char*))m)(self, buffer);
}
char* getType(Object* self, char* buffer){
    void* m = _getMethod(self, "getType");
    if(m == NULL){
        return NULL;
    }
    return ((char*(*)(Object*, char*))m)(self, buffer);
}

void destroy(Object* self){
    void* m = _getMethod(self, "destroy");
    if(m == NULL){
        return;
    }
    ((void(*)(Object*))m)(self);
}
