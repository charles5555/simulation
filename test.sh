#!/bin/bash

g++ -std=c++11 -c boxcounting.cpp -o boxcounting.o &&\
	g++ -std=c++11 -c test.cpp -o test.o &&\
	g++ boxcounting.o test.o -o test &&\
	./test 2 2
