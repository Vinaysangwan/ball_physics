# Compiler
CXX = g++
CXXFLAGS = -I./include -std=c++23 -Wall -Wextra

# Libraries
LDFLAGS = -L./lib -lsfml-window -lsfml-system -lsfml-graphics

# Object Files
OBJ = output/main.o output/Game.o output/Ball.o

# Executable File
EXE = main.exe

# Target
all: compile link run

# Compile
compile:
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o output/main.o
	$(CXX) $(CXXFLAGS) -c src/core/Game.cpp -o output/Game.o
	$(CXX) $(CXXFLAGS) -c src/entities/Ball.cpp -o output/Ball.o

# Link
link:
	$(CXX) $(OBJ) -o main $(LDFLAGS)

# Run (gdb)
run:
	./$(EXE)

# Clean
clean:
	rm -rf output/* $(EXE)