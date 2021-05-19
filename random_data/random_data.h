#ifndef _RANDOM_DATA_H_
#define _RANDOM_DATA_H_
#include <string>
#include <vector>
using std::string;
using namespace std;
class Randomgenerationdata {
public: Randomgenerationdata();
	int energypercell, randomnumint, numberespectre, espectre, xdimension, ydimension, zdimension;
	double randomnumdouble, particlespercell;
};
class Particletype : public Randomgenerationdata {
	public:
		Particletype(void);
		Particletype(double, int, int, int, int, int);
		int Generationdata(double, int, int, int, int, int);
		int Savedata();
		std::vector<double> vectorenergylevel;
		std::vector<vector<vector<double> > > vectorcells;
};
#endif
