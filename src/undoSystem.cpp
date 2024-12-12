#include <iostream>

#include "undoSystem.h"
#include "grid.h"

UndoSystem::UndoSystem(int amountOfSaves){
    this->currentSave = 0;
    this->backSave = 0;
    this->frontSave = 1;

    // std::vector<std::vector<GridSquare>> tSaves(amountOfSaves, std::vector<GridSquare> ());
    // this->saves = ;

    std::vector<std::vector<GridSquareSave>> tSaves;
    tSaves.resize(amountOfSaves);
    this->saves = tSaves;
    this->amountOfSaves = amountOfSaves;

};

void UndoSystem::printSystem(){

    for(int i = 0; i < this->saves.size(); i++){
        std::cout << "Save: " << i << " \n";
        for(int j = 0; j < this->saves[i].size(); j++){

            GridSquareSave save = this->saves[i][j];
            std::cout << save.x << " " << save.y << " " << save.color.toInteger() << "\n";

        }
    }
}

void UndoSystem::commitSave(){
    currentSave = currentSave + 1;
    if(currentSave >= amountOfSaves){
        currentSave = 0;
    }

    frontSave = currentSave;

    if(frontSave == backSave){
        backSave = backSave + 1;

        if(backSave >= amountOfSaves){
            backSave = 0;
        }
    }

    this->saves[currentSave].clear();
    this->squaresInSave.clear();
    
};

void UndoSystem::undo(Grid* grid){

    if(this->backSave == this->currentSave){
        return;
    }
    
    this->currentSave = this->currentSave - 1;
    if(this->currentSave == -1){
        this->currentSave = this->amountOfSaves - 1;
    }

    grid->autoAdd(this->saves[this->currentSave]);
    this->squaresInSave.clear();
};

void UndoSystem::addToCurrentSave(GridSquareSave* square){

    std::pair<int, int> pairSquare = std::make_pair(square->x, square->y);
    if(this->squaresInSave.find(pairSquare) != this->squaresInSave.end()){
        return;
    }
    this->squaresInSave.insert(pairSquare);

    saves[this->currentSave].push_back(*square);    
};

UndoSystem::~UndoSystem(){
}  