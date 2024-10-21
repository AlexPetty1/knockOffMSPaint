EXE=main
CC = g++

$(EXE): grid.o
	g++ -Isrc/include -c brushSizeSelector.cpp colorSelector.cpp grid.cpp gridSquare.cpp main.cpp tileTracker.cpp undoSystem.cpp 
	g++ brushSizeSelector.o colorSelector.o grid.o gridSquare.o main.o tileTracker.o undoSystem.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

grid.o: grid.cpp
	$(CC) -Isrc/include -c grid.cpp


