# Compiler and flags
CXX = g++
CXXFLAGS = -g -O0 -Iinclude

# Target executable
TARGET = main

# Automatically find all .cpp and .h files in the src directory
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files into an executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
