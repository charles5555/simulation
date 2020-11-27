#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
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
	string Load;
	ifstream inFile;

	inFile.open("cluster-2e4.dat");
	if (!inFile) {
		cout << "Unable to open file";
		return EXIT_FAILURE ;
			}
	while(getline(inFile, line)){
		count+=1;
		}  
	/*cout << "El número de lineas es: " << count << endl;*/
	//double **matrixinfo= new double*[count];
	vector<vector<double> > matrixinfo(count);
	for (int i=0; i<count; ++i){
		//matrixinfo[i] = new double[3];
		matrixinfo[i].resize(3);
		}
	inFile.clear();
	inFile.seekg(0);
	for (int i=0; i<count; ++i){
		matrixinfo[i][0]=i+1;
		inFile >> matrixinfo[i][1] >> matrixinfo[i][2];
	}
	
	inFile.close();
	for (int i=0; i<3; ++i){
		for (int j=0; j<3; ++j){
			cout << "la entrada matrixinfo["<< i <<"]["<< j <<"] es: "<< matrixinfo[i][j] << endl;  
		}
	}
	for (int i=0; i<count; ++i){
		//delete [] matrixinfo[i];
		matrixinfo[i].clear();
	}
	//delete [] matrixinfo;
	matrixinfo.clear();
	return 0;
}
	
