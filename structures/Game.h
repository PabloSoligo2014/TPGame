#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<stdbool.h>
#include "Entities.h"
#include "Vector.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int delay;
    bool isRunning;
} Game;

Game* Game_create();
void Game_init(Game* game, const char* title, int x, int y, int w, int h, int flags, int delay);
void Game_handleEvents(Game* game);
void Game_update(Game* game);
void Game_render(Game* game);
void Game_clean(Game* game);
bool Game_isRunning(Game* game);

#endif // GAME_H_INCLUDED
