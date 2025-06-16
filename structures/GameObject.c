#include "GameObject.h"

#define GAME_OBJECT_TYPE_DESCRIPTOR "GameObject"

// CONSTRUCTOR
void* GameObject_create(GameObject* self, char* textureID, char* objectID, int x, int y){
    static const char dtype[DTYPE_LENGTH] = GAME_OBJECT_TYPE_DESCRIPTOR;

    Object_create(&self->base);
    self->base.dtype = dtype;
    self->pvtable = self->base.pvtable;

    // Direcciones de metodos, asignacion de metodos para simplificar uso
    // Agregar metodo si hay sobreescritura o nuevo metodo
    TMethod methods[] = {
        {"setPosition", 2, "GameObject_setPosition", GameObject_setPosition},
        {"setTextureId", 1, "GameObject_setTextureId", GameObject_setTextureId},
        {"setObjectId", 1, "GameObject_setObjectId", GameObject_setObjectId},
        {"getPosition", 2, "GameObject_getPosition", GameObject_getPosition},
        {"getTextureId", 1, "GameObject_getTextureId", GameObject_getTextureId},
        {"getObjectId", 1, "GameObject_getObjectId", GameObject_getObjectId},
        {"toString", 1, "GameObject_toString", GameObject_toString}, // Sobreescritura
        {"draw", 1, "GameObject_draw", GameObject_draw},
        {"update", 0, "GameObject_update", GameObject_update},
        {"clean", 0, "GameObject_clean", GameObject_clean}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));

    // Inicia los parametros del GameObject
    GameObject_setTextureId(self, textureID);
    GameObject_setObjectId(self, objectID);
    GameObject_setPosition(self, x, y);

    return self;

}

// SET
int GameObject_setPosition(GameObject* self, int x, int y){
    self->x = x;
    self->y = y;

    return 1;
}

int GameObject_setTextureId(GameObject* self, char* textureID){
    strcpy(self->textureId, textureID);

    self->currentRow = 1;
    self->currentFrame = 1;

    return 1;
}

int GameObject_setObjectId(GameObject* self, char* objectID){
    strcpy(self->objectId, objectID);

    return 1;
}


int setPosition(GameObject* self, int x, int y){
    void* m = _getMethod((Object*)self, "setPosition");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, int, int))m)(self, x, y);
}

int setTextureId(GameObject* self, char* textureID) {
    void* m = _getMethod((Object*)self, "setTextureId");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, char*))m)(self, textureID);
}

int setObjectId(GameObject* self, char* objectID) {
    void* m = _getMethod((Object*)self, "setObjectId");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, char*))m)(self, objectID);
}


// GET
void GameObject_getPosition(GameObject* self, int* x, int* y){
    if (x != NULL) {
        *x = self->x;
    }
    if (y != NULL) {
        *y = self->y;
    }
}

void GameObject_getTextureId(GameObject* self, char* buffer) {
    strcpy(buffer, self->textureId);
}

void GameObject_getObjectId(GameObject* self, char* buffer) {
    strcpy(buffer, self->objectId);
}


void getPosition(GameObject* self, int* x, int* y){
    void* m = _getMethod((Object*)self, "getPosition");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, int*, int*))m)(self, x, y);
}

void getTextureId(GameObject* self, char* buffer){
    void* m = _getMethod((Object*)self, "getTextureId");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, char*))m)(self, buffer);
}

void getObjectId(GameObject* self, char* buffer){
    void* m = _getMethod((Object*)self, "getObjectId");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, char*))m)(self, buffer);
}


// OTROS
char* GameObject_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding GameObject) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

void GameObject_draw(GameObject* self, SDL_Renderer* pRenderer){
    char buffer[CAPACIDAD];
    GameObject_getTextureId(self, buffer);
    TextureManager_draw(buffer, self->x, self->y, pRenderer, SDL_FLIP_NONE);
    //TextureManager_drawFrame(buffer, self->x, self->y, self->currentRow, self->currentFrame,pRenderer, SDL_FLIP_NONE);
}

int GameObject_update(GameObject* self) {
    int x;
    int y;
    getPosition(self, &x, &y);


    setPosition(self, x, y);

    return 1;
}

int GameObject_clean(GameObject* self) {
    return 1;
}


int draw(GameObject* self, SDL_Renderer* pRenderer){
    void* m = _getMethod((Object*)self, "draw");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, SDL_Renderer*))m)(self, pRenderer);
}

int update(GameObject* self) {
    void* m = _getMethod((Object*)self, "update");
    if(m == NULL) {
        return 0;
    }
    return ((int(*)(GameObject*))m)(self);
}

int clean(GameObject* self) {
    void* m = _getMethod((Object*)self, "clean");
    if(m == NULL) {
        return 0;
    }
    return ((int(*)(GameObject*))m)(self);
}


// CMP
int compararTextureID(const void* a, const void* b) {
    GameObject* a1 = (GameObject*)a;
    GameObject* b1 = (GameObject*)b;

    return strcmp(a1->textureId, b1->textureId);
}

int compararObjectID(const void* a, const void* b) {
    GameObject* a1 = (GameObject*)a;
    GameObject* b1 = (GameObject*)b;

    return strcmp(a1->objectId, b1->objectId);
}
