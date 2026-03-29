#include <string>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pugixml.hpp>
class ADLHandler{
public:
    void Graphics(pugi::xml_node Application);
    void Sound(pugi::xml_node Application);
    void IO(pugi::xml_node Application);
    bool Scripting(pugi::xml_node Application,bool toggle);
    void Initize(pugi::xml_node Application);
};