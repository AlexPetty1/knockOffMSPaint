#ifndef EVENT_H
#define EVENT_H 

#include <SFML/Graphics.hpp>

using namespace sf;

class Button{

private:
        const Color defaultUnSelectColor = Color(180, 180, 180, 255);
        const Color defaultSelectColor = Color(30, 30, 30, 255);
        const Color defaultBorderColor = Color::Black;
        const Color defaultTextColor = Color::Black;
        const int defaultBorderWidth = 3;
        const int defaultCharacterSize = 12;

        int x;
        int y;
        int lengthX;
        int lengthY;
        int borderSize;
        int value;
        RectangleShape shape;
        Text text;
        Font fonts;
        Color selectColor;
        Color unSelectColor;

public:
    Button(int x, int y, int lengthX, int lengthY, String text, int value);
    ~Button();

    void setSelectColor(Color);
    void setUnSelectColor(Color);
    void setValue(int value);


    
    int isClicked(RenderWindow* window);
    void select();
    void unselect();
    void display(RenderWindow*);
};
#endif