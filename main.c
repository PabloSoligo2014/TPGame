#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
/**
Pablo Soligo. Plantilla de proyecto codeblocks para proyectos SDL.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuración de proyecto.
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
    unsigned char done = 0;
    int k;
    //Mucha de esta parametrizacion puede venir por linea de comando!!
    int delay               = 100;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    SDL_Rect fillRect;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                640,
                                                480,
                                                SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Creamos el lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    //Este horror es solo para saber si las funciones de SDL_Image estan disponibles
    //char* x;
    //IMG_ReadXPMFromArray(&x);

    while (!done){ //Se puede parar tambien cuando no se observen cambios!
        while (SDL_PollEvent(&e) != 0) {
            // Salida del usuario
            if (e.type == SDL_QUIT) {
                puts("Saliendo");
                done = 1;
            }
        }
        // Se limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        fillRect.x = 50; //Pos X
        fillRect.y = 50; //Pos Y
        fillRect.h = 30; //Alto
        fillRect.w = 30; //Ancho

        //Plantilla para pintar cuadrados
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &fillRect);

        fillRect.x = 100; //Pos X
        fillRect.y = 100; //Pos Y
        fillRect.h = 30; //Alto
        fillRect.w = 30; //Ancho

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &fillRect);


        //Plantilla para pintar circulos si gusta mas
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        drawFilledCircle(renderer, 50, 50, 50);
        //drawFilledCircle(renderer, X+e_size_w/2, Y+e_size_h/2, (e_size_w>e_size_h?e_size_h/2:e_size_w/2));

        // Actualizacion del "lienzo"
        SDL_RenderPresent(renderer);
        k++;
        //SDL_UpdateWindowSurface(window);

        //Titulo/caption de la ventana
        SDL_SetWindowTitle(window, "SDL_Image con texturas funciona bien? No lo probe!");
        SDL_Delay(delay);

        //Procesamiento de matriz?
    }

    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


