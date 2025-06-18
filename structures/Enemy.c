#include "Enemy.h"

#define ENEMY_TYPE_DESCRIPTOR "Enemy"

// CONSTRUCTOR
void* Enemy_create(Enemy* self, char* textureID, char* objectID, float x, float y){
    static const char dtype[DTYPE_LENGTH] = ENEMY_TYPE_DESCRIPTOR;

    GameObject_create(&self->base, textureID, objectID,x, y);
    self->base.base.dtype = dtype;
    self->pvtable = self->base.pvtable;

    //Direcciones de metodos, asignacion de metodos para simplificar uso
    TMethod methods[] = {
        {"setPosition", 2, "Enemy_setPosition", Enemy_setPosition},
        {"setTextureId", 1, "Enemy_setTextureId", Enemy_setTextureId},
        {"getPosition", 2, "Enemy_getPosition", Enemy_getPosition},
        {"toString", 1, "Enemy_toString", Enemy_toString}, // Sobreescritura
        {"draw", 1, "Enemy_draw", Enemy_draw},
        {"update", 0, "Enemy_update", Enemy_update},
        {"clean", 0, "Enemy_clean", Enemy_clean},
        {"destroy", 0, "Enemy_destroy", Enemy_destroy}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));
    return self;
}


// SET
int Enemy_setPosition(GameObject* self, float x, float y){
    Vector2D_setX(&self->position, x);
    Vector2D_setY(&self->position, y);
    return 1;
}

int Enemy_setTextureId(Enemy* self, char* textureID) {
    GameObject_setTextureId(&self->base, textureID);
    return 1;
}


// GET
void Enemy_getPosition(GameObject* self, float* x, float* y){
    if (x != NULL) {
        *x = Vector2D_getX(&self->position);
    }
    if (y != NULL) {
        *y = Vector2D_getY(&self->position);
    }
}


// OTROS
char* Enemy_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding Enemy) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

void Enemy_draw(Enemy* self, SDL_Renderer* pRenderer) {
    float x, y;
    getPosition(&self->base, &x, &y);
    char buffer[CAPACIDAD];
    getTextureId(&self->base, buffer);
    TextureManager_draw(buffer, x, y, pRenderer, SDL_FLIP_VERTICAL);
}

int Enemy_update(Enemy* self) {
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

    if(InputHandler_isKeyDown(SDL_SCANCODE_SPACE)) {
        Vector2D_setY(&newVel, 5);
    }

    int N = 800 - width;
    if(y > 600) {
        x = rand() % (N + 1);
        setPosition(&self->base, x, 0 - height);
    }

    setVelocity(&self->base, newVel);
    self->base.currentFrame = (int)(((SDL_GetTicks() / 100) % 6)); //El 6 me limita a que las animaciones tengan 6 frames
    GameObject_update(&self->base);
    return 1;
}

int Enemy_clean(Enemy* self) {
    return 1;
}

void Enemy_destroy(Enemy* self) {
    return;
}
