#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "simulation.h"

int main (int argc, char *argv[]) {
	int m=std::stoi(string(argv[1]));
	Particletype s(m);
	s.Openfileandsavedata();
	s.Sortdata();

	return EXIT_SUCCESS;
}
