#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Object.h"



void* Object_create(Object* self){
    static const struct SObjectVTable ovtable = {
        .getId = Object_getId,
        .toString = Object_toString,
        .getType = Object_getType,
        .destroy = Object_destroy
    };
    static const char dtype[DTYPE_LENGTH] = OBJECT_TYPE_DESCRIPTOR;
    self->dtype = dtype;

    self->ovtable = &ovtable;
    self->id = self;

    //To improve readability for the user of the class (aka o->method(&o)), this is optional.
    self->toString  = toString;
    self->getId     = getId;
    self->getType   = getType;
    self->destroy   = destroy;
    return self;
}



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

void* getId(Object* obj){
    return obj->ovtable->getId(obj);
}

char* toString(Object* obj, char* buffer){
    return obj->ovtable->toString(obj, buffer);
}

char* getType(Object* obj, char* buffer){
    return obj->ovtable->getType(obj, buffer);
}

void destroy(Object* obj){
    obj->ovtable->destroy(obj);
}


