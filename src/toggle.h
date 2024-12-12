#ifndef TOGGLE_H
#define TOGGLE_H 

#include <SFML/Graphics.hpp>

using namespace sf;

class Toggle{
    private:
            Color defaultUnSelectColor = Color(180, 180, 180, 255);
            Color defaultSelectColor = Color(30, 30, 30, 255);
            Color defaultBorderSelectColor = Color(180, 180, 180, 255);
            Color defaultBorderUnselectColor = Color::White;
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
        Toggle(int x, int y, int lengthX, int lengthY, String text, int value);
        ~Toggle();

        void setSelectColor(Color);
        void setUnSelectColor(Color);
        void setValue(int value);

        int getValue();
        int getWidth();
        int getHeight();
        void setXY(int x, int y);
        void setFontSize(int x);
        
        int isClicked(RenderWindow* window);
        void select();
        void unselect();
        void display(RenderWindow*);
};
#endif