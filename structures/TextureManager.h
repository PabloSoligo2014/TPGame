#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector.h"

#define CAPACIDAD 50

typedef struct{                 // 74 bytes
    SDL_Texture* m_textureMap;  // 8 bytes
    int x;                      // 4 bytes
    int y;                      // 4 bytes
    int ancho;                  // 4 bytes
    int alto;                   // 4 bytes
    char id[CAPACIDAD];         // 50 bytes
}t_map;

Vector VecTex;

int Texture_Create();

void Texture_delete();

bool TextureManager_load(const char* fileName, const char* id, SDL_Renderer* pRenderer, int x, int y, int ancho, int alto); // Funcion para cargar una imagen o el primer frame de una en caso de ser animacion

void TextureManager_draw(const char* id, int xpos, int ypos, SDL_Renderer* pRenderer, SDL_RendererFlip flip); //Funcion para mostar una imagen estatica

void TextureManager_drawFrame(const char* id , int xpos, int ypos, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip); // Funcion para animar una imagen

int compararIdTex(const void* a,const void* b); // Funcion de comparacion entre un INT y una ID de t_map

int compararTex(const void* a, const void* b); // Funcion de comparacion entre dos ID de t_map

#endif // TEXTUREMANAGER_H_INCLUDED
