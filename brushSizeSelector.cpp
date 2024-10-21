#include <SFML/Graphics.hpp>

#include "grid.h"
#include "brushSizeSelector.h"

using namespace sf;

BrushSizeSelector::BrushSizeSelector(int x, int y, int size, int borderSize, int brushSize){
    this->x = x;
    this->y = y;
    this->shapeSize = size;
    this->brushSize = brushSize;
    this->borderSize = borderSize;

    this->shape = RectangleShape(Vector2f(float(size), float(size)));
    this->shape.setPosition(float(x), float(y));
    this->shape.setFillColor(unSelectColor);
    this->shape.setOutlineColor(Color::Black);
    this->shape.setOutlineThickness(float(borderSize));

    this->fonts = Font();
    this->fonts.loadFromFile("fonts/OpenSans-Bold.ttf");

    Text tText = Text();
    tText.setFont(this->fonts);
    tText.setPosition(float(x + 5), float(y + 5));
    tText.setCharacterSize(24);
    tText.setString(std::to_string(this->brushSize));
    this->text = tText;
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
    this->text.setFillColor(unSelectColor);
}

void BrushSizeSelector::unselect(){
    this->shape.setFillColor(unSelectColor);
    this->text.setFillColor(selectColor);
}

void BrushSizeSelector::display(RenderWindow* window){
    window->draw(this->shape);
    window->draw(this->text);
}