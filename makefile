G=g++ -pedantic -std=c++11
F=g++ -pedantic

all: test

test: simulation.o test.o
	$(F) simulation.o test.o -o test
test.o: test.cpp
	$(G) -c test.cpp -o test.o
simulation.o: simulation.cpp
	$(G) -c simulation.cpp -o simulation.o
clean:
	rm test simulation.o test.o outputdata.dat restrictionsdata.dat
cleanall:
	rm test simulation.o test.o outputdata.dat restrictionsdata.dat plot_restriction_energy.png plot_restriction_particle.png
