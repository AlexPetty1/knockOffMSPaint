#ifndef GRID_SELECTOR_H
#define GRID_SELECTOR_H

#include <SFML/Graphics.hpp>
using namespace sf;

struct GridSelector{
    bool held;
    bool effectingGrid;
    int brushWidth;
    Color selectedColor;
    int mode;           // 0: brush
                        // 1: flood
                        // 2: pointer
                        // 3: line

    int tilePaintedX;   //stores x of tile your painting, -1 painting nothing
    int tilePaintedY;   //prevents multiple updates if holding down

    int lineCord1[2]; 
};

#endif