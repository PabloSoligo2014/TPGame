#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector.h"

#define CAPACIDAD 256

typedef struct{
    SDL_Texture* m_textureMap;
    int id;
}t_map;

bool TextureManager_load(Vector* v, const char* fileName, int id, SDL_Renderer* pRenderer); // Funcion para cargar una imagen o el primer frame de una en caso de ser animacion

void TextureManager_draw(Vector* v, int id, int xpos, int ypos, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip); //Funcion para mostar una imagen estatica

void TextureManager_drawFrame(Vector* v, int id , int xpos, int ypos, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip); // Funcion para animar una imagen

int compararIdTex(const void* a,const void* b); // Funcion de comparacion entre un INT y una ID de t_map

int compararTex (const void* a, const void* b); // Funcion de comparacion entre dos ID de t_map

#endif // TEXTUREMANAGER_H_INCLUDED
