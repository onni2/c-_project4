# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Source files for the game and launcher
GAME_SRC = game.cpp weapons/weapon_loader.cpp entity/character_loader.cpp battle/battle.cpp lvl_up/lvl_up.cpp
LAUNCHER_SRC = launcher.cpp

# Output executables
GAME_TARGET = game.exe
LAUNCHER_TARGET = launcher.exe

# Default target
all: $(GAME_TARGET) $(LAUNCHER_TARGET)

# Build the game executable
$(GAME_TARGET): $(GAME_SRC)
	$(CXX) $(CXXFLAGS) -o $(GAME_TARGET) $(GAME_SRC)

# Build the launcher executable
$(LAUNCHER_TARGET): $(LAUNCHER_SRC)
	$(CXX) $(CXXFLAGS) -o $(LAUNCHER_TARGET) $(LAUNCHER_SRC)

# Clean up generated files
clean:
	rm -f $(GAME_TARGET) $(LAUNCHER_TARGET)

# Rebuild the program
rebuild: clean all
