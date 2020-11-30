#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "boxcounting.h"

int main (int argc, char *argv[]) {
	//int s=std::stoi(string(argv[1]));
	int tama=std::stoi(string(argv[1]));
	//std::cout << "s: " << s << '\n';
	std::cout << "tama: " << tama << '\n';
	Particletype cluster1(tama);
	cluster1.Openfileandsavedata();
	cluster1.Sortdata();

	return EXIT_SUCCESS;
}
