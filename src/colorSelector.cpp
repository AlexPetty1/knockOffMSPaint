#include <SFML/Graphics.hpp>

#include "colorSelector.h"
#include "grid.h"
#include <iostream>

using namespace sf;


ColorSelector::ColorSelector(int x, int y, int size, int borderSize, Color color){
    this->x = x;
    this->y = y;
    this->size = size;
    this->borderSize = borderSize;
    this->color = color;

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(color);
    this->shape.setOutlineColor(unSelectColor);
    this->shape.setOutlineThickness(float(borderSize));
};


void ColorSelector::isClicked(RenderWindow* window, Selector* selector){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    std::cout << "Is clicked called\n";

    if(mouseX < this->x || this->x + size < mouseX){
        return;
    }

    if(mouseY < this->y || this->y + size < mouseY){
        return;
    }

    std::cout << "Is clicked got past edge guards\n";

    if(selector->currentColorSelector != NULL){
        selector->currentColorSelector->unSelect();
    }
    selector->currentColorSelector = this;

    std::cout << "Selected a color\n";
    selector->selectedColor = this->color;
    this->shape.setOutlineColor(selectColor);
}

void ColorSelector::unSelect(){
    std::cout << "called unselect\n";
    //this->shape.setOutlineColor(Color(150, 150, 150, 255));
}

void ColorSelector::display(RenderWindow* window){
    window->draw(this->shape);
}