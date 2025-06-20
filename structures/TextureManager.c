#include "TextureManager.h"

static TextureSingleton* instance = NULL;

TextureSingleton* getInstance(){

    if (instance == NULL) {

        instance = (TextureSingleton*)malloc(sizeof(TextureSingleton));

        if (instance != NULL) {

            int result = Vector_create(&(instance->Vectex), 5); // Inicialización de ejemplo
            if(!result){
                return NULL;
            }
        }

    }

    return instance;

}

void Texture_delete(){
    if (instance != NULL){
        free(instance);
        instance = NULL;
    }
}

// Funcion para cargar una imagen o el primer frame de una en caso de ser animacion
bool TextureManager_load(const char* fileName, const char* id, SDL_Renderer* pRenderer, int x, int y, int ancho, int alto){
    SDL_Surface* pTempSurface = IMG_Load(fileName);

    if(pTempSurface == 0){
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    // everything went ok, add the texture to our list

    if(pTexture != 0){
        t_map tex;
        tex.m_textureMap = pTexture;        // Imagen
        strncpy(tex.id, id, CAPACIDAD - 1); // id de la imagen
        tex.id[CAPACIDAD - 1] = '\0';
        tex.x = x;                          // Pos horizontal de que parte de la imagen tomamos
        tex.y = y;                          // Pos vertical de que parte de la imagen tomamos
        tex.alto = alto;                    // Que tan alta es la imagen (pixeles)
        tex.ancho = ancho;                  // Que tan ancha es la imagen (pixeles)

        if(!Vector_insertInOrderNoRepeat(&getInstance()->Vectex, &tex, sizeof(t_map), compararTex)){
            return false;
        }

        return true;
    }

    // reaching here means something went wrong
    return false;
}

//Funcion para mostrar una imagen estatica
void TextureManager_draw(const char* id, int x, int y, SDL_Renderer* pRenderer, SDL_RendererFlip flip){ //Funcion para cargar una imagen estatica

    SDL_Rect srcRect;
    SDL_Rect destRect;

    void* nodo = Vector_bsearch(&getInstance()->Vectex, (void*)id, compararIdTex);

    if(nodo == NULL){
        printf("Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    t_map textura = *(t_map*)(nodo);

    SDL_Texture* tex = textura.m_textureMap;

    srcRect.x = textura.x;                  //Pos horizontal dentro de  la imagen
    srcRect.y = textura.y;                  //Pos vertical dentro de  la imagen

    srcRect.w = destRect.w = textura.ancho; //Cant de pixeles de ancho que tomamos de la imagen
    srcRect.h = destRect.h = textura.alto;  //Cant de pixeles de alto que tomamos de la imagen
    destRect.x = x;                         //Pos horizontal en la pantalla
    destRect.y = y;                         //Pos vertical en la pantalla

    SDL_RenderCopyEx(pRenderer, tex, &srcRect, &destRect, 0, 0, flip);
}

// Funcion para animar una imagen
void TextureManager_drawFrame(const char* id, int x, int y, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip){

    SDL_Rect srcRect;
    SDL_Rect destRect;

    void* nodo = Vector_bsearch(&getInstance()->Vectex, (void*)id, compararIdTex);

    if(nodo == NULL){
        printf("Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    t_map textura = *(t_map*)(nodo);

    srcRect.x = textura.ancho * currentFrame + textura.x;       //Pos horizontal dentro de la imagen
    srcRect.y = textura.alto * (currentRow - 1) + textura.y;    //Pos vertical dentro de la imagen

    srcRect.w = destRect.w = textura.ancho;                     //Cant de pixeles de ancho que tomamos de la imagen
    srcRect.h = destRect.h = textura.alto;                      //Cant de pixeles de alto que tomamos de la imagen
    destRect.x = x;                                             //Pos horizontal en la pantalla
    destRect.y = y;                                             //Pos vertical en la pantalla

    SDL_Texture* tex = textura.m_textureMap;

    SDL_RenderCopyEx(pRenderer, tex, &srcRect, &destRect, 0, 0, flip);
}

// Funcion de comparacion entre un INT y una ID de t_map
int compararIdTex(const void* a, const void* b){//si a < b retorna 1
    char* elem = (char*)a;
    t_map* tex = (t_map*)b;

    return strcmp(elem, tex->id);
}

// Funcion de comparacion entre dos ID de t_map
int compararTex (const void* a, const void* b){
    t_map* a1 = (t_map*)(a);
    t_map* b1 = (t_map*)(b);

    return strcmp(a1->id, b1->id);
}
