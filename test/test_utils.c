//TODO Cambiar este import
#include "../structures/Object.h"


int cmp_int(const void* a, const void* b){
    return  *(int*)a-*(int*)b;
}

void show_method(void* m){
    TMethod* pm = (TMethod*)m;
    printf("Nombre: %s, argumentos: %d, tag: %s, direccion: %p\n",
           pm->methodName,
           pm->args_count,
           pm->tag,
           pm->method);
}
