#include <iostream>
#include <SFML/Graphics.hpp>

#include "gridSquare.h"

using namespace sf;

GridSquare::GridSquare(){

}

void GridSquare::printInfo(){
    std::cout << this->shape.getPosition().x << " " << this->shape.getPosition().y << " "
    << this->shape.getFillColor().b << " "<< this->shape.getScale().x <<"\n";
}

Color GridSquare::getColor(){
    return this->shape.getFillColor();
}

void GridSquare::drawSquare(RenderWindow* window){
    window->draw(this->shape);
}

void GridSquare::setColor(Color newColor){
    this->shape.setFillColor(newColor);
}

GridSquare::GridSquare(int x, int y, int size){

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(Vector2f(float(x), float(y)));
    this->size = size;

    this->shape.setFillColor(Color::White);
}