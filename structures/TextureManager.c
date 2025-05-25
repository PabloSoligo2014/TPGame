#include "TextureManager.h"

// Funcion para cargar una imagen o el primer frame de una en caso de ser animacion
bool TextureManager_load(Vector *v, const char* fileName, int id, SDL_Renderer* pRenderer){
    SDL_Surface* pTempSurface = IMG_Load(fileName);

    if(pTempSurface == 0){
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    // everything went ok, add the texture to our list

    if(pTexture != 0){
        t_map tex;
        tex.m_textureMap = pTexture;
        tex.id = id;

        if(!Vector_insertInOrder(v, &tex, sizeof(t_map), compararTex)){
            return false;
        }

        return true;
    }

    // reaching here means something went wrong
    return false;
}

//Funcion para mostrar una imagen estatica
void TextureManager_draw(Vector *v, int id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip){ //Funcion para cargar una imagen estatica
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    void* nodo = (void*)Vector_bsearch(v, &id, compararIdTex);
    t_map textura = *(t_map*)(nodo);

    SDL_Texture* tex = textura.m_textureMap;

    SDL_RenderCopyEx(pRenderer, tex, &srcRect, &destRect, 0, 0, flip);
}

// Funcion para animar una imagen
void TextureManager_drawFrame(Vector *v, int id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip){
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    void* nodo = (void*)Vector_bsearch(v, &id, compararIdTex);
    t_map textura = *(t_map*)(nodo);

    SDL_Texture* tex = textura.m_textureMap;

    SDL_RenderCopyEx(pRenderer, tex, &srcRect, &destRect, 0, 0, flip);
}

// Funcion de comparacion entre un INT y una ID de t_map
int compararIdTex(const void*a,const void*b){//si a < b retorna 1
    int elem = *(int*)a;
    t_map b1 = *(t_map*)(b);

    return (elem - b1.id);
}

// Funcion de comparacion entre dos ID de t_map
int compararTex (const void* a, const void* b){
    t_map a1 = *(t_map*)(a);
    t_map b1 = *(t_map*)(b);

    return (a1.id - b1.id);
}
