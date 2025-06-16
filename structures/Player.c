#include "Player.h"

#define PLAYER_TYPE_DESCRIPTOR "Player"


void* Player_create(Player* self, char* textureID, char* objectID, int x, int y){
    static const char dtype[DTYPE_LENGTH] = PLAYER_TYPE_DESCRIPTOR;

    GameObject_create(&self->base, textureID, objectID,x, y);
    self->base.base.dtype = dtype;
    self->pvtable = self->base.pvtable;

    //Direcciones de metodos, asignacion de metodos para simplificar uso
    TMethod methods[] = {
        {"toString", 1, "Player_toString", Player_toString},//overriding!!
        {"setPosition", 2, "Player_setPosition", Player_setPosition},
        {"getPosition", 2, "Player_getPosition", Player_getPosition},
        {"setTextureId", 1, "Player_setTextureId", Player_setTextureId},
        {"draw", 1, "Player_draw", Player_draw},
        {"update", 0, "Player_update", Player_update},
        {"clean", 0, "Player_clean", Player_clean}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));
    self->speedX = VELOCIDAD;
    self->speedY = VELOCIDAD;
    return self;
}

char* Player_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding Player) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}


int Player_setPosition(GameObject* self, int x, int y){
    self->x = x;
    self->y = y;
    return 1;
}


void Player_getPosition(GameObject* self, int* x, int* y){
    if (x != NULL) {
        *x = self->x;
    }
    if (y != NULL) {
        *y = self->y;
    }
}


int Player_setTextureId(Player* self, char* textureID) {
    GameObject_setTextureId(&self->base, textureID);
    return 1;
}

void Player_draw(Player* self, SDL_Renderer* pRenderer) {
    GameObject_draw(&self->base, pRenderer);
}


int Player_update(Player* self) {
    int x;
    int y;
    GameObject_getPosition(&self->base, &x, &y);

    if(x > 800 - 110) {
        self->speedX = -1 * VELOCIDAD;
    }
    if(x < 0) {
        self->speedX = VELOCIDAD;
    }
    x = x + self->speedX;

    if(y > 600 - 110) {
        self->speedY = -1 * VELOCIDAD;
    }
    if(y < 0) {
        self->speedY = VELOCIDAD;
    }
    y = y + self->speedY;

    GameObject_setPosition(&self->base, x, y);

    return 1;
}


int Player_clean(Player* self) {
    return 1;
}
