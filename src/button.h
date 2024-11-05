#ifndef BUTTON_H
#define BUTTON_H 

#include <SFML/Graphics.hpp>

using namespace sf;

class Button{
    private:
            Color defaultUnSelectColor = Color(180, 180, 180, 255);
            Color defaultSelectColor = Color(30, 30, 30, 255);
            Color defaultBorderColor = Color::White;
            Color defaultTextColor = Color::Black;
            int defaultBorderWidth = 3;
            int defaultCharacterSize = 12;

            int isSelected;
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

        int getWidth();
        int getHeight();
        void setXY(int x, int y);
        
        int isClicked(RenderWindow* window);
        void select();
        void unselect();
        void display(RenderWindow*);
};
#endif