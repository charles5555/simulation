#ifndef _RANDOM_DATA_H_
#define _RANDOM_DATA_H_
#include <string>
#include <vector>
using std::string;
using namespace std;
class Randomgenerationdata {
public: Randomgenerationdata();
	int particlespercell, energypercell, randomnumint, numberespectre, espectre, xdimension, ydimension, zdimension;
	double randomnumdouble;
};
class Particletype : public Randomgenerationdata {
	public:
		Particletype(void);
		Particletype(int, int, int, int, int, int);
		int Generationdata(int, int, int, int, int);
		int Savedata();
		std::vector<double> vectorenergylevel;
		std::vector<vector<vector<double> > > vectorcells;
};
#endif
