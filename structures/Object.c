#include <stdlib.h>
#include <stdio.h>

#include "Object.h"


void* Object_create(Object* self){
    static const struct SObjectVTable ovtable = {
        .getId = Object_getId,
        .toString = Object_toString,
        .destroy = NULL
    };
    static const char dtype[DTYPE_LENGTH] = "Object";
    self->dtype = dtype;

    self->ovtable = &ovtable;
    self->id = self;

    //Para mejorar la legibilidad
    self->toString  = toString;
    self->getId     = getId;
    return self;
}




void* Object_getId(Object* self){
    return self->id;

}

char* Object_toString(Object* self, char* buffer){
    sprintf(buffer, "My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

void* getId(Object* obj){
    return obj->ovtable->getId(obj);
}

char* toString(Object* obj, char* buffer){

    return obj->ovtable->toString(obj, buffer);
}
