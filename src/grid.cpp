
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>

#include "grid.h"
#include "undoSystem.h"
#include "gridSelector.h"

using namespace sf;

Grid::Grid(int gridXDim, int gridYDim, int squareSize, int gridOffsetX, int gridOffsetY){

    std::vector<std::vector<GridSquare>> tGrid(gridYDim , std::vector<GridSquare> (gridXDim));
    this->squareGrid = tGrid;

    for(int i = 0; i < gridYDim; i++) { 
        for(int j = 0; j < gridXDim; j++) { 
            int x = gridOffsetX + squareSize * i;
            int y = gridOffsetY + squareSize * j;

            this->squareGrid[i][j] = GridSquare(x, y, squareSize); 
        } 
    } 

    this->gridXDim = gridXDim;
    this->gridYDim = gridYDim;
    this->squareSize = squareSize;
    this->gridX = gridOffsetX;
    this->gridY = gridOffsetY;
}

// Name: autoAdd
// Description: automatically colors squares on the grid from an array
//          error checks to make sure squares are on grid
// Arguments: squares - vector of grid squares
// Sideffects: changes gridsquares
void Grid::autoAdd(std::vector<GridSquareSave> squares){
    
    for(int i = 0; i < squares.size(); i++){
        int x = squares[i].x;
        int y = squares[i].y;
        Color color = squares[i].color;


        if(x < 0 || this->gridXDim <= x){
            return;
        }

        if(y < 0 || this->gridYDim <= y){
            return;
        }

        this->squareGrid[x][y].setColor(color);
    }
}

// Name: selectOnGrid
// Description: runs when you click on a grid
//      error checks to make sure cursor is on grid
// Arguments: window - window the grid is on
//             selector - selector 
//             undoSystem - 
// Sideffects: 
void Grid::selectOnGrid(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;
    
    int squareX = (mouseX - this->gridX) / this->squareSize;
    int squareY = (mouseY - this->gridY) / this->squareSize;
    
    //makes sure tile is in bounds
    if(squareX < 0 || this->gridXDim <= squareX){
        return;
    }

    if(squareY < 0 || this->gridYDim <= squareY){
        return;
    }
    
    //prevents multiple updates on hold
    if(squareX == selector->tilePaintedX && squareY == selector->tilePaintedY){
        return;
    }

    switch(selector->mode){
        case 0:
            brushOnGrid(window, selector, undoSystem);
            break;
        case 1: 
            releaseTheFlood(window, selector, undoSystem);
            break;
        case 3:
            selectDrawLine(window, selector, undoSystem);
            break;
    }
}


void Grid::selectDrawLine(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem){
    int xTile = this->getMouseOnXTile(window);
    int yTile = this->getMouseOnYTile(window);

    //makes sure valid tile
    if(xTile <= 0 || this->gridXDim <= xTile){
        return;
    }

    if(yTile <= 0 || this->gridYDim <= yTile){
        return;
    }

    selector->effectingGrid = true;

    if(selector->lineCord1[0] == -1 || selector->lineCord1[1] == -1){
        selector->lineCord1[0] = xTile;
        selector->lineCord1[1] = yTile;
        return;
    }


    drawLine(selector->lineCord1[0], selector->lineCord1[1], 
        xTile, yTile, selector, undoSystem);
    
    selector->lineCord1[0] = xTile;
    selector->lineCord1[1] = yTile;

}


// runs when clicking on the grid
void Grid::brushOnGrid(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;
    
    int squareX = (mouseX - this->gridX) / this->squareSize;
    int squareY = (mouseY - this->gridY) / this->squareSize;
    
    //makes sure tile is in bounds
    if(squareX < 0 || this->gridXDim <= squareX){
        return;
    }

    if(squareY < 0 || this->gridYDim <= squareY){
        return;
    }
    
    //prevents multiple updates on hold
    if(squareX == selector->tilePaintedX && squareY == selector->tilePaintedY){
        return;
    }

    selector->effectingGrid = true;

    selector->tilePaintedX = squareX;
    selector->tilePaintedY = squareY;
    
   drawDiamond(squareX, squareY, selector->brushWidth, selector, undoSystem);
}

// draws a diamond on the grid
//                          o
// creates                o o o
//                      o o o o o
//                        o o o
//                          o
//
void Grid::drawDiamond(int xIndex, int yIndex, int radius, GridSelector* selector, UndoSystem* undoSystem){
    if(radius < 1){
        return;
    }

    //makes center
    drawSquare(xIndex, yIndex, selector, undoSystem);
    //makes wings
    for(int i = 1; i < selector->brushWidth; i++){
        drawSquare(xIndex + i, yIndex, selector, undoSystem);
        drawSquare(xIndex - i, yIndex, selector, undoSystem);
        drawSquare(xIndex, yIndex + i, selector, undoSystem);
        drawSquare(xIndex, yIndex - i, selector, undoSystem);
    }
    //makes corners
    for(int i = 1; i < selector->brushWidth; i++){
        for(int j = 1; j < selector->brushWidth - i; j++){
            drawSquare(xIndex + j, yIndex + i, selector, undoSystem);
            drawSquare(xIndex + j, yIndex - i, selector, undoSystem);

            drawSquare(xIndex - j, yIndex + i, selector, undoSystem);
            drawSquare(xIndex - j, yIndex - i, selector, undoSystem);
        }
    }
}



void Grid::drawSquare(int xIndex, int yIndex, GridSelector* selector, UndoSystem* undoSystem){
    
    if(xIndex < 0 || this->gridXDim <= xIndex){
        return;
    }

    if(yIndex < 0 || this->gridYDim <= yIndex){
        return;
    }

    Color oldColor = this->squareGrid[xIndex][yIndex].getColor();
    this->squareGrid[xIndex][yIndex].setColor(selector->selectedColor);

    GridSquareSave* newSave = new GridSquareSave {xIndex, yIndex, oldColor};
    undoSystem->addToCurrentSave(newSave);
}

void Grid::drawSquareColor(int xIndex, int yIndex, Color newColor, UndoSystem* undoSystem){
    
    if(xIndex < 0 || this->gridXDim <= xIndex){
        return;
    }

    if(yIndex < 0 || this->gridYDim <= yIndex){
        return;
    }

    Color oldColor = this->squareGrid[xIndex][yIndex].getColor();
    this->squareGrid[xIndex][yIndex].setColor(newColor);

    GridSquareSave* newSave = new GridSquareSave {xIndex, yIndex, oldColor};
    undoSystem->addToCurrentSave(newSave);
}

Color Grid::getColor(int xIndex, int yIndex){
    return this->squareGrid[xIndex][yIndex].getColor();
}

void Grid::releaseTheFlood(RenderWindow* window, GridSelector* selector, UndoSystem* undoSystem){
    int xTile = this->getMouseOnXTile(window);
    int yTile = this->getMouseOnYTile(window);

    //makes sure valid tile
    if(xTile <= 0 || this->gridXDim <= xTile){
        return;
    }

    if(yTile <= 0 || this->gridYDim <= yTile){
        return;
    }

    selector->effectingGrid = true;

    Color newColor = selector->selectedColor;
    Color oldColor = this->getColor(xTile, yTile);

    this->flood(xTile, yTile, oldColor, newColor, undoSystem);
}


void Grid::flood(int xIndex, int yIndex, 
    Color oldColor, Color newColor, UndoSystem* undoSystem){

    //makes sure valid tile
    if(xIndex <= 0 || this->gridXDim <= xIndex){
        return;
    }

    if(yIndex <= 0 || this->gridYDim <= yIndex){
        return;
    }

    //returns if not the same color
    Color squareColor = this->squareGrid[xIndex][yIndex].getColor();
    if(squareColor != oldColor){
        return;
    }

    //need if newColor is equal to old color
    if(squareColor == newColor){
        return;
    }


    drawSquareColor(xIndex, yIndex, newColor, undoSystem);

    flood(xIndex + 1, yIndex, oldColor, newColor, undoSystem);
    flood(xIndex - 1, yIndex, oldColor, newColor, undoSystem);
    flood(xIndex, yIndex + 1, oldColor, newColor, undoSystem);
    flood(xIndex, yIndex - 1, oldColor, newColor, undoSystem);
}

int Grid::getMouseOnXTile(RenderWindow* window){
    int mouseX = Mouse::getPosition(*window).x;
    int squareX = (mouseX - this->gridX) / this->squareSize;


    if(squareX < 0 || this->gridXDim <= squareX){
        return -1;
    }

    return squareX;
}

int Grid::getMouseOnYTile(RenderWindow* window){
    int mouseY = Mouse::getPosition(*window).y;
    int squareY = (mouseY - this->gridY) / this->squareSize;


    if(squareY < 0 || this->gridXDim <= squareY){
        return -1;
    }

    return squareY;
}

int Grid::getMouseOnXTileNoCheck(RenderWindow* window){
    int mouseX = Mouse::getPosition(*window).x;
    int squareX = (mouseX - this->gridX) / this->squareSize;
    return squareX;
}

int Grid::getMouseOnYTileNoCheck(RenderWindow* window){
    int mouseY = Mouse::getPosition(*window).y;
    int squareY = (mouseY - this->gridY) / this->squareSize;
    return squareY;
}

void Grid::drawLine(int xStart, int yStart, int xEnd, int yEnd, 
    GridSelector* selector, UndoSystem* UndoSystem){
    
    int thickness = selector->brushWidth;
    float slope = float(yEnd - yStart) / float(xEnd - xStart);
    int direction = 1;

    if(abs(slope) <  1){
        if((xEnd - xStart) < 0){
            direction = -1;
        }

        for(int i = 0; i <= abs(xEnd - xStart); i++){
            int x = i * direction + xStart;
            int y = round(i * slope * direction + yStart);
            this->drawSquare(x, y, selector, UndoSystem);

            //makes thickness
            for(int j = 1; j < thickness; j++){
                this->drawSquare(x, y + j, selector, UndoSystem);
                this->drawSquare(x, y - j, selector, UndoSystem);
            }
        }
    } else {
        if((yEnd - yStart) < 0){
            direction = -1;
        }

        float rotatedSlope = (1/slope); 

        for(int i = 0; i <= abs(yEnd - yStart); i++){
            int y = i * direction + yStart;
            int x = round(i * rotatedSlope * direction + xStart);

            this->drawSquare(x, y, selector, UndoSystem);

            //makes thickness
            for(int j = 1; j < thickness; j++){
                this->drawSquare(x + j, y, selector, UndoSystem);
                this->drawSquare(x - j, y, selector, UndoSystem);
            }
        }
    }
}

void Grid::display(RenderWindow* window){
    for(int i = 0; i < this->gridYDim; i++){
        for(int j = 0; j < this->gridXDim; j++){
            this->squareGrid[i][j].drawSquare(window);
            
        }
    }
}