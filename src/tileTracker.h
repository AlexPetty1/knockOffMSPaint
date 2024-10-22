#ifndef TILE_TRACKER_H
#define TILE_TRACKER_H 

#include <SFML/Graphics.hpp>

using namespace sf;

//forward declaration
class Grid;

class TileTracker{

    private:
        int xLocation;
        int yLocation;
        int xValue;
        int yValue;
        Text textX;
        Text textY;
        Font fonts;


    public:
        TileTracker(int x, int y);
        void update(RenderWindow* window, Grid* grid);
        void draw(RenderWindow* window);
};

#endif