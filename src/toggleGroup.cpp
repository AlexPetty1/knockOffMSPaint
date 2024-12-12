#include <SFML/Graphics.hpp>
#include <vector>

#include "toggleGroup.h"
#include "toggle.h"
#include <iostream>

using namespace sf;


ToggleGroup::ToggleGroup(std::vector<Toggle> toggleList){

    this->togglesList = toggleList;
    this->numberOfToggles = toggleList.size();
    this->value = -1;

    unSelectAll();
}


ToggleGroup::ToggleGroup(std::vector<Toggle> togglesList, 
        int x, int y, int rows, int cols, int gap){
    
    this->togglesList = togglesList;
    this->numberOfToggles = togglesList.size();
    this->value = -1;

    rowify(x, y, rows, cols, gap);
    unSelectAll();
}


void ToggleGroup::rowify(int x, int y, int rows, int cols, int gap){
    int toggleHeight = this->togglesList[0].getHeight();
    int toggleWidth = this->togglesList[0].getWidth();

    int rowOn = 0;
    int colOn = 0;
    for(int i = 0; i < this->numberOfToggles; i++){
        int toggleX = x + colOn * toggleWidth + colOn * gap;
        int toggleY = y + rowOn * toggleHeight + rowOn * gap;
        togglesList[i].setXY(toggleX, toggleY);

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

int ToggleGroup::isClicked(RenderWindow* window){

    int value = -1;
    for(int i = 0; i < this->numberOfToggles; i++){

        value = this->togglesList[i].isClicked(window);

        if(value != -1){
            //unselects if clicking selected toggle
            if(i == this->toggleSelected){
                return -1;
            }

            this->togglesList[this->toggleSelected].unselect();
            this->toggleSelected = i;
            this->value = value;
            return value;
        }

    }
    return -1; 
}

int ToggleGroup::selectSpecific(int index){
    if(0 > index || index >= this->numberOfToggles){
        return -1;
    }

    this->togglesList[index].select();
    this->value = togglesList[index].getValue();
    this->toggleSelected = index;
    return this->value;
}

int ToggleGroup::getValue(){
    return value;
}

void ToggleGroup::unSelectAll(){
    for(int i = 0; i < this->numberOfToggles; i++){
        this->togglesList[i].unselect();
    }
}

void ToggleGroup::display(RenderWindow* window){
    for(int i = 0; i < this->numberOfToggles; i++){\
        this->togglesList[i].display(window);
    }
}

void ToggleGroup::setFontSize(int size){
    for(int i = 0; i < this->numberOfToggles; i++){\
        this->togglesList[i].setFontSize(size);
    }
}