#include "GameObject.h"

#define GAME_OBJECT_TYPE_DESCRIPTOR "GameObject"

// CONSTRUCTOR
void* GameObject_create(GameObject* self, char* textureID, char* objectID, float x, float y){
    static const char dtype[DTYPE_LENGTH] = GAME_OBJECT_TYPE_DESCRIPTOR;

    Object_create(&self->base);
    self->base.dtype = dtype;
    self->pvtable = self->base.pvtable;

    // Direcciones de metodos, asignacion de metodos para simplificar uso
    // Agregar metodo si hay sobreescritura o nuevo metodo
    TMethod methods[] = {
        {"setPosition", 2, "GameObject_setPosition", GameObject_setPosition},
        {"setHeight", 1, "GameObject_setHeight", GameObject_setHeight},
        {"setWidth", 1, "GameObject_setWidth", GameObject_setWidth},
        {"setVelocity", 1, "GameObject_setVelocity", GameObject_setVelocity},
        {"setTextureId", 1, "GameObject_setTextureId", GameObject_setTextureId},
        {"setObjectId", 1, "GameObject_setObjectId", GameObject_setObjectId},
        {"setCurrentFrame", 1, "GameObject_setCurrentFrame", GameObject_setCurrentFrame},
        {"setCurrentRow", 1, "GameObject_setCurrentFrame", GameObject_setCurrentRow},
        {"getPosition", 2, "GameObject_getPosition", GameObject_getPosition},
        {"getHeight", 1, "GameObject_getHeight", GameObject_getHeight},
        {"getWidth", 1, "GameObject_getWidth", GameObject_getWidth},
        {"getVelocity", 1, "GameObject_getVelocity", GameObject_getVelocity},
        {"getTextureId", 1, "GameObject_getTextureId", GameObject_getTextureId},
        {"getObjectId", 1, "GameObject_getObjectId", GameObject_getObjectId},
        {"getCurrentFrame", 1, "GameObject_getCurrentFrame", GameObject_getCurrentFrame},
        {"getCurrentRow", 1, "GameObject_getCurrentRow", GameObject_getCurrentRow},
        {"toString", 1, "GameObject_toString", GameObject_toString}, // Sobreescritura
        {"draw", 1, "GameObject_draw", GameObject_draw},
        {"update", 0, "GameObject_update", GameObject_update},
        {"clean", 0, "GameObject_clean", GameObject_clean},
        {"destroy", 0, "GameObject_destroy", GameObject_destroy}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));

    // Inicia los parametros del GameObject
    GameObject_setTextureId(self, textureID);
    GameObject_setObjectId(self, objectID);
    GameObject_setPosition(self, x, y);
    Vector2D vel = {0, 0};
    GameObject_setVelocity(self, vel);

    // Busco en el vector de texturas el ancho y alto de la textura
    void* nodo = Vector_bsearch(&VecTex, (void*)textureID, compararIdTex);
    if(nodo == NULL){
        printf("Error, la id '%s' no se encuentra.\n", textureID);
        return NULL;
    }
    t_map textura = *(t_map*)(nodo);

    GameObject_setHeight(self, textura.alto);
    GameObject_setWidth(self, textura.ancho);

    return self;

}

// SET
int GameObject_setPosition(GameObject* self, float x, float y){
    Vector2D_setX(&self->position, x);
    Vector2D_setY(&self->position, y);

    return 1;
}

int GameObject_setHeight(GameObject* self, int height) {
    self->height = height;

    return 1;
}

int GameObject_setWidth(GameObject* self, int width) {
    self->width = width;

    return 1;
}

int GameObject_setVelocity(GameObject* self, Vector2D vel) {
    self->velocity = vel;

    return 1;
}

int GameObject_setTextureId(GameObject* self, char* textureID){
    strcpy(self->textureId, textureID);

    setCurrentFrame(self, 1);
    setCurrentRow(self, 1);

    return 1;
}

int GameObject_setObjectId(GameObject* self, char* objectID){
    strcpy(self->objectId, objectID);

    return 1;
}

int GameObject_setCurrentFrame(GameObject* self, int currentFrame){
    self->currentFrame = currentFrame;

    return 1;
}

int GameObject_setCurrentRow(GameObject* self, int currentRow){
    self->currentRow = currentRow;

    return 1;
}


int setPosition(GameObject* self, float x, float y){
    void* m = _getMethod((Object*)self, "setPosition");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, float, float))m)(self, x, y);
}

int setHeight(GameObject* self, int height) {
    void* m = _getMethod((Object*)self, "setHeight");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, int))m)(self, height);
}

int setWidth(GameObject* self, int width) {
    void* m = _getMethod((Object*)self, "setWidth");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, int))m)(self, width);
}

int setVelocity(GameObject* self, Vector2D vel) {
    void* m = _getMethod((Object*)self, "setVelocity");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, Vector2D))m)(self, vel);
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

int setCurrentFrame(GameObject* self, int currentFrame) {
    void* m = _getMethod((Object*)self, "setCurrentFrame");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, int))m)(self, currentFrame);
}

int setCurrentRow(GameObject* self, int currentRow) {
    void* m = _getMethod((Object*)self, "setCurrentRow");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, int))m)(self, currentRow);
}


// GET
void GameObject_getPosition(GameObject* self, float* x, float* y){
    if (x != NULL) {
        *x = Vector2D_getX(&self->position);
    }
    if (y != NULL) {
        *y = Vector2D_getY(&self->position);
    }
}

void GameObject_getHeight(GameObject* self, int* height) {
    if (height != NULL) {
        *height = self->height;
    }
}

void GameObject_getWidth(GameObject* self, int* width) {
    if (width != NULL) {
        *width = self->width;
    }
}

void GameObject_getVelocity(GameObject* self, Vector2D* vel) {
    if (vel != NULL) {
        *vel = self->velocity;
    }
}

void GameObject_getTextureId(GameObject* self, char* buffer) {
    strcpy(buffer, self->textureId);
}

void GameObject_getObjectId(GameObject* self, char* buffer) {
    strcpy(buffer, self->objectId);
}

void GameObject_getCurrentFrame(GameObject* self, int* currentFrame) {
    if (currentFrame != NULL) {
        *currentFrame = self->currentFrame;
    }
}

void GameObject_getCurrentRow(GameObject* self, int* currentRow) {
    if (currentRow != NULL) {
        *currentRow = self->currentRow;
    }
}


void getPosition(GameObject* self, float* x, float* y){
    void* m = _getMethod((Object*)self, "getPosition");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, float*, float*))m)(self, x, y);
}

void getHeight(GameObject* self, int* height) {
    void* m = _getMethod((Object*)self, "getHeight");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, int*))m)(self, height);
}

void getWidth(GameObject* self, int* width) {
    void* m = _getMethod((Object*)self, "getWidth");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, int*))m)(self, width);
}

void getVelocity(GameObject* self, Vector2D* vel) {
    void* m = _getMethod((Object*)self, "getVelocity");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, Vector2D*))m)(self, vel);
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

void getCurrentFrame(GameObject* self, int* currentFrame){
    void* m = _getMethod((Object*)self, "getCurrentFrame");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, int*))m)(self, currentFrame);
}

void getCurrentRow(GameObject* self, int* currentRow){
    void* m = _getMethod((Object*)self, "getCurrentRow");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, int*))m)(self, currentRow);
}


// OTROS
char* GameObject_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding GameObject) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

void GameObject_draw(GameObject* self, SDL_Renderer* pRenderer){
    char buffer[CAPACIDAD];
    GameObject_getTextureId(self, buffer);
    //TextureManager_draw(buffer, self->x, self->y, pRenderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(buffer, (int)Vector2D_getX(&self->position), (int)Vector2D_getY(&self->position), self->currentRow, self->currentFrame,pRenderer, SDL_FLIP_NONE);
}

int GameObject_update(GameObject* self) {
    Vector2D_add(&self->velocity, &self->acceleration);
    Vector2D_add(&self->position, &self->velocity);

    return 1;
}

int GameObject_clean(GameObject* self) {
    return 1;
}

void GameObject_destroy(GameObject* self) {
    return;
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
