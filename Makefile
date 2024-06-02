#!make -f

CXX=g++
CXXFLAGS=-std=c++11 -g 
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTS=$(SOURCES:.cpp=.o)

run: demo
	./demo

demo: Demo.o Graph.o Algorithms.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++

test: TestCounter.o Test.o Algorithms.o Graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++ -lm

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test