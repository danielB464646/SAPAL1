# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.

# Compiler flags
CXXFLAGS = -g -O0 -Iinclude

all: clean compile run

compile:
	g++ -g -O0 -Iinclude -o main src/main.cpp src/Simulation.cpp
	g++ $(CXXFLAGS) -o main src/main.cpp

run:
	./main

clean:
	rm -f main
