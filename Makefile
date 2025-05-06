CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

.PHONY: test valgrind clean
OUTPUT = test

TEST_SRC = Tests.cpp SquareMat.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $^

valgrind: $(OUTPUT)
	valgrind --leak-check=full --track-origins=yes ./$(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)