/*
ADL - Active Declarative Language
ADL will be serve as a base to all ActiveFX Shockwave Applications.
ADL is a XML dialect used for AFX Shockwave Application, it gives the programmer an easier
option to develop apps quick with ADL's provided tookit instead of LinkScript AFX API
*/
#include <cstdio>
#include <string.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<pugixml.hpp>
#include "entry.h"
class ADL{
public:
    SDL_Renderer* renderer;
    pugi::xml_document doc;
    pugi::xml_node Application;
    Runtime runtime;
    ADL(char* file ,SDL_Renderer* renderer); // Initaize ADL
    void Graphics(); //High-Level Graphics API
    void Audio(); //Audio API
    void Scripting(); //Scripting using LinkScript or 
    void Modules(); //Importing user made ADL Components
};