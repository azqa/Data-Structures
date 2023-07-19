CXX = g++
CXXFLAGS = -Wall -g

driver: driver.cpp show.o
	$(CXX) $(CXXFLAGS) driver.cpp show.o -o driver

show.o: show.h show.cpp
	$(CXX) $(CXXFLAGS) -c show.cpp

test: mytest.cpp show.o
	$(CXX) $(CXXFLAGS) mytest.cpp show.o -o mytest
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

