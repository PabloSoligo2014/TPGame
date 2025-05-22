#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
// Inspired by the works of Axel-Tobias Schreiner and Miro Samek among others.

#include "Object.h"
#include "Vector.h"

typedef struct sgameobject{
    Object base; // Inheritance from Object
    Vector* pvtable;
    unsigned int x;
    unsigned int y;
}GameObject;


void* GameObject_create(GameObject* self);
int GameObject_setPosition(GameObject* self, unsigned int x, unsigned int y);
void GameObject_getPosition(GameObject* self, unsigned int* x, unsigned int* y);
char* GameObject_toString(Object* self, char* buffer);


int setPosition(GameObject* self, unsigned int x, unsigned int y);
void getPosition(GameObject* self, unsigned int* x, unsigned int* y);


#endif
