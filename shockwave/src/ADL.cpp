#include "ADL.hpp"
#include "helpers/storage.h"
ADL::ADL(char* file,SDL_Renderer* renderer){
    this->renderer = renderer;
    doc.load_file(file);
    Application = doc.child("Application");
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}
void ADL::Graphics(){

    /* Rect */
    {
        pugi::xml_node Rect = Application.child("Rect");

        int x = Rect.attribute("x").as_int();
        int y = Rect.attribute("y").as_int();
        int w = Rect.attribute("width").as_int();
        int h = Rect.attribute("height").as_int();

        std::string colorString = Rect.attribute("color").as_string();

        int r = 0, g = 0, b = 0, a = 255;

        if (colorString == "RED") {
            r = 255;
        }

        SDL_Rect rect = { x, y, w, h };

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderFillRect(renderer, &rect);
    }

    /* Textures */
    for (pugi::xml_node texture : Application.children("Texture")) {

        int x = texture.attribute("x").as_int();
        int y = texture.attribute("y").as_int();
        int w = texture.attribute("width").as_int();
        int h = texture.attribute("height").as_int();

        std::string fileTex = texture.attribute("path").as_string();
        std::string id = texture.attribute("id").as_string();

        if (id.empty()) {
            printf("Please specify object ID!\n");
            continue;
        }

        // create only once
        if (!objs.count(id)) {
            objs[id] = { float(x), float(y), w, h };
        }

        // texture cache
        SDL_Texture* tex = nullptr;

        if (!textureCache.count(fileTex)) {
            tex = IMG_LoadTexture(renderer, fileTex.c_str());
            if (!tex) {
                printf("Failed to load texture: %s\n", fileTex.c_str());
                continue;
            }
            textureCache[fileTex] = tex;
        } else {
            tex = textureCache[fileTex];
        }

        // auto size
        if (objs[id].w == 0 || objs[id].h == 0) {
            SDL_QueryTexture(tex, NULL, NULL, &objs[id].w, &objs[id].h);
        }

        SDL_Rect rect = {
            (int)objs[id].x,
            (int)objs[id].y,
            objs[id].w,
            objs[id].h
        };

        SDL_RenderCopy(renderer, tex, NULL, &rect);
    }
}
void ADL::Scripting(){
    pugi::xml_node macro = Application.child("macro");
    int h = macro.attribute("type").as_int();
    if(macro){
        run(runtime,macro.text().as_string(),false);
    }
}