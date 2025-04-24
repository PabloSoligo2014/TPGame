#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include "structures/Game.h"

/**
Pablo Soligo. Plantilla de proyecto codeblocks para proyectos SDL.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuraci�n de proyecto.
Esto compila al solo efecto de demostrar que estan los enlaces correctamente
configurados a la biblioteca SDL.
*/

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}


int main(int argc, char *argv[])
{
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

    return 0;
}


