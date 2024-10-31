#include <SFML/Graphics.hpp>

#include "grid.h"
#include "brushSizeSelector.h"

using namespace sf;

BrushSizeSelector::BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize){
    this->fonts = Font();
    this->fonts.loadFromFile("fonts/OpenSans-Bold.ttf");

    this->x = x;
    this->y = y;
    this->shapeSize = size;
    this->brushSize = brushSize;
    this->borderSize = borderSize;

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(unSelectColor);
    this->shape.setOutlineColor(Color::White);
    this->shape.setOutlineThickness(float(borderSize));

    this->brushText = Text(std::to_string(this->brushSize), this->fonts, 15);
    this->brushText.setPosition(float(this->x + 5), float(this->y + 5));
    this->brushText.setFillColor(selectColor);
};


void BrushSizeSelector::isClicked(RenderWindow* window, Selector* selector){
    int mouseX = Mouse::getPosition(*window).x;
    int mouseY = Mouse::getPosition(*window).y;

    if(mouseX < this->x || this->x + this->shapeSize < mouseX){
        return;
    }

    if(mouseY < this->y || this->y + this->shapeSize < mouseY){
        return;
    }

    select(selector);
}

void BrushSizeSelector::select(Selector* selector){
    selector->brushWidth = this->brushSize;
    selector->currentBrushSelector->unselect();
    selector->currentBrushSelector = this;

    this->shape.setFillColor(selectColor);
    this->brushText.setFillColor(unSelectColor);
}

void BrushSizeSelector::unselect(){
    this->shape.setFillColor(unSelectColor);
    this->brushText.setFillColor(selectColor);
}

void BrushSizeSelector::display(RenderWindow* window){
    this->brushText.setFont(this->fonts);   //the text will not load if only loading font in constructor
                                            //  so it loads here as well
    window->draw(this->shape);
    window->draw(this->brushText);
}