CXX = g++
CXXFLAGS = -Wall -g

driver: driver.cpp cqueue.o
	$(CXX) $(CXXFLAGS) driver.cpp cqueue.o -o driver

cqueue.o: cqueue.h cqueue.cpp
	$(CXX) $(CXXFLAGS) -c cqueue.cpp

test: mytest.cpp cqueue.o
	$(CXX) $(CXXFLAGS) mytest.cpp cqueue.o -o mytest
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
