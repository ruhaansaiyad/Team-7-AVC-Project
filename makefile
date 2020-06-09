INCLUDE = -I C:\\SFML\include 
LIBS = -L C:\\SFML\lib 
main.exe: main.o 
	g++ $(LIBS) -o main main.o -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
main.o: main.cpp 
	g++  -c $(INCLUDE) main.cpp
