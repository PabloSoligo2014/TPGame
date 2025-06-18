#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Object.h"
#include "GameObject.h"
#include "Vector.h"
#include "InputHandler.h"

typedef struct splayer{
    GameObject base; // Herencia de GameObject
    Vector* pvtable;
}Player;

// CONSTRUCTOR
void* Player_create(Player* self, char* textureID, char* objectID, float x, float y);

// SET
int Player_setPosition(GameObject* self, float x, float y);
int Player_setTextureId(Player* self, char* textureID);

// GET
void Player_getPosition(GameObject* self, float* x, float* y);

// OTROS
char* Player_toString(Object* self, char* buffer);
void Player_draw(Player* self, SDL_Renderer* pRenderer);
int Player_update(Player* self);
int Player_clean(Player* self);
void Player_destroy(Player* self);

#endif // PLAYER_H_INCLUDED
