#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include <string>
#include <vector>
using std::string;
using namespace std;
class Beginsimulation {
public:
	Beginsimulation();
	int xdimension, ydimension, zdimension, cellnumber, totalcells, totallines, cero1, cero2, init, m, totalparticles, totallines1, times1, times, functionform;
	double alpha, time, coef, t0, particlepercell, energypercell;
};
class Particletype : public Beginsimulation {
	public:
		Particletype();
	        Particletype(int);
		int Openfileandsavedata();
		int Sortdata();
		int Simulation(int, int);
		int Exportdata();
		std::vector<vector<vector<vector<double> > > > matrixinfo;
		std::vector<vector<double> > info;
		std::vector<vector<double> > particles;
		std::vector<vector<vector<vector<double> > > > matrixparticles;
		std::vector<vector<vector<vector<vector<double> > > > > matrixsimulation;
		std::vector<double> restrictionsuma;
		std::vector<double> restrictionenergysuma;
};
class Help {
public: 
	Help();
};
#endif
