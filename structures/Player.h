#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Object.h"
#include "GameObject.h"
#include "Vector.h"

#define VELOCIDAD 5

typedef struct splayer{
    GameObject base; // Inheritance from Object
    Vector* pvtable;
    int speedX;
    int speedY;
}Player;

void* Player_create(Player* self, char* textureID, char* objectID, int x, int y);
char* Player_toString(Object* self, char* buffer);
int Player_setPosition(GameObject* self, int x, int y);
void Player_getPosition(GameObject* self, int* x, int* y);

int Player_setTextureId(Player* self, char* textureID);
void Player_draw(Player* self, SDL_Renderer* pRenderer);
int Player_update(Player* self);
int Player_clean(Player* self);

#endif // PLAYER_H_INCLUDED
