#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
// Inspired by the works of Axel-Tobias Schreiner and Miro Samek among others.

#define DTYPE_LENGTH 20


typedef struct sobject{
    const struct SObjectVTable* ovtable; // Pointer to the virtual table
    void* id;  
    const char* dtype; // Data type of the object
    //Optional
    void *(*getId)(struct sobject* self);
    char* (*toString)(struct sobject* self, char* buffer);
}Object;

struct SObjectVTable{
    void (*destroy)(Object* self);
    void* (*getId)(Object* self);
    char* (*toString)(Object* self, char* buffer);

    //to be implemented
    int (*compare)(Object* self, Object* other);
    int (*copy)(Object* self, Object* other);

};


void* Object_create(Object* self);
void Object_destroy(Object* self);
void* Object_getId(Object* self);
char* Object_toString(Object* self, char* buffer);

void* getId(Object* obj);
char* toString(Object* obj, char* buffer);


#endif