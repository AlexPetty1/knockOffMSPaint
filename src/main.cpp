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
#include "colorSelector.h"
#include "brushSizeSelector.h"

using namespace sf;

int main(){
    RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(480);
    
    srand (time(NULL));

    //creates directory if it exists
    // const char* savePath = "./saves";
    // struct stat sb;
    // if (stat(savePath, &sb) != 0){
    //     _mkdir(savePath);
    // }

    int gridXDim = 60;
    int gridYDim = 60;
    int squareSize = 10;
    int gridOffsetX = 100;
    int gridOffsetY = 100;

    Grid grid = Grid(gridXDim, gridYDim, squareSize, gridOffsetX, gridOffsetY);

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
    selector.currentColorSelector = &colorSelectorsVec[4];
    selector.brushWidth = 2;
    selector.currentBrushSelector = &brushSelectorsVec[1];

    selector.tilePaintedX = -1;
    selector.tilePaintedY = -1;

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

            // on hold
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

            //off
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