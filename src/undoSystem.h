#ifndef UNDO_SYSTEM_H
#define UNDO_SYSTEM_H 

#include <SFML/Graphics.hpp>
#include <set>
#include <vector>

using namespace sf;

//forward declaration
class Grid;

struct GridSquareSave{
    int x;
    int y;
    Color color;
};

class UndoSystem{


    private:
        std::vector<std::vector<GridSquareSave>> saves;
        std::set<std::pair<int, int>> squaresInSave;
        

        int backSave;           //marks furthest you can go back
        int currentSave;        //marks current save your on in array
        int frontSave;          //marks furthest you can go forward
        int amountOfSaves;      //amount of saves stored

    public:
        UndoSystem(int amountOfSaves);

        void printSystem();

        void commitSave();

        void undo(Grid* grid);

        void addToCurrentSave(GridSquareSave* square);

        ~UndoSystem();
};

#endif