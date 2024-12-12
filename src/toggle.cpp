#include <SFML/Graphics.hpp>
#include <iostream>

#include "toggle.h"

using namespace sf;

Toggle::Toggle(int x, int y, int lengthX, int lengthY, String text, int value){
    this->fonts = Font();
    this->fonts.loadFromFile("fonts/OpenSans-Bold.ttf");

    this->lengthX = lengthX;
    this->lengthY = lengthY;
    this->borderSize = defaultBorderWidth;

    this->selectColor = defaultSelectColor;
    this->unSelectColor = defaultUnSelectColor;

    this->shape = RectangleShape(Vector2f(float(lengthX), float(lengthY)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(defaultUnSelectColor);
    this->shape.setOutlineColor(defaultBorderUnselectColor);
    this->shape.setOutlineThickness(float(defaultBorderWidth));

    this->text = Text(text, this->fonts, defaultCharacterSize);
    this->text.setFillColor(defaultTextColor);
    this->value = value;

    setXY(x, y);

    this->isSelected = 0;
};

// tests if the Toggle is clicked, assumes mouse is already down
//      returns -1 if not clicked
//      returns the value assigned to the Toggle if clicked
//      switches Toggles color and state if clicked
int Toggle::isClicked(RenderWindow* window){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    if(mouseX < this->x || this->x + this->lengthX < mouseX){
        return -1;
    }

    if(mouseY < this->y || this->y + this->lengthY < mouseY){
        return -1;
    }

    if(isSelected == 0){
        select();
    } else {
        unselect();
    }
    
    return this->value;
}

void Toggle::setValue(int value){
    this->value = value;
}

void Toggle::select(){
    this->shape.setFillColor(this->selectColor);
    this->text.setFillColor(this->unSelectColor);
    this->shape.setOutlineColor(this->defaultBorderSelectColor);
    this->isSelected = 1;
}

void Toggle::unselect(){
    this->shape.setFillColor(this->unSelectColor);
    this->text.setFillColor(this->selectColor);
    this->shape.setOutlineColor(this->defaultBorderUnselectColor);
    this->isSelected = 0;
}

void Toggle::setSelectColor(Color newColor){
    this->selectColor = newColor;
}

void Toggle::setUnSelectColor(Color newColor){
    this->unSelectColor = newColor;
}

void Toggle::display(RenderWindow* window){
    this->text.setFont(this->fonts);   //the text will not load if only loading font in constructor
                                            //  so it loads here as well
    window->draw(this->shape);
    window->draw(this->text);
}

int Toggle::getWidth(){
    return this->lengthX;
}

int Toggle::getHeight(){
    return this->lengthX;
}

int Toggle::getValue(){
    return this->value;
}

void Toggle::setXY(int x, int y){
    this->x = x;
    this->y = y;
    this->shape.setPosition(float(x), float(y));
    this->text.setPosition(float(this->x + 5), float(this->y + 5));
}

void Toggle::setFontSize(int size){
    this->text.setCharacterSize(size);
}


Toggle::~Toggle(){
}