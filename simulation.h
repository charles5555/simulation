#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include <string>
#include <vector>
using std::string;
using namespace std;
class Beginsimulation {
public:
	Beginsimulation();
	int xdimension, ydimension, zdimension, cellnumber, totalcells, totallines, cero1, cero2, init, m, totalparticles, totallines1;
};
class Particletype : public Beginsimulation {
	public:
		Particletype();
	        Particletype(int);
		int Openfileandsavedata();
		int Sortdata();
		std::vector<vector<vector<vector<double> > > > matrixinfo;
		std::vector<vector<double> > info;
		std::vector<vector<double> > particles;
		std::vector<vector<vector<vector<double> > > > matrixparticles;
};
class Help {
public: 
	Help();
};
#endif
