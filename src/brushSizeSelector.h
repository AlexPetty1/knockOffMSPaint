#ifndef BrushSizeSelector_H
#define BrushSizeSelector_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

//forward declaration
struct Selector;

class BrushSizeSelector{
    
    private:
        const Color unSelectColor = Color(180, 180, 180, 255);
        const Color selectColor = Color(30, 30, 30, 255);
        int x;
        int y;
        int shapeSize;
        int borderSize;
        int brushSize;
        RectangleShape shape;
        RectangleShape innerShape;
        Text brushText;
        Font fonts;
    
    public:
        BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize);

        void isClicked(RenderWindow* window, Selector* selector);

        void select(Selector* selector);

        void unselect();

        void display(RenderWindow* window);
};

#endif