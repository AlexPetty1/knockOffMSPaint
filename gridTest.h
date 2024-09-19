#ifndef GRIDTEST_H
#define GRIDTEST_H 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <set>

using namespace sf;

//forward declaration
class ColorSelector;
class BrushSizeSelector;
class Grid;

struct FontHouse{
    Font fontSans;
};

struct Selector{
    bool held;
    bool brushing;
    int brushWidth;
    Color selectedColor;
    ColorSelector* currentColorSelector;                //current color selector activated
    BrushSizeSelector* currentBrushSelector;

    int tilePaintedX;   //stores x of tile your painting, -1 painting nothing
    int tilePaintedY;   //prevents multiple updates if holding down
};


struct GridSquareSave{
    int x;
    int y;
    Color color;
};


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

class UndoSystem{

    std::vector<std::vector<GridSquareSave>> saves;
    std::set<std::pair<int, int>> squaresInSave;
    

    int backSave;           //marks furthest you can go back
    int currentSave;        //marks current save your on in array
    int frontSave;          //marks furthest you can go forward
    int amountOfSaves;      //amount of saves stored
    int* sizeSavesArray;    //save size of each save array, 
                            //      saves overwrite previous saves


    public:
        UndoSystem(int amountOfSaves);

        void printSystem();

        void commitSave();

        void undo(Grid* grid);

        void addToCurrentSave(GridSquareSave* square);

        ~UndoSystem();
};


class Grid{
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


        void flood(int xIndex, int yIndex, Color oldColor, 
            Color newColor, UndoSystem* UndoSystem);

        void display(RenderWindow* window);
};

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
    
    public:
        BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize);

        void isClicked(RenderWindow* window, Selector* selector);

        void select(Selector* selector);

        void unselect();

        void display(RenderWindow* window);
};

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