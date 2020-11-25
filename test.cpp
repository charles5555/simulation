#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "boxcounting.h"

int main (int argc, char *argv[]) {
	int s=std::stoi(string(argv[1]));
	int tama=std::stoi(string(argv[2]));
	std::cout << "s: " << s << '\n';
	std::cout << "tama: " << tama << '\n';
	Boxcountingfractaldimension cluster1(s, tama);
	cluster1.Openfileandsortdata();

	return EXIT_SUCCESS;
}
