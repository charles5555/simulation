#!/bin/bash

g++ -std=c++11 -c simulation.cpp -o simulation.o &&\
	g++ -std=c++11 -c test.cpp -o test.o &&\
	g++ simulation.o test.o -o test &&\
	./test 2
