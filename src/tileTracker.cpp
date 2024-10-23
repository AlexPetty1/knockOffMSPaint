#include "tileTracker.h"
#include "grid.h"

using namespace sf;

TileTracker::TileTracker(int x, int y){
    this->xLocation = x;
    this->yLocation = y;
    this->xValue = -1;
    this->yValue = -1;


    this->fonts = Font();
    this->fonts.loadFromFile("fonts/OpenSans-Bold.ttf");

    Text xText = Text("X: ", this->fonts, 12);
    xText.setPosition(float(this->xLocation), float(this->yLocation));
    this->textX = xText;

    Text yText = Text();
    yText.setFont(this->fonts);
    yText.setPosition(float(this->xLocation + 30), float(this->yLocation));
    yText.setCharacterSize(12);
    yText.setString("Y: ");
    this->textY = yText;
}

void TileTracker::update(RenderWindow* window, Grid* grid){
    this->xValue = grid->getMouseOnXTile(window);
    this->yValue = grid->getMouseOnYTile(window);

    if(this->xValue == -1 || this->yValue == -1){
        return;
    }
        

    this->textX.setString("X: " + std::to_string(this->xValue));
    this->textY.setString("Y: " + std::to_string(this->yValue));
}

void TileTracker::draw(RenderWindow* window){
    window->draw(this->textX);
    window->draw(this->textY);
}