all: compile link

# compile:
# 	g++ -Isrc/include -c main.cpp

# link:
# 	g++ main.o -o main -Lsrc\lib -lsfml-graphics -lsfml-window -lsfml-system


# placeTest:
# 	g++ -Isrc/include -c placeTest.cpp
# 	g++ placeTest.o -o placeTest -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system


gridTest:
	g++ -Isrc/include -c gridTest.cpp
	g++ gridTest.o -o gridTest -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system



