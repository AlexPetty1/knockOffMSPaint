#ifndef GRID_H
#define GRID_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "GridSquare.h"
#include "undoSystem.h"
#include "gridSelector.h"

#include <set>

using namespace sf;

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

        void selectOnGrid(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem);
        void brushOnGrid(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem);
        
        void drawDiamond(int xIndex, int yIndex, int radius, GridSelector* selector, UndoSystem* undoSystem);
        void drawCircle(int centerX, int centerY, int radius, GridSelector* selector, UndoSystem* undoSystem);

        void drawSquare(int xIndex, int yIndex, GridSelector* selector, UndoSystem* undoSystem);
        void drawSquareColor(int xIndex, int yIndex, Color newColor, UndoSystem* undoSystem);
        Color getColor(int xIndex, int yIndex);

        void selectDrawLine(RenderWindow* window, GridSelector* selector, UndoSystem* UndoSystem);
        void drawLine(int xStart, int yStart, int xEnd, int yEnd, 
            GridSelector* selector, UndoSystem* UndoSystem);

        void flood(int xIndex, int yIndex, Color oldColor, 
            Color newColor, UndoSystem* UndoSystem);
        
        void releaseTheFlood(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem);

        int getMouseOnXTile(RenderWindow* window);
        int getMouseOnYTile(RenderWindow* window);

        int getMouseOnXTileNoCheck(RenderWindow* window);
        int getMouseOnYTileNoCheck(RenderWindow* window);

        void display(RenderWindow* window);
};


#endif