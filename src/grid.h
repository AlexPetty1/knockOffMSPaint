#ifndef GRID_H
#define GRID_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ColorSelector.h"
#include "BrushSizeSelector.h"
#include "GridSquare.h"
#include "undoSystem.h"

#include <set>

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


class Grid{


    private:
        int gridXDim;
        int gridYDim;
        int squareSize;
        int gridX;
        int gridY;
        std::vector<std::vector<GridSquare>> squareGrid;

    public:
        Grid(int gridXDim, int gridYDim, int squareSize, int gridOffsetX, int gridOffsetY);

        //automatically adds a bunch of squares to the grid
        //used for undo
        void autoAdd(std::vector<GridSquareSave> squares);

        void selectOnGrid(RenderWindow* window, Selector* selector, UndoSystem* undoSystem);

        //changes the color of a specific square
        void drawSquare(int xIndex, int yIndex, Selector* selector, UndoSystem* undoSystem);
        void drawSquareColor(int xIndex, int yIndex, Color newColor, UndoSystem* undoSystem);
        Color getColor(int xIndex, int yIndex);

        void drawLine(int xStart, int yStart, int xEnd, int yEnd, 
            Selector* selector, UndoSystem* UndoSystem);

        void flood(int xIndex, int yIndex, Color oldColor, 
            Color newColor, UndoSystem* UndoSystem);
        
        void releaseTheFlood(RenderWindow* window, Selector* selector, UndoSystem* undoSystem);

        int getMouseOnXTile(RenderWindow* window);
        int getMouseOnYTile(RenderWindow* window);

        int getMouseOnXTileNoCheck(RenderWindow* window);
        int getMouseOnYTileNoCheck(RenderWindow* window);

        void display(RenderWindow* window);
};


#endif