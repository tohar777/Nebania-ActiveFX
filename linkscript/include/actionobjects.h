#ifndef ACTIONOBJECTS_DOM
#define ACTIONOBJECTS_DOM

#include <string>
#include <cstring>
#include <stdio.h>
#include <emscripten.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
//======================
//  DOM Manipolation
//======================

namespace ActionObjects
{   
    EM_JS(void, js_create_button, (const char* text, const char* id, const char* onclick), {
        const btn = document.createElement("button");

        btn.innerText = UTF8ToString(text);
        btn.id = UTF8ToString(id);

        // Optional click handler (string-based for now)
        const handler = UTF8ToString(onclick);
        if (handler.length > 0) {
            btn.onclick = function() {
                console.log("[AFX CLICK]", handler);
            };
        }

        document.body.appendChild(btn);
    });
    EM_JS(void,js_gotoURL,(const char* url),{
        window.open(url, "_blank");
    }); 
    
        
    namespace graphics {
        SDL_Window* window = nullptr;
        SDL_GLContext glContext;
        bool running = true;

        void init(int w, int h) {
            SDL_Init(SDL_INIT_VIDEO);

            window = SDL_CreateWindow("AFX",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                w, h,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

            glContext = SDL_GL_CreateContext(window);
            SDL_GL_SetSwapInterval(1); // vsync

            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            //glOrtho(0, w, h, 0, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        bool isRunning() {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) running = false;
            }
            return running;
        }

        void clear() {
            glClearColor(0,0,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
        }

        void present() {
            SDL_GL_SwapWindow(window);
        }

        namespace draw {
            void drawRect(float x, float y, float w, float h, float r, float g, float b) {
                glColor3f(r, g, b);
                glBegin(GL_LINE_LOOP);
                    glVertex2f(x, y);
                    glVertex2f(x+w, y);
                    glVertex2f(x+w, y+h);
                    glVertex2f(x, y+h);
                glEnd();
            }
        }

    }
} // namespace ActionObjects

#endif