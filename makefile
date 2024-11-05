CXX_FILES = $(wildcard src/*.cpp)   # All .cpp files in the directory
SRC_DIR = src
CC = g++
EXE = main

OBJ_FILES_WIN = $(CXX_FILES:src/%.cpp=$(OBJ_DIR_WIN)/%.o)   # Corresponding .o files
OBJ_DIR_WIN = obj_win
INC_WIN = -Isrc/include
LIBS_WIN = -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

OBJ_FILES_LIN = $(CXX_FILES:src/%.cpp=$(OBJ_DIR_LIN)/%.o)   # Corresponding .o files
OBJ_DIR_LIN = obj_lin
LIBS_LIN = -lsfml-graphics -lsfml-window -lsfml-system 
FLAGS_LIN = -g


# linux
linux: $(OBJ_FILES_LIN)
	g++ $(FLAGS_LIN) $(OBJ_FILES_LIN) -o $(EXE) $(LIBS_WIN)

$(OBJ_DIR_LIN)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS_LIN) -c $< -o $@

# windows
# windows: $(OBJ_FILES_WIN)
# 	g++ $(OBJ_FILES_WIN) -o main $(LIBS_WIN)

# $(OBJ_DIR_WIN)/%.o: $(SRC_DIR)/%.cpp
# 	$(CC) $(INC_WIN) -c $< -o $@


clean: 
	rm -f $(OBJ_DIR_LIN)/*.o makeLin
	rm -f $(OBJ_DIR_WIN)/*.o makeLin

