
#include <SFML/Graphics.hpp>
#include "colorSelector.h"
#include "brushSizeSelector.h"
using namespace sf;

struct Selector{
    bool held;
    bool brushing;
    int brushWidth;
    Color selectedColor;
    ColorSelector* currentColorSelector;                //current color selector activated
    BrushSizeSelector* currentBrushSelector;
    int mode;           // 0: brush
                        // 1: flood
                        // 2: select
                        // 3: pointer

    int tilePaintedX;   //stores x of tile your painting, -1 painting nothing
    int tilePaintedY;   //prevents multiple updates if holding down
};