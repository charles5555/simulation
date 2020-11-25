#ifndef _BOXCOUNTING_H_
#define _BOXCOUNTING_H_
#include <string>
using std::string;
class Boxcountingfractaldimension{
public:
	Boxcountingfractaldimension();
	Boxcountingfractaldimension(int, int);
	int Openfileandsortdata();
	void Countingpoints();
	void Fractaldimension();
	int size, m;
};
class Help{
public:
	Help();
};
#endif
