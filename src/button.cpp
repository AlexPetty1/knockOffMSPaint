#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.h"

using namespace sf;

Button::Button(int x, int y, int lengthX, int lengthY, String text, int value){
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
    this->shape.setOutlineColor(defaultBorderColor);
    this->shape.setOutlineThickness(float(defaultBorderWidth));

    this->text = Text(text, this->fonts, defaultCharacterSize);
    this->text.setFillColor(defaultTextColor);
    this->value = value;

    setXY(x, y);

    this->isSelected = 0;
};

// tests if the button is clicked, assumes mouse is already down
//      returns -1 if not clicked
//      returns the value assigned to the button if clicked
//      switches buttons color and state if clicked
int Button::isClicked(RenderWindow* window){
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

void Button::setValue(int value){
    this->value = value;
}

void Button::select(){
    this->shape.setFillColor(this->selectColor);
    this->text.setFillColor(this->unSelectColor);
    this->isSelected = 1;
}

void Button::setSelectColor(Color newColor){
    this->selectColor = newColor;
}

void Button::setUnSelectColor(Color newColor){
    this->unSelectColor = newColor;
}

void Button::unselect(){
    this->shape.setFillColor(this->unSelectColor);
    this->text.setFillColor(this->selectColor);
    this->isSelected = 0;
}

void Button::display(RenderWindow* window){
    this->text.setFont(this->fonts);   //the text will not load if only loading font in constructor
                                            //  so it loads here as well
    window->draw(this->shape);
    window->draw(this->text);
}

int Button::getWidth(){
    return this->lengthX;
}

int Button::getHeight(){
    return this->lengthX;
}

void Button::setXY(int x, int y){
    this->x = x;
    this->y = y;
    this->shape.setPosition(float(x), float(y));
    this->text.setPosition(float(this->x + 5), float(this->y + 5));
}



Button::~Button(){
}