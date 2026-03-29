#include "Application.hpp"

void Shockwave::InitWindow(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Initial Error:" << SDL_GetError() << std::endl;
    }
    doc.load_file("app.xml");
    Application = doc.child("Application");
    int w,h;
    if(Application.attribute("width")){
        w = Application.attribute("width").as_int();
    } else {
        w = 550;
        std::cout << "Failed to find/load attribute:width" << std::endl;
    }

    if(Application.attribute("height")){
        h = Application.attribute("height").as_int();
    } else {
        h = 400;
        std::cout << "Failed to find/load attribute:height" << std::endl;
    }
    window = SDL_CreateWindow("Shockwave Player",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_OPENGL);
    if(!window){
        std::cout << "Window Error:" << SDL_GetError() << std::endl;
    }
    gl = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);
    std::string bg = Application.attribute("Background").as_string();  
    if(bg == "White"){
        glClearColor(255,255,255,1);
    }else if(bg == "Red"){
        glClearColor(255,0,0,1);
    }else if(bg == "Blue"){
        glClearColor(0,0,255,1);
    }else if(bg == "Green"){
        glClearColor(0,255,0,1);
    }else{
        glClearColor(255,255,255,1);
        std::cout << "Color Not Found:" << bg << std::endl;
    }
}

void Shockwave::Events(){
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            isRunning = false;
        }
    }
}
void Shockwave::Display(){
    Events();
    glClear(GL_COLOR_BUFFER_BIT);

    adl.Initize(Application);
    
    SDL_Delay(32);
    SDL_GL_SwapWindow(window);
}
void Shockwave::Reshape() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 2D projection: left, right, bottom, top
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Shockwave::Quit(){
    SDL_GL_DeleteContext(gl);
    SDL_DestroyWindow(window);
}
void Shockwave::Start(){
    InitWindow();
    Reshape();
    while(isRunning){
        Shockwave::Display();
    }
    Quit();
}