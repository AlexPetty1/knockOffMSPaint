#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.h"

using namespace sf;

Button::Button(int x, int y, int lengthX, int lengthY, String text, int value){
    this->fonts = Font();
    this->fonts.loadFromFile("fonts/OpenSans-Bold.ttf");

    this->x = x;
    this->y = y;
    this->lengthX = lengthX;
    this->lengthY = lengthY;
    this->borderSize = defaultBorderWidth;

    this->selectColor = defaultSelectColor;
    this->unSelectColor = defaultUnSelectColor;

    this->shape = RectangleShape(Vector2f(float(lengthX), float(lengthY)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(defaultSelectColor);
    this->shape.setOutlineColor(defaultBorderColor);
    this->shape.setOutlineThickness(float(defaultBorderWidth));

    this->text = Text(text, this->fonts, defaultCharacterSize);
    this->text.setPosition(float(this->x + 5), float(this->y + 5));
    this->text.setFillColor(defaultTextColor);

    this->value = value;
};


int Button::isClicked(RenderWindow* window){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    if(mouseX < this->x || this->x + this->lengthX < mouseX){
        return -1;
    }

    if(mouseY < this->y || this->y + this->lengthY < mouseY){
        return -1;
    }

    select();
    return this->value;
}

void Button::setValue(int value){
    this->value = value;
}

void Button::select(){
    this->shape.setFillColor(selectColor);
}

void Button::unselect(){
    this->shape.setFillColor(unSelectColor);
}

void Button::display(RenderWindow* window){
    this->text.setFont(this->fonts);   //the text will not load if only loading font in constructor
                                            //  so it loads here as well
    window->draw(this->shape);
    window->draw(this->text);
}


Button::~Button(){
}