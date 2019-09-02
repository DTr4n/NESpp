SRC_DIR ?= ./src
HEADER_DIR ?= ./include

CXXFLAGS = -ggdb -std=c++17

output: main.o CPU.o
	g++ $(CXXFLAGS) main.o CPU.o -o output

main.o: $(SRC_DIR)/main.cpp
	g++ $(CXXFLAGS) -c $(SRC_DIR)/main.cpp

CPU.o: $(SRC_DIR)/CPU.cpp $(HEADER_DIR)/CPU.h
	g++ $(CXXFLAGS) -c $(SRC_DIR)/CPU.cpp

clean:
	rm *.o output