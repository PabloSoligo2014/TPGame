#include <stdlib.h>

#include <stdio.h> //there is a put call...will disappear, but now it is
#include "Game.h"

SDL_Texture* m_pTexture; // the new SDL_Texture variable
SDL_Rect m_sourceRectangle; // the first rectangle
SDL_Rect m_destinationRectangle; // another rectangle

int m_currentFrame;

//This function will disappear, just for test
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}


Game* Game_create(){
    Game* game = (Game*)malloc(sizeof(Game));
    game->window = NULL;
    game->renderer = NULL;
    game->isRunning = false;
    return game;
}

void Game_init(Vector* v, Game* game, const char* title, int x, int y, int w, int h, int flags, int delay){
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

    TextureManager_load(v, "assets/1945.png", "Subamarino", game->renderer, 367, 103, 33, 98);
    TextureManager_load(v, "assets/1945.png", "Kaboom", game->renderer, 70, 169, 33, 32);
    TextureManager_load(v, "assets/1945.png", "Nave Acercamiento", game->renderer, 300, 4, 99, 98);
    TextureManager_load(v, "assets/animate-alpha.png", "Puma", game->renderer, 0, 0, 128, 82);
    TextureManager_load(v, "assets/aviones.png", "4", game->renderer, 0, 110, 110, 110);
}


void Game_update(Game *game){
    /*
    Generar la logica del juego
    */
    m_currentFrame = (int)(((SDL_GetTicks() / 100) % 6)); //El 6 me limita a que las animaciones tengan 6 frames
}

void Game_render(Vector* v, Game* game){
    //Imagenes

    SDL_RenderClear(game->renderer); // clear the renderer to the draw color

    SDL_RenderCopyEx(game->renderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_NONE); // pass in the horizontal flip

    TextureManager_draw(v, "Subamarino", 0, 0, game->renderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(v, "Subamarino", 0, 100, 1, m_currentFrame, game->renderer, SDL_FLIP_NONE);

    TextureManager_draw(v, "Nave Acercamiento", 150, 0, game->renderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(v, "Nave Acercamiento", 150, 100, 1, m_currentFrame, game->renderer, SDL_FLIP_NONE);

    TextureManager_draw(v, "Puma", 300, 0, game->renderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(v, "Puma", 300, 100, 1, m_currentFrame, game->renderer, SDL_FLIP_NONE);

    TextureManager_draw(v, "4", 450, 0, game->renderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(v, "4", 450, 100, 1, m_currentFrame, game->renderer, SDL_FLIP_NONE);

    TextureManager_draw(v, "Kaboom", 600, 0, game->renderer, SDL_FLIP_NONE);
    TextureManager_drawFrame(v, "Kaboom", 600, 100, 1, m_currentFrame, game->renderer, SDL_FLIP_NONE);

    SDL_RenderPresent(game->renderer); // draw to the screen
}

void Game_handleEvents(Game* game){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
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
