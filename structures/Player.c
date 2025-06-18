#include "Player.h"

#define PLAYER_TYPE_DESCRIPTOR "Player"

// CONSTRUCTOR
void* Player_create(Player* self, char* textureID, char* objectID, float x, float y){
    static const char dtype[DTYPE_LENGTH] = PLAYER_TYPE_DESCRIPTOR;

    GameObject_create(&self->base, textureID, objectID,x, y);
    self->base.base.dtype = dtype;
    self->pvtable = self->base.pvtable;

    //Direcciones de metodos, asignacion de metodos para simplificar uso
    TMethod methods[] = {
        {"setPosition", 2, "Player_setPosition", Player_setPosition},
        {"setTextureId", 1, "Player_setTextureId", Player_setTextureId},
        {"getPosition", 2, "Player_getPosition", Player_getPosition},
        {"toString", 1, "Player_toString", Player_toString}, // Sobreescritura
        {"draw", 1, "Player_draw", Player_draw},
        {"update", 0, "Player_update", Player_update},
        {"clean", 0, "Player_clean", Player_clean},
        {"destroy", 0, "Player_destroy", Player_destroy}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));
    return self;
}


// SET
int Player_setPosition(GameObject* self, float x, float y){
    Vector2D_setX(&self->position, x);
    Vector2D_setY(&self->position, y);
    return 1;
}

int Player_setTextureId(Player* self, char* textureID) {
    GameObject_setTextureId(&self->base, textureID);
    return 1;
}


// GET
void Player_getPosition(GameObject* self, float* x, float* y){
    if (x != NULL) {
        *x = Vector2D_getX(&self->position);
    }
    if (y != NULL) {
        *y = Vector2D_getY(&self->position);
    }
}


// OTROS
char* Player_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding Player) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

void Player_draw(Player* self, SDL_Renderer* pRenderer) {
    GameObject_draw(&self->base, pRenderer);
}

int Player_update(Player* self) {
    float x;
    float y;
    getPosition(&self->base, &x, &y);
    int height;
    getHeight(&self->base, &height);
    int width;
    getWidth(&self->base, &width);
    getPosition(&self->base, &x, &y);

    Vector2D newVel;
    getVelocity(&self->base, &newVel);


    if(InputHandler_isKeyDown(SDL_SCANCODE_RIGHT)) {
        Vector2D_setX(&newVel, 2);
    }
    if(InputHandler_isKeyDown(SDL_SCANCODE_LEFT)) {
        Vector2D_setX(&newVel, -2);
    }
    if(InputHandler_isKeyDown(SDL_SCANCODE_UP)) {
        Vector2D_setY(&newVel, -2);
    }
    if(InputHandler_isKeyDown(SDL_SCANCODE_DOWN)) {
        Vector2D_setY(&newVel, 2);
    }


    if(x > 800) {
        setPosition(&self->base, 0 - width, y);
    }
    if(x < 0 - width) {
        setPosition(&self->base, 800, y);
    }
    if(y > 600) {
        setPosition(&self->base, x, 0 - height);
    }
    if(y + width <= 0) {
        setPosition(&self->base, x, 600);
    }

    setVelocity(&self->base, newVel);
    setCurrentFrame(&self->base, (int)(((SDL_GetTicks() / 100) % 6))); //El 6 me limita a que las animaciones tengan 6 frames
    GameObject_update(&self->base);
    return 1;
}

int Player_clean(Player* self) {
    return 1;
}

void Player_destroy(Player* self) {
    return;
}
