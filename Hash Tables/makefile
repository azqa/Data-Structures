CXX = g++
CXXFLAGS = -Wall -g

driver: driver.cpp vdetect.o
	$(CXX) $(CXXFLAGS) driver.cpp vdetect.o -o driver

vdetect.o: vdetect.h vdetect.cpp
	$(CXX) $(CXXFLAGS) -c vdetect.cpp

test: mytest.cpp vdetect.o
	$(CXX) $(CXXFLAGS) mytest.cpp vdetect.o -o mytest

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
