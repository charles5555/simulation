#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
#include "random_data.h"

int main (int argc, char *argv[]){
	int particlespercell=std::stoi(string(argv[1]));
	int energypercell=std::stoi(string(argv[2]));
	double xdimension=std::stod(string(argv[3]));
	double ydimension=std::stod(string(argv[4]));
	double zdimension=std::stod(string(argv[5]));
	int numberespectre=std::stoi(string(argv[6]));
	//Particletype quantumsin;
	Particletype quantum(particlespercell, energypercell, xdimension, ydimension, zdimension, numberespectre);
	quantum.Generationdata(particlespercell, numberespectre, xdimension, ydimension, zdimension);
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <typeinfo>
using namespace std;;
	//quantumsin.Generationdata();	

	return EXIT_SUCCESS;
}
