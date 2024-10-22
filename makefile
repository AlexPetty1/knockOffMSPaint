
CXX_FILES = $(wildcard src/*.cpp)   # All .cpp files in the directory
OBJ_FILES = $(CXX_FILES:src/%.cpp=$(OBJ_DIR)/%.o)   # Corresponding .o files
OBJ_DIR = obj
SRC_DIR = src
INC = -Isrc/include
CC = g++
LIBS = -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

# Rules
all: $(OBJ_FILES)
	g++ $(OBJ_FILES) -o main $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(INC) -c $< -o $@
