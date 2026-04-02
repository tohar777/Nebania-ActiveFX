#include "Shockwave.hpp"


Shockwave::Shockwave(uint w,uint h){
    Init(w,h);\
    ADL adl("app.xml",renderer);
    adl.Scripting();
    while(isRunning){
        Events();
        Display();
        adl.Graphics();
        SDL_Delay(32);
        SDL_RenderPresent(renderer);
    }
    Quit();
}
int Shockwave::Init(uint w,uint h){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Failed to initiaze SDL2");
        #ifdef __EMSCRIPTEN__
           //pass 
        #else
            return -1;
        #endif
    }
    window = SDL_CreateWindow("Nebania Shockwave Player 1"
        ,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED
        ,w,h
        ,0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    renderer = SDL_CreateRenderer(window,-1,0);
    return 0;
}
void Shockwave::Events(){
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            isRunning = false;
        }
    }
}
void Shockwave::Display(){
    SDL_SetRenderDrawColor(renderer,100, 149, 237,255);
    SDL_RenderClear(renderer);

}
void Shockwave::Quit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}