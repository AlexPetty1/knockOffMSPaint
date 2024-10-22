#ifndef BrushSizeSelector_H
#define BrushSizeSelector_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

//forward declaration
struct Selector;

class BrushSizeSelector{
    int x;
    int y;
    int shapeSize;
    int borderSize;
    int brushSize;
    Text text;
    RectangleShape shape;

    private:
        const Color unSelectColor = Color(150, 150, 150, 255);
        const Color selectColor = Color(40, 40, 40, 255);
        Font fonts;
    
    public:
        BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize);

        void isClicked(RenderWindow* window, Selector* selector);

        void select(Selector* selector);

        void unselect();

        void display(RenderWindow* window);
};

#endif