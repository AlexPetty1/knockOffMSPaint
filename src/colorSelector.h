#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H 

#include <SFML/Graphics.hpp>

#include "colorSelector.h"

using namespace sf;

//forward declaration
struct Selector;

class ColorSelector{
    int x;
    int y;
    int size;
    int borderSize;
    Color color;
    RectangleShape shape;

    private:
        const Color unSelectColor = Color(150, 150, 150, 255);
        const Color selectColor = Color(40, 40, 40, 255);
    
    public:
        ColorSelector(int x, int y, int size, int borderSize, Color color);

        void isClicked(RenderWindow* window, Selector* selector);

        void unSelect();

        void display(RenderWindow* window);
};

#endif