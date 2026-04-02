#include <cstdio>
#include <cstdlib>
#include "ADL.hpp"
#include <SDL2/SDL.h>

class Shockwave{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event e;
        bool isRunning = true;
        int Init(uint w,uint h);
        void Events();
        void Display();
        void Quit();
        #ifdef __EMSCRIPTEN__
            void Loop(); 
        #endif
    public:
        Shockwave(uint w,uint h);
};