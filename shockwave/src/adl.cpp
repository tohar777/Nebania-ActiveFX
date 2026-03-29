#include "adl.hpp"
void ADLHandler::Graphics(pugi::xml_node Application)
{
    printf("h");
    /*Primitives*/
    pugi::xml_node quad = Application.child("Quads");
    pugi::xml_node triangle = Application.child("Triangles");
    pugi::xml_node polygon = Application.child("Polygons");
    /*Vertices*/
    pugi::xml_node v2 = Application.child("Vertex2");
    pugi::xml_node v3 = Application.child("Vertex3");
    /*Logic*/
    if (quad)
    {
        std::string Color = quad.attribute("Color").as_string();
        if (Color == "White")
        {
            glColor3f(255, 255, 255);
        }
        else if (Color == "Red")
        {
            glColor3f(255, 0, 0);
        }
        else if (Color == "Blue")
        {
            glColor3f(0, 0, 255);
        }
        else if (Color == "Green")
        {
            glColor3f(0, 255, 0);
        }
        else
        {
            glColor3f(255, 255, 255);
            std::cout << "Color Not Found:" << Color << std::endl;
        }
        glBegin(GL_QUADS);
        {

            glVertex2f(quad.attribute("startx").as_float(), quad.attribute("starty").as_float());
            glVertex2f(quad.attribute("endx").as_float(), quad.attribute("starty").as_float());
            glVertex2f(quad.attribute("endx").as_float(), quad.attribute("endy").as_float());
            glVertex2f(quad.attribute("startx").as_float(), quad.attribute("endy").as_float());
        }
        glEnd();
    }
}

void ADLHandler::Initize(pugi::xml_node Application)
{
    Graphics(Application);
    // IO();
    // Scripting(false);
    // Sound();
}