CC := gcc
CXX := g++

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic

C_PROGRAM := problem1_c
CPP_PROGRAM := problem1_cpp

.PHONY: all c cpp run-c run-cpp clean

all: c cpp

c: $(C_PROGRAM)

cpp: $(CPP_PROGRAM)

$(C_PROGRAM): problem1.c
	$(CC) $(CFLAGS) $< -o $@

$(CPP_PROGRAM): problem1.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run-c: $(C_PROGRAM)
	./$(C_PROGRAM)

run-cpp: $(CPP_PROGRAM)
	./$(CPP_PROGRAM)

clean:
	rm -f $(C_PROGRAM) $(CPP_PROGRAM)
