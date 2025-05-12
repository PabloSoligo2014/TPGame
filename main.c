#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "structures/Vector.h"
#include "structures/Game.h"

/*Pablo Soligo. Plantilla de proyecto codeblocks para proyectos SDL.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuraci�n de proyecto.
Esto compila al solo efecto de demostrar que estan los enlaces correctamente
configurados a la biblioteca SDL.
*/

int main(int argc, char *argv[]){

    //Codigo prueba del bsearch
    //Invito a probarlo
    Vector v;
    Vector_create(&v,10);
    int i;

    for(i=0;i<15;i++){
        Vector_insertInOrder(&v,&i,sizeof(int),compararInt);
    }


    for(i=0;i<15;i++){
        printf("%d - ", *(int*)(((tNodo*)v.vec[i].dato)));
    }

    int a = 9;
    tNodo* nodo = Vector_bsearch(&v, &a, compararInt);

    if (nodo) {
        *(int*)(nodo->dato) = 90;  // Cambia el valor encontrado con bsearch
    }
    printf("\n\n");

    for(i=0;i<15;i++){
        printf("%d - ", *(int*)(((tNodo*)v.vec[i].dato)));
    }

    /*
    Game* game=Game_create();
    Game_init(game,"La IEEE 754 llego al barrio",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                800,
                                                600,
                                                SDL_WINDOW_SHOWN,
                                                100);

    while(Game_isRunning(game)){
        Game_handleEvents(game);
        Game_update(game);
        Game_render(game);
    }

    Game_clean(game);
    */return 0;
}

