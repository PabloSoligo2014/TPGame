#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
// Inspired by the works of Axel-Tobias Schreiner and Miro Samek among others.

#define DTYPE_LENGTH 64


#include "Vector.h"

typedef struct{
    char methodName[DTYPE_LENGTH];
    unsigned args_count;
    char tag[DTYPE_LENGTH];
    void* method;
}TMethod;

int cmp_method(const void* a, const void* b);

typedef struct sobject{
    void* id;
    const char* dtype; // Data type of the object
    Vector vtable;
    Vector* pvtable;
}Object;



//void* Invoke(Object* obj, const char* method, ...);
void _method_assign(Vector* v, TMethod* methods, unsigned methodCount);
void* _getMethod(Object* self, const char* methodName);

void* Object_create(Object* self);
void Object_destroy(Object* self);
void* Object_getId(Object* self);
char* Object_toString(Object* self, char* buffer);
char* Object_getType(Object* self, char* buffer);

void destroy(Object* self);
void* getId(Object* self);
char* toString(Object* self, char* buffer);
char* getType(Object* self, char* buffer);




#endif
