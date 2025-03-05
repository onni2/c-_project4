# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Source files
SRC = main.cpp weapon_loader.cpp character_loader.cpp

# Output executable
TARGET = my_program

# Default target
all: $(TARGET)

# Link source files directly into the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Rebuild the program
rebuild: clean all