#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include <string>
#include <vector>
using std::string;
using std::vector;
class Beginsimulation {
public:
	Beginsimulation();
	int xdimension, ydimension, zdimension, cellnumber, totalcells, totallines, cero1, cero2, init, m, totalparticles, totallines1, times1, times, functionform, particlespercell;
	double alpha, time, coef, t0, energypercell, energyspectre, totalenergy, energypercell1;
	string infiledata;
};
class Particletype : public Beginsimulation {
	public:
		Particletype();
	        Particletype(int);
		int Openfileandsavedata(string);
		int Sortdata();
		int Simulation(int, int);
		int Exportdata();
		vector<vector<vector<vector<double> > > > matrixinfo;
		vector<vector<double> > info;
		vector<vector<double> > particles;
		vector<vector<vector<vector<double> > > > matrixparticles;
		vector<vector<vector<vector<vector<double> > > > > matrixsimulation;
		vector<double> restrictionsuma;
		vector<double> restrictionenergysuma;
		vector<double> vectorenergyspectre;
		vector<double> vectorsign;
};
class Help {
public: 
	Help();
};
#endif
