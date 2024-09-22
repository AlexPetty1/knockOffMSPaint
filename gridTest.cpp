#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <stdio.h> 
#include <stdlib.h>     
#include <time.h>
#include <math.h>

#include "gridTest.h"

using namespace sf;


//globals
Font fonts;


void GridSquare::printInfo(){
    std::cout << this->shape.getPosition().x << " " << this->shape.getPosition().y << " "
    << this->shape.getFillColor().b << " "<< this->shape.getScale().x <<"\n";
}

Color GridSquare::getColor(){
    return this->shape.getFillColor();
}

void GridSquare::drawSquare(RenderWindow* window){
    window->draw(this->shape);
    
}

void GridSquare::setColor(Color newColor){
    this->shape.setFillColor(newColor);
}

GridSquare::GridSquare(int x, int y, int size){

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(Vector2f(float(x), float(y)));
    this->size = size;

    this->shape.setFillColor(Color::White);
}

GridSquare::GridSquare(){

}


UndoSystem::UndoSystem(int amountOfSaves){
    this->currentSave = 0;
    this->backSave = 0;
    this->frontSave = 1;

    // std::vector<std::vector<GridSquare>> tSaves(amountOfSaves, std::vector<GridSquare> ());
    // this->saves = ;

    std::vector<std::vector<GridSquareSave>> tSaves;
    tSaves.resize(amountOfSaves);
    this->saves = tSaves;
    this->amountOfSaves = amountOfSaves;

};

void UndoSystem::printSystem(){

    int max = 5;
    for(int i = 0; i < this->saves.size(); i++){
        std::cout << "Save: " << i << " \n";
        for(int j = 0; j < this->saves[i].size(); j++){
            if(j == max){
                break;
            }

            GridSquareSave save = this->saves[i][j];
            std::cout << save.x << " " << save.y << " " << save.color.toInteger() << "\n";

        }
    }
}

void UndoSystem::commitSave(){
    currentSave = currentSave + 1;
    if(currentSave >= amountOfSaves){
        currentSave = 0;
    }


    frontSave = currentSave;

    if(frontSave == backSave){
        backSave = backSave + 1;

        if(backSave >= amountOfSaves){
            backSave = 0;
        }
    }

    this->saves[currentSave].clear();
    this->squaresInSave.clear();
    
};

void UndoSystem::undo(Grid* grid){

    if(this->backSave == this->currentSave){
        return;
    }
    
    this->currentSave = this->currentSave - 1;
    if(this->currentSave == -1){
        this->currentSave = this->amountOfSaves - 1;
    }

    grid->autoAdd(this->saves[this->currentSave]);
    this->squaresInSave.clear();
};

void UndoSystem::addToCurrentSave(GridSquareSave* square){

    std::pair<int, int> pairSquare = std::make_pair(square->x, square->y);
    if(this->squaresInSave.find(pairSquare) != this->squaresInSave.end()){
        return;
    }
    this->squaresInSave.insert(pairSquare);

    
    //adds new
    saves[this->currentSave].push_back(*square);
    
};

UndoSystem::~UndoSystem(){
}  




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

//automatically adds a bunch of squares to the grid
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


void Grid::selectOnGrid(RenderWindow* window, Selector* selector, UndoSystem* undoSystem){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;
    
    
    int squareX = (mouseX - this->gridX) / this->squareSize;
    int squareY = (mouseY - this->gridY) / this->squareSize;
    
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

    selector->tilePaintedX = squareX;
    selector->tilePaintedY = squareY;

    selector->brushing = true;
    
    //deals with brush size     o
    // creates                o o o
    //                      o o o o o
    //                        o o o
    //                          o
    //makes center
    drawSquare(squareX, squareY, selector, undoSystem);
    //makes wings
    for(int i = 1; i < selector->brushWidth; i++){
        drawSquare(squareX + i, squareY, selector, undoSystem);
        drawSquare(squareX - i, squareY, selector, undoSystem);
        drawSquare(squareX, squareY + i, selector, undoSystem);
        drawSquare(squareX, squareY - i, selector, undoSystem);
    }
    //makes corners
    for(int i = 1; i < selector->brushWidth; i++){

        for(int j = 1; j < selector->brushWidth - i; j++){

            drawSquare(squareX + j, squareY + i, selector, undoSystem);
            drawSquare(squareX + j, squareY - i, selector, undoSystem);

            drawSquare(squareX - j, squareY + i, selector, undoSystem);
            drawSquare(squareX - j, squareY - i, selector, undoSystem);
        }
    }
}

//changes the color of a specific square
void Grid::drawSquare(int xIndex, int yIndex, Selector* selector, UndoSystem* undoSystem){
    
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

void Grid::releaseTheFlood(RenderWindow* window, Selector* selector, UndoSystem* undoSystem){
    int xTile = this->getMouseOnXTile(window);
    int yTile = this->getMouseOnYTile(window);
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
    Selector* selector, UndoSystem* UndoSystem){
    
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




BrushSizeSelector::BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize){
    this->x = x;
    this->y = y;
    this->shapeSize = size;
    this->brushSize = brushSize;
    this->borderSize = borderSize;

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(unSelectColor);
    this->shape.setOutlineColor(Color::Black);
    this->shape.setOutlineThickness(float(borderSize));

    Text tText = Text();
    tText.setFont(fonts);
    tText.setPosition(float(x + 5), float(y + 5));
    tText.setCharacterSize(24);
    tText.setString(std::to_string(this->brushSize));
    this->text = tText;
};


void BrushSizeSelector::isClicked(RenderWindow* window, Selector* selector){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    if(mouseX < this->x || this->x + this->shapeSize < mouseX){
        return;
    }

    if(mouseY < this->y || this->y + this->shapeSize < mouseY){
        return;
    }

    select(selector);
}

void BrushSizeSelector::select(Selector* selector){
    selector->brushWidth = this->brushSize;
    selector->currentBrushSelector->unselect();
    selector->currentBrushSelector = this;

    this->shape.setFillColor(selectColor);
    this->text.setFillColor(unSelectColor);
}

void BrushSizeSelector::unselect(){
    this->shape.setFillColor(unSelectColor);
    this->text.setFillColor(selectColor);
}

void BrushSizeSelector::display(RenderWindow* window){
    window->draw(this->shape);
    window->draw(this->text);
}


    

ColorSelector::ColorSelector(int x, int y, int size, int borderSize, Color color){
    this->x = x;
    this->y = y;
    this->size = size;
    this->borderSize = borderSize;
    this->color = color;

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(color);
    this->shape.setOutlineColor(unSelectColor);
    this->shape.setOutlineThickness(float(borderSize));
};


void ColorSelector::isClicked(RenderWindow* window, Selector* selector){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    if(mouseX < this->x || this->x + size < mouseX){
        return;
    }

    if(mouseY < this->y || this->y + size < mouseY){
        return;
    }

    selector->currentColorSelector->unSelect();
    selector->currentColorSelector = this;

    selector->selectedColor = this->color;
    this->shape.setOutlineColor(selectColor);
}

void ColorSelector::unSelect(){
    this->shape.setOutlineColor(unSelectColor);
}

void ColorSelector::display(RenderWindow* window){
    window->draw(this->shape);
}

TileTracker::TileTracker(int x, int y){
    this->xLocation = x;
    this->yLocation = y;
    this->xValue = -1;
    this->yValue = -1;

    Text xText;
    xText.setFont(fonts);
    xText.setPosition(float(this->xLocation), float(this->yLocation));
    xText.setCharacterSize(12);
    xText.setString("X: ");
    this->textX = xText;

    Text yText;
    yText.setFont(fonts);
    yText.setPosition(float(this->xLocation + 30), float(this->yLocation));
    yText.setCharacterSize(12);
    yText.setString("Y: ");
    this->textY = yText;
}

void TileTracker::update(RenderWindow* window, Grid* grid){
    this->xValue = grid->getMouseOnXTile(window);
    this->yValue = grid->getMouseOnYTile(window);

    if(this->xValue == -1 || this->yValue == -1){
        return;
    }
        

    this->textX.setString("X: " + std::to_string(this->xValue));
    this->textY.setString("Y: " + std::to_string(this->yValue));
}

void TileTracker::draw(RenderWindow* window){
    window->draw(this->textX);
    window->draw(this->textY);
}





int main(){
    RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(480);

    //declared as a global
    fonts = Font();
    fonts.loadFromFile("fonts/OpenSans-Bold.ttf");
    


    srand (time(NULL));

    int gridXDim = 60;
    int gridYDim = 60;
    int squareSize = 10;
    int gridOffsetX = 100;
    int gridOffsetY = 100;


    Grid grid = Grid(gridXDim, gridYDim, squareSize, gridOffsetX, gridOffsetY);
    // GridSquare testSquare = GridSquare(300, 300, 50);

    TileTracker tileTracker = TileTracker(200, 750);


    UndoSystem undoSystem = UndoSystem(20);

    std::vector<ColorSelector> colorSelectorsVec = {
        ColorSelector(50, 10, 40, 5, Color::Red),
        ColorSelector(100, 10, 40, 5, Color::Green),
        ColorSelector(150, 10, 40, 5, Color::Blue),
        ColorSelector(200, 10, 40, 5, Color::White),
        ColorSelector(250, 10, 40, 5, Color::Black)
    };

    std::vector<BrushSizeSelector> brushSelectorsVec = {
        BrushSizeSelector(20, 100, 30, 5, 1),   //size 1
        BrushSizeSelector(20, 140, 30, 5, 2),   //size 2
        BrushSizeSelector(20, 180, 30, 5, 3),   //size 3
        BrushSizeSelector(20, 220, 30, 5, 4),   //size 4
        BrushSizeSelector(20, 260, 30, 5, 5),   //size 5
        BrushSizeSelector(20, 300, 30, 5, 10)   //size 10
    };

    struct Selector selector;
    selector.held = false;
    selector.brushing = false;

    selector.selectedColor = Color::Black;
    selector.currentColorSelector = &colorSelectorsVec[5];
    selector.brushWidth = 2;
    selector.currentBrushSelector = &brushSelectorsVec[1];

    selector.tilePaintedX = -1;
    selector.tilePaintedY = -1;



    grid.drawLine(10, 10, 45, 30, &selector, &undoSystem);

    bool jClick = false;
    bool kClick = false;
    int previousX = 0;
    int previousY = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        
        if(Keyboard::isKeyPressed(Keyboard::J)){
            //on click
            if(jClick == false){
                jClick = true;

                grid.releaseTheFlood(&window, &selector, &undoSystem);
                undoSystem.commitSave();
            } 
        } else {
            jClick = false;

        }

        if(Keyboard::isKeyPressed(Keyboard::K)){
            //on click
            if(kClick == false){
                kClick = true;

                //test undo
                undoSystem.undo(&grid);
            } 
        } else {
            kClick = false;
        }

        if (Mouse::isButtonPressed(Mouse::Left)){

            // if held
            grid.selectOnGrid(&window, &selector, &undoSystem);

            int currentX = grid.getMouseOnXTileNoCheck(&window);
            int currentY = grid.getMouseOnYTileNoCheck(&window);

            //on click
            if(selector.held == false){
                //refactor into on click later

                for(int i = 0; i < colorSelectorsVec.size(); i++){
                    colorSelectorsVec[i].isClicked(&window, &selector);
                }

                for(int i = 0; i < brushSelectorsVec.size(); i++){
                    brushSelectorsVec[i].isClicked(&window, &selector);
                }

                selector.held = true;
            } else {

                grid.drawLine(previousX, previousY, currentX, currentY, &selector, &undoSystem);
            }

            previousX = currentX;
            previousY = currentY;



        } else {
            selector.held = false;

            if(selector.brushing == true){
                undoSystem.commitSave();
                selector.brushing = false;
                selector.tilePaintedX = -1;
                selector.tilePaintedY = -1;
            }
        }
        tileTracker.update(&window, &grid);

        window.clear();
        grid.display(&window);

        //displays color menu on top
        for(int i = 0; i < colorSelectorsVec.size(); i++){
            colorSelectorsVec[i].display(&window);
        }

        //displays brush size menu on top
        for(int i = 0; i < brushSelectorsVec.size(); i++){
            brushSelectorsVec[i].display(&window);
        }
        tileTracker.draw(&window);

        window.display();
    }

    return 0;
}