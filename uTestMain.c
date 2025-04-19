#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "minunit.h"

int sumar(int a, int b){
    return a+b;
}

MU_TEST(test_muestra){
    int expResult = 10;
    char* errorMsg = "Error en la funcion de suma";
    mu_assert( expResult==sumar(5,5), errorMsg);

}

MU_TEST_SUITE(test_suite) {

    MU_RUN_TEST(test_muestra);
    //Mas test aca


}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;

}


