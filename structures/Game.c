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

    int result = Vector_create(&game->objVec, 5);
    if(!result) {
        return NULL;
    }

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

    void* result = getInstance();
    if(result==NULL){
        return;
    }

    // Se cargan las texturas
    TextureManager_load("assets/1945.png", "Subamarino", game->renderer, 367, 103, 33, 98);
    TextureManager_load("assets/1945.png", "Kaboom", game->renderer, 70, 169, 33, 32);
    TextureManager_load("assets/1945.png", "Nave Acercamiento", game->renderer, 300, 4, 99, 98);
    TextureManager_load("assets/animate-alpha.png", "Puma", game->renderer, 0, 0, 128, 82);
    TextureManager_load("assets/aviones.png", "4", game->renderer, 0, 110, 110, 110);
    TextureManager_load("assets/aircrafts.png", "Avion_8", game->renderer, 194, 619, 94, 76);
    TextureManager_load("assets/aircrafts.png", "Avion_10", game->renderer, 322, 618, 94, 76);

    // Se crean objetos
    Enemy go1;
    Player pl1;

    Vector_insertInOrderNoRepeat(&(game->objVec), Enemy_create(&go1, "Avion_8", "Enemigo1",100, 100), sizeof(GameObject), compararObjectID);
    Vector_insertInOrderNoRepeat(&(game->objVec), Enemy_create(&go1, "Avion_10", "Enemigo2",200, 200), sizeof(GameObject), compararObjectID);
    Vector_insertInOrderNoRepeat(&(game->objVec), Enemy_create(&go1, "Avion_8", "Enemigo3",500, 450), sizeof(GameObject), compararObjectID);
    Vector_insertInOrderNoRepeat(&(game->objVec), Enemy_create(&go1, "Avion_10", "Enemigo4",450, 300), sizeof(GameObject), compararObjectID);
    Vector_insertInOrderNoRepeat(&(game->objVec), Player_create(&pl1, "Puma", "Player", 200, 250), sizeof(Player), compararObjectID);
}

void Game_update(Game *game){
    // Logica del juego
    int i;
    GameObject* o;

    size_t cant = Vector_count(&(game->objVec));
    for(i=0;i<cant;i++){
        o = Vector_getRefByPos(&(game->objVec), i);
        update(o);
    }
}

void Game_render(Game* game){
    // Dibujado a pantalla
    int i;
    GameObject* o;
    SDL_RenderClear(game->renderer); // clear the renderer to the draw color
    SDL_RenderCopyEx(game->renderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_NONE); // pass in the horizontal flip

    size_t cant = Vector_count(&(game->objVec));
    for(i=0;i<cant;i++){
        o = Vector_getRefByPos(&(game->objVec), i);
        draw(o, game->renderer);
    }
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

    // Eliminar objetos primero con destroy
    // TODO: Implementar destroy de objetos
    Vector_destroy(&game->objVec);
    free(game);
}

bool Game_isRunning(Game* game){
    return game->isRunning;
}
