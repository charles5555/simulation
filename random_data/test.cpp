#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
#include "random_data.h"
#include <vector>

int main (int argc, char *argv[]){
	double particlespercell=std::stod(string(argv[1]));
	int energypercell=std::stoi(string(argv[2]));
	int xdimension=std::stoi(string(argv[3]));
	int ydimension=std::stoi(string(argv[4]));
	int zdimension=std::stoi(string(argv[5]));
	int numberespectre=std::stoi(string(argv[6]));
	//Particletype quantumsin;
	Particletype quantum(particlespercell, energypercell, xdimension, ydimension, zdimension, numberespectre);
	quantum.Generationdata(particlespercell, energypercell, numberespectre, xdimension, ydimension, zdimension);
	//quantumsin.Generationdata();	

	return EXIT_SUCCESS;
}
