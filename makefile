G=g++ -std=c++11
F=g++

all: test

test: boxcounting.o test.o
	$(F) boxcounting.o test.o -o test
test.o: test.cpp
	$(G) -c test.cpp -o test.o
boxcounting.o: boxcounting.cpp
	$(G) -c boxcounting.cpp -o boxcounting.o
clean:
	rm test boxcounting.o test.o
