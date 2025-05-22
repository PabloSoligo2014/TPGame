#include "GameObject.h"

#define GAME_OBJECT_TYPE_DESCRIPTOR "GameObject"

void* GameObject_create(GameObject* self){
    static const char dtype[DTYPE_LENGTH] = GAME_OBJECT_TYPE_DESCRIPTOR;

    Object_create(&self->base);
    self->base.dtype = dtype;
    self->pvtable = self->base.pvtable;
    //Vector* vtable = &self->base.vtable;


    //Direcciones de metodos, asignacion de metodos para simplificar uso
    TMethod methods[] = {
        {"toString", 1, "GameObject_toString", GameObject_toString},//overriding!!
        {"setPosition", 2, "GameObject_setPosition", GameObject_setPosition},
        {"getPosition", 2, "GameObject_getPosition", GameObject_getPosition}
    };

    _method_assign(self->pvtable, methods, sizeof(methods)/sizeof(TMethod));
    return self;

}

int GameObject_setPosition(GameObject* self, unsigned int x, unsigned int y){
    self->x = x;
    self->y = y;
    return 1;
}


void GameObject_getPosition(GameObject* self, unsigned int* x, unsigned int* y){
    if (x != NULL) {
        *x = self->x;
    }
    if (y != NULL) {
        *y = self->y;
    }

}

//To test overriding
char* GameObject_toString(Object* self, char* buffer){
    sprintf(buffer, "(Testing overriding GameObject) -> My type is %s and my id is %p", self->dtype, self->id);
    return buffer;
}

int setPosition(GameObject* self, unsigned int x, unsigned int y){
    void* m = _getMethod((Object*)self, "setPosition");
    if(m == NULL){
        return 0;
    }
    return ((int(*)(GameObject*, unsigned int, unsigned int))m)(self, x, y);
}
void getPosition(GameObject* self, unsigned int* x, unsigned int* y){
    void* m = _getMethod((Object*)self, "getPosition");
    if(m == NULL){
        return;
    }
    ((void(*)(GameObject*, unsigned int*, unsigned int*))m)(self, x, y);
}
