#ifndef _BOXCOUNTING_H_
#define _BOXCOUNTING_H_
#include <string>
#include <vector>
using std::string;
using namespace std;
class Boxcountingfractaldimension {
public:
	Boxcountingfractaldimension();
	double xmin, ymin, xmax, ymax;
	int m, count;
};
class Particletype : public Boxcountingfractaldimension {
	public:
		Particletype();
		Particletype(int);
		int Openfileandsavedata();
		int Sortdata();
		void Countingpoints();
		void Fractaldimension();
		std::vector<vector<double> > matrixinfo;
		std::vector<vector<int> > malla;
		
};
class Help{
public:
	Help();
};
#endif
