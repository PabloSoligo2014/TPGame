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

#define FPS 60
#define DELAY_TIME 1000.0f / FPS

/*Pablo Soligo. Plantilla de proyecto codeblocks para proyectos SDL.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuraci�n de proyecto.
Esto compila al solo efecto de demostrar que estan los enlaces correctamente
configurados a la biblioteca SDL.
*/

int main(int argc, char *argv[]){
    Uint32 frameStart, frameTime;

    Game* game=Game_create();

    Game_init(game,"La IEEE 754 llego al barrio",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                800,
                                                600,
                                                SDL_WINDOW_SHOWN,
                                                100);

    while(Game_isRunning(game)){
        frameStart = SDL_GetTicks();

        Game_handleEvents(game);
        Game_update(game);
        Game_render(game);

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    Game_clean(game);
    return 0;
}

