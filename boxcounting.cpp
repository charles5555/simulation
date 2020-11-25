#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
#include "boxcounting.h"
Boxcountingfractaldimension::Boxcountingfractaldimension(){
	size=1000;
	m=10;
}
Boxcountingfractaldimension::Boxcountingfractaldimension(int s, int tama){
	size=s;
	m=tama;
}
int Boxcountingfractaldimension::Openfileandsortdata() {
	int count;
	string line;
	ifstream inFile;

	inFile.open("cluster-2e4.dat");
	if (!inFile) {
		cout << "Unable to open file";
		return EXIT_FAILURE ;
			}
	while(getline(inFile, line)){
		count+=1;
		}  
	cout << "El número de lineas es: " << count << endl;
	inFile.close();
	return 0;
}
	
