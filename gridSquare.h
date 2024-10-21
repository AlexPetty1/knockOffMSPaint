#ifndef GRID_SQUARE_H
#define GRID_SQUARE_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class GridSquare{
    RectangleShape shape;
    float size;

    public:
        void printInfo();

        Color getColor();

        void drawSquare(RenderWindow* window);

        void setColor(Color newColor);

        GridSquare(int x, int y, int size);

        GridSquare();
};

#endif