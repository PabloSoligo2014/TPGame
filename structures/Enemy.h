#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Object.h"
#include "GameObject.h"
#include "Vector.h"
#include "InputHandler.h"

typedef struct senemy{
    GameObject base; // Herencia de GameObject
    Vector* pvtable;
}Enemy;

// CONSTRUCTOR
void* Enemy_create(Enemy* self, char* textureID, char* objectID, float x, float y);

// SET
int Enemy_setPosition(GameObject* self, float x, float y);
int Enemy_setTextureId(Enemy* self, char* textureID);

// GET
void Enemy_getPosition(GameObject* self, float* x, float* y);

// OTROS
char* Enemy_toString(Object* self, char* buffer);
void Enemy_draw(Enemy* self, SDL_Renderer* pRenderer);
int Enemy_update(Enemy* self);
int Enemy_clean(Enemy* self);
void Enemy_destroy(Enemy* self);

#endif // ENEMY_H_INCLUDED
