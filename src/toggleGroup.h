#ifndef TOGGLE_GROUP_H
#define TOGGLE_GROUP_H 

#include <SFML/Graphics.hpp>
#include "toggle.h"

using namespace sf;

class ToggleGroup{

private:
    int numberOfToggles;
    std::vector<Toggle> togglesList;

    int toggleSelected;
    int rows;
    int columns;
    int xLocation;
    int yLocation;
    int value;
    
public:
    ToggleGroup(std::vector<Toggle> togglesList);   //unrowified
    ToggleGroup(std::vector<Toggle> togglesList, 
        int x, int y, int rows, int cols, int gap);   //rowified

    void setFontSize(int size);
    void rowify(int x, int y, int rows, int cols, int gap);
    int isClicked(RenderWindow* window);
    int getValue();
    void unSelectAll();
    void display(RenderWindow* window);
    int selectSpecific(int index);
};
#endif