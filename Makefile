# Compiler
CXX = g++
CXXFLAGS = -I./include -std=c++23 -Wall -Wextra

# Libraries
LDFLAGS = -L./lib -lsfml-window -lsfml-system -lsfml-graphics

# Object 
DIR_SRC = src
DIR_OBJ = output

SRC = $(wildcard $(DIR_SRC)/*.cpp $(DIR_SRC)/**/*.cpp)
OBJ = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(SRC))

# Executable File
EXE = main.exe

# Target
all: $(EXE) run

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ) $(LDFLAGS)

# Run (gdb)
run:
	./$(EXE)

# Clean
clean:
	rm -rf output/* $(EXE)