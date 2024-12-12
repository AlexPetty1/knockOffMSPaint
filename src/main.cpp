#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <stdio.h> 
#include <stdlib.h>     
#include <time.h>
#include <math.h>

#include "grid.h"
#include "tileTracker.h"
#include "toggle.h"
#include "toggleGroup.h"
#include "gridSelector.h"

using namespace sf;

int main(){

    RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(480);
    
    srand (time(NULL));

    int gridXDim = 60;
    int gridYDim = 60;
    int squareSize = 10;
    int gridOffsetX = 100;
    int gridOffsetY = 100;

    Grid grid = Grid(gridXDim, gridYDim, squareSize, gridOffsetX, gridOffsetY);

    TileTracker tileTracker = TileTracker(200, 750);

    UndoSystem undoSystem = UndoSystem(20);


    Color Red = Color(255, 0, 0, 255);
    Color RedSelect = Color(200, 0, 0, 255);
    Color Green = Color(0, 255, 0, 255);
    Color GreenSelect = Color(0, 200, 0, 255);
    Color Blue = Color(0, 0, 255, 255);
    Color BlueSelect = Color(0, 0, 200, 255);
    Color White = Color(255, 255, 255, 255);
    Color WhiteSelect = Color(220, 220, 220, 255);
    Color Black = Color(0, 0, 0, 255);
    Color BlackSelect = Color(10, 10, 10, 255);
    Color Magenta = Color(255, 0, 255, 255);
    Color MagentaSelect = Color(200, 0, 200, 255);
    std::vector<Toggle> colorSelectorsList = {
        Toggle(0, 0, 25, 25, "", Red.toInteger()),
        Toggle(0, 0, 25, 25, "", Green.toInteger()),
        Toggle(0, 0, 25, 25, "", White.toInteger() - 1),    //-1 as white is -1 as a signed integer
        Toggle(0, 0, 25, 25, "", Blue.toInteger()),
        Toggle(0, 0, 25, 25, "", Black.toInteger()),
        Toggle(0, 0, 25, 25, "", Magenta.toInteger())
    };
    colorSelectorsList[0].setSelectColor(RedSelect);
    colorSelectorsList[0].setUnSelectColor(Red);
    colorSelectorsList[1].setSelectColor(GreenSelect);
    colorSelectorsList[1].setUnSelectColor(Green);
    colorSelectorsList[2].setSelectColor(WhiteSelect);
    colorSelectorsList[2].setUnSelectColor(White);
    colorSelectorsList[3].setSelectColor(BlueSelect);
    colorSelectorsList[3].setUnSelectColor(Blue);
    colorSelectorsList[4].setSelectColor(BlackSelect);
    colorSelectorsList[4].setUnSelectColor(Black);
    colorSelectorsList[5].setSelectColor(MagentaSelect);
    colorSelectorsList[5].setUnSelectColor(Magenta);

    ToggleGroup colorSelectorsGroup = ToggleGroup(colorSelectorsList, 50, 10, 10, 5, 10);
    colorSelectorsGroup.selectSpecific(4);

    std::vector<Toggle> brushSelectorsList = {
        Toggle(0, 0, 25, 25, "1", 1),
        Toggle(0, 0, 25, 25, "2", 2),
        Toggle(0, 0, 25, 25, "3", 3),
        Toggle(0, 0, 25, 25, "4", 4),
        Toggle(0, 0, 25, 25, "5", 5),
        Toggle(0, 0, 25, 25, "10", 10),
        Toggle(0, 0, 25, 25, "15", 15),
        Toggle(0, 0, 25, 25, "25", 25)
    };
    ToggleGroup brushSelectorsGroup = ToggleGroup(brushSelectorsList, 10, 100, -1, 2, 5);
    brushSelectorsGroup.selectSpecific(1);

    std::vector<Toggle> modeSelectorList = {
        Toggle(0, 0, 50, 25, "Brush", 0),
        Toggle(0, 0, 50, 25, "Fill", 1),
        Toggle(0, 0, 50, 25, "Select", 2),
        Toggle(0, 0, 50, 25, "Line", 3)
    };
    ToggleGroup modeSelectorGroup = ToggleGroup(modeSelectorList, 350, 10, 1, -1, 5);
    modeSelectorGroup.selectSpecific(0);

    Toggle undoToggle = Toggle(300, 10, 50, 25, "Undo", 1);    

    struct GridSelector selector;
    selector.held = false;
    selector.effectingGrid = false;

    selector.selectedColor = Color::Black;
    selector.brushWidth = 2;

    selector.tilePaintedX = -1;
    selector.tilePaintedY = -1;

    selector.lineCord1[0] = -1;
    selector.lineCord1[1] = -1;

    bool isMousePressed = false;
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

        isMousePressed = Mouse::isButtonPressed(Mouse::Left);

        if (isMousePressed == true){

            grid.selectOnGrid(&window, &selector, &undoSystem);
            int currentX = grid.getMouseOnXTileNoCheck(&window);
            int currentY = grid.getMouseOnYTileNoCheck(&window);

            //on click
            if(selector.held == false){
                
                int newBrushWidth = brushSelectorsGroup.isClicked(&window);
                if(newBrushWidth != -1){
                    selector.brushWidth = newBrushWidth;
                }

                int newColor = colorSelectorsGroup.isClicked(&window);
                if(newColor != -1){
                    selector.selectedColor = Color(newColor);
                }

                int undoValue = undoToggle.isClicked(&window);
                if(undoValue != -1){
                    undoSystem.undo(&grid);
                }

                int newModeValue = modeSelectorGroup.isClicked(&window);
                if(newModeValue != -1){
                    selector.mode = newModeValue;

                    if(selector.mode == 3){
                        selector.lineCord1[0] = -1;
                        selector.lineCord1[1] = -1;
                    }
                }

                selector.held = true;
            } else {
                grid.drawLine(previousX, previousY, currentX, currentY, &selector, &undoSystem);
            }

            previousX = currentX;
            previousY = currentY;
        }
        
        if(isMousePressed == false){
            selector.held = false;

            if(selector.effectingGrid == true){
                undoSystem.commitSave();
                selector.effectingGrid = false;
                selector.tilePaintedX = -1;
                selector.tilePaintedY = -1;
            }
        }


        tileTracker.update(&window, &grid);
        window.clear();
        grid.display(&window);

        //displays color menu on top
        tileTracker.draw(&window);
        brushSelectorsGroup.display(&window);
        colorSelectorsGroup.display(&window);
        modeSelectorGroup.display(&window);
        undoToggle.display(&window);


        window.display();
    }



    return 0;
}