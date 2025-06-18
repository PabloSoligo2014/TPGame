#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
// Inspired by the works of Axel-Tobias Schreiner and Miro Samek among others.

#include <SDL2/SDL.h>
#include "Object.h"
#include "TextureManager.h"
#include "Vector.h"
#include "Vector2D.h"


typedef struct sgameobject{
    Object base; // Herencia de Object
    Vector* pvtable;
    Vector2D position;
    int height;
    int width;
    Vector2D velocity;
    Vector2D acceleration;
    char textureId[CAPACIDAD];
    char objectId[CAPACIDAD];
    int currentFrame;
    int currentRow;
}GameObject;

// CONSTRUCTOR
void* GameObject_create(GameObject* self, char* textureID, char* objectID, float x, float y);


// SET
int GameObject_setPosition(GameObject* self, float x, float y);
int GameObject_setHeight(GameObject* self, int height);
int GameObject_setWidth(GameObject* self, int width);
int GameObject_setVelocity(GameObject* self, Vector2D vel);
int GameObject_setTextureId(GameObject* self, char* textureID);
int GameObject_setObjectId(GameObject* self, char* buffer);
int GameObject_setCurrentFrame(GameObject* self, int currentFrame);
int GameObject_setCurrentRow(GameObject* self, int currentRow);

int setPosition(GameObject* self, float x, float y);
int setHeight(GameObject* self, int height);
int setWidth(GameObject* self, int width);
int setVelocity(GameObject* self, Vector2D vel);
int setTextureId(GameObject* self, char* textureID);
int setObjectId(GameObject* self, char* textureID);
int setCurrentFrame(GameObject* self, int currentFrame);
int setCurrentRow(GameObject* self, int currentRow);


// GET
void GameObject_getPosition(GameObject* self, float* x, float* y);
void GameObject_getHeight(GameObject* self, int* height);
void GameObject_getWidth(GameObject* self, int* width);
void GameObject_getVelocity(GameObject* self, Vector2D* vel);
void GameObject_getTextureId(GameObject* self, char* buffer);
void GameObject_getObjectId(GameObject* self, char* buffer);
void GameObject_getCurrentFrame(GameObject* self, int* currentFrame);
void GameObject_getCurrentRow(GameObject* self, int* currentRow);

void getPosition(GameObject* self, float* x, float* y);
void getHeight(GameObject* self, int* height);
void getWidth(GameObject* self, int* width);
void getVelocity(GameObject* self, Vector2D* vel);
void getTextureId(GameObject* self, char* buffer);
void getObjectId(GameObject* self, char* buffer);
void getCurrentFrame(GameObject* self, int* currentFrame);
void getCurrentRow(GameObject* self, int* currentRow);


// OTROS
char* GameObject_toString(Object* self, char* buffer);
void GameObject_draw(GameObject* self, SDL_Renderer* pRenderer);
int GameObject_update(GameObject* self);
int GameObject_clean(GameObject* self);
void GameObject_destroy(GameObject* self);

int draw(GameObject* self, SDL_Renderer* pRenderer);
int update(GameObject* self);
int clean(GameObject* self);


// CMP
int compararTextureID(const void* a, const void* b);
int compararObjectID(const void* a, const void* b);

#endif
