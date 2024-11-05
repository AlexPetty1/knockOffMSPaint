#ifndef BUTTON_GROUP_H
#define BUTTON_GROUP_H 

#include <SFML/Graphics.hpp>
#include "button.h"

using namespace sf;

class ButtonGroup{

private:
    int numberOfButtons;
    std::vector<Button> buttonsList;

    int buttonSelected;
    int rows;
    int columns;
    int xLocation;
    int yLocation;
    int value;
    
public:
    ButtonGroup(std::vector<Button> buttonsList);   //unrowified
    ButtonGroup(std::vector<Button> buttonsList, 
        int x, int y, int rows, int cols, int gap);   //rowified

    void rowify(int x, int y, int rows, int cols, int gap);
    int isClicked(RenderWindow* window);
    int getValue();
    void unSelectAll();
    void display(RenderWindow* window);
};
#endif