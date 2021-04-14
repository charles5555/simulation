G=g++ -std=c++11
F=g++

all: test

test: random_data.o test.o
	$(F) random_data.o test.o -o test
test.o: test.cpp
	$(G) -c test.cpp -o test.o
random_data.o: random_data.cpp
	$(G) -c random_data.cpp -o random_data.o
clean:
	rm test random_data.o test.o cellsdata.dat 

