CXX = g++
CXXFLAGS = -Wall -g

driver: driver.cpp fuel.o
	$(CXX) $(CXXFLAGS) driver.cpp fuel.o -o driver

fuel.o: fuel.h fuel.cpp
	$(CXX) $(CXXFLAGS) -c fuel.cpp

test: mytest.cpp fuel.o
	$(CXX) $(CXXFLAGS) mytest.cpp fuel.o -o mytest
clean:
	rm *~

run:
	./driver

val:
	valgrind ./driver

run1:
	./mytest


run2:
	valgrind ./mytest

