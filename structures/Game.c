#include <stdlib.h>
#include "Game.h"

Game* Game_create(){
    Game* game = (Game*)malloc(sizeof(Game));
    game->window = NULL;
    game->renderer = NULL;
    game->isRunning = false;
    return game;
}

void Game_init(Game* game, const char* title, int x, int y, int w, int h, int flags, int delay){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Error al inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    game->window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!game->window) {
        SDL_Log("No se pudo crear la ventana: %s\n", SDL_GetError());
        return;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        SDL_Log("No se pudo crear el renderer: %s\n", SDL_GetError());
        Game_clean(game);
        return;
    }
    SDL_SetWindowTitle(game->window, title);
    game->delay = delay;
    game->isRunning = true;
}


void Game_update(Game *game){
    /*
    Generar la logica del juego
    */
}

void Game_render(Game* game){
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    SDL_Rect rect1 = {150, 150, 30, 30};
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(game->renderer, &rect1);

    SDL_Rect rect2 = {100, 100, 30, 30};
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(game->renderer, &rect2);

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    drawFilledCircle(game->renderer, 50, 50, 50);

    SDL_RenderPresent(game->renderer);

    SDL_Delay(game->delay);
}

void Game_handleEvents(Game* game){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->isRunning = false;
            puts("ENTER para salir");
        }
    }

    /*
    Manejar i/o del usuario
    */
}

void Game_clean(Game* game){
    if (game->renderer) SDL_DestroyRenderer(game->renderer);
    if (game->window) SDL_DestroyWindow(game->window);
    SDL_Quit();
    free(game);
}

bool Game_isRunning(Game* game){
    return game->isRunning;
}
