#include "InputHandler.h"
const Uint8* keystate;


bool InputHandler_isKeyDown(SDL_Scancode key) {
    keystate = SDL_GetKeyboardState(0);

    if(keystate != 0) {
        if(keystate[key] == 1) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}
