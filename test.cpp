#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
#include "simulation.h"

int main (int argc, char *argv[]) {
	int times1=std::stoi(string(argv[1]));
	int functionform=std::stoi(string(argv[2]));
	string infiledata=std::string(argv[3]);
	Particletype s(times1);
	s.Openfileandsavedata(infiledata);
	s.Sortdata();
	s.Simulation(times1, functionform);
	s.Exportdata();

	return EXIT_SUCCESS;
}
