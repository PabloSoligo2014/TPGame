#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
// Inspired by the works of Axel-Tobias Schreiner and Miro Samek among others.

#include <SDL2/SDL.h>
#include "Object.h"
#include "TextureManager.h"
#include "Vector.h"


typedef struct sgameobject{
    Object base; // Herencia de Object
    Vector* pvtable;
    // Capaz que no debe ser unsigned
    //unsigned int x;
    //unsigned int y;
    int x;
    int y;
    char textureId[CAPACIDAD];
    char objectId[CAPACIDAD];
    int currentFrame;
    int currentRow;
}GameObject;

// CONSTRUCTOR
void* GameObject_create(GameObject* self, char* textureID, char* objectID, int x, int y);


// SET
int GameObject_setPosition(GameObject* self, int x, int y);
int GameObject_setTextureId(GameObject* self, char* textureID);
int GameObject_setObjectId(GameObject* self, char* buffer);

int setPosition(GameObject* self, int x, int y);
int setTextureId(GameObject* self, char* textureID);
int setObjectId(GameObject* self, char* textureID);


// GET
void GameObject_getPosition(GameObject* self, int* x, int* y);
void GameObject_getTextureId(GameObject* self, char* buffer);
void GameObject_getObjectId(GameObject* self, char* buffer);

void getPosition(GameObject* self, int* x, int* y);
void getTextureId(GameObject* self, char* buffer);
void getObjectId(GameObject* self, char* buffer);


// OTROS
char* GameObject_toString(Object* self, char* buffer);
void GameObject_draw(GameObject* self, SDL_Renderer* pRenderer);
int GameObject_update(GameObject* self);
int GameObject_clean(GameObject* self);

int draw(GameObject* self, SDL_Renderer* pRenderer);
int update(GameObject* self);
int clean(GameObject* self);


// CMP
int compararTextureID(const void* a, const void* b);
int compararObjectID(const void* a, const void* b);
#endif
