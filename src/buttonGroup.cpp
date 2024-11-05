#include <SFML/Graphics.hpp>
#include <vector>

#include "buttonGroup.h"
#include "button.h"

using namespace sf;


ButtonGroup::ButtonGroup(std::vector<Button> buttonList){

    this->buttonsList = buttonList;
    this->numberOfButtons = buttonList.size();
    this->value = -1;
}


ButtonGroup::ButtonGroup(std::vector<Button> buttonsList, 
        int x, int y, int rows, int cols, int gap){
    
    this->buttonsList = buttonsList;
    this->numberOfButtons = buttonsList.size();
    this->value = -1;

    rowify(x, y, rows, cols, gap);
}


void ButtonGroup::rowify(int x, int y, int rows, int cols, int gap){
    int buttonHeight = this->buttonsList[0].getHeight();
    int buttonWidth = this->buttonsList[0].getWidth();

    int rowOn = 0;
    int colOn = 0;
    for(int i = 0; i < this->numberOfButtons; i++){
        int buttonX = x + colOn * buttonWidth + colOn * gap;
        int buttonY = y + rowOn * buttonHeight + rowOn * gap;
        buttonsList[i].setXY(buttonX, buttonY);

        //gets next row
        if(cols == -1){
            rowOn = rowOn + 1;

            if(rowOn == rows){
                rowOn = 0;
                colOn = colOn + 1;
            }
        } else {
            colOn = colOn + 1;

            if(colOn == cols){
                colOn = 0;
                rowOn = rowOn + 1;
            }
        }
    }
}

int ButtonGroup::isClicked(RenderWindow* window){

    int value = -1;
    for(int i = 0; i < this->numberOfButtons; i++){

        value = this->buttonsList[i].isClicked(window);

        if(value != -1){
            //unselects if clicking selected button
            if(i == this->buttonSelected){
                return -1;
            }

            this->buttonsList[this->buttonSelected].unselect();
            this->buttonSelected = i;
            this->value = value;
            return value;
        }

    }
    return -1; 
}

int ButtonGroup::getValue(){
    return value;
}

void ButtonGroup::unSelectAll(){
    for(int i = 0; i < this->numberOfButtons; i++){
        this->buttonsList[i].unselect();
    }
}

void ButtonGroup::display(RenderWindow* window){
    for(int i = 0; i < this->numberOfButtons; i++){\
        this->buttonsList[i].display(window);
    }
}