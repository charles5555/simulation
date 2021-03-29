#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
#include "simulation.h"
Beginsimulation::Beginsimulation(){
	cout << "The program is starting" << endl;
}
Particletype::Particletype(){ // constructor sin valores
	init=0;	
}
Particletype::Particletype(int m){ // constructor con valores
	init=m;
}
int Particletype::Openfileandsavedata() { // como guardar los datos
	string line;
	totalcells=0;
	totallines=0;
	ifstream inFile;
	inFile.open("cellsdata1.dat"); // abre el archivo cellsdata.dat
	if (!inFile) {
		cout << "Unable to open file" << endl;
		return EXIT_FAILURE;
	}
	while(getline(inFile, line)){ // cuenta el número de lineas que tiene el archivo
		totallines+=1;
	}
	totalcells=totallines-1; 
	cout << "The total number of cells is: " << totalcells << endl;
	info.resize(totallines); // se arma la matriz info donde guardaremos la información del archivo
	for (int i=0; i<totallines; ++i){
		info[i].resize(5);
	}
	inFile.clear();
	inFile.seekg(0);
	for (int i=0; i<totallines; ++i){
		inFile >> info[i][0] >> info[i][1] >> info[i][2] >> info[i][3] >> info[i][4];
	} // se guarda la información en la matriz info
	inFile.close();
	//for (int i=0; i<totallines; ++i){
	//	for (int j=0; j<5; ++j){
	//		cout << "info["<< i << "]["<< j << "]= " << info[i][j] << endl;
	//	}
	//}
// abrimos el archivo donde está la información de las partículas
	totalparticles=0;
	inFile.open("particlesdata.dat");
	if (!inFile){
		cout << "Unable to open file" << endl;
		return EXIT_FAILURE;
	}
	while(getline(inFile, line)){
		totallines1+=1;
	}
	totalparticles=totallines1;
	cout << "The total number of particles is: " << totalparticles << endl;
	particles.resize(totalparticles);
	for (int i=0; i<totalparticles; ++i){
		particles[i].resize(5);
	}
	inFile.clear();
	inFile.seekg(0);
	for (int i=0; i<totalparticles; ++i){
		inFile >> particles[i][0] >> particles[i][1] >> particles[i][2] >> particles[i][3] >> particles[i][4];
	}
	inFile.close();
	for (int i=0; i<totalparticles; ++i){
		for (int j=0; j<5; ++j){
			cout << "particles[" << i << "][" << j << "]= " << particles[i][j] << endl;
		}
	}
	return 0;
}
int Particletype::Sortdata() {
	xdimension=info[0][0]; //definimos las dimensiones de cada eje que tiene el archivo .dar
	ydimension=info[0][1];
	zdimension=info[0][2];
	cout << "xd= " << xdimension << endl;
	cout << "yd= " << ydimension << endl;
	cout << "zd= " << zdimension << endl;
	cout << "totallines= " << totallines << endl;
	matrixinfo.resize(xdimension); // construimos la latriz de 4 dimensiones
	for (int i=0; i<xdimension; ++i){
		matrixinfo[i].resize(ydimension);
	}
	for (int i=0; i<xdimension; ++i){
		for (int j=0; j<ydimension; ++j){
			matrixinfo[i][j].resize(zdimension);
		}
	}
	for (int i=0; i<xdimension; ++i){
		for (int j=0; j<ydimension; ++j){
			for (int k=0; k<zdimension; ++k){
				matrixinfo[i][j][k].resize(3);
			}
		}
	}
	for (int i=1; i<totallines; ++i){
		matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]=info[i][0];
		matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]=info[i][1];
		matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]=6.0;
		if (static_cast<int>(info[i][2])-1 == 0 or static_cast<int>(info[i][2])-1 == xdimension-1){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		}
		if (static_cast<int>(info[i][3])-1 == 0 or static_cast<int>(info[i][3])-1 == ydimension-1){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		}
		if (static_cast<int>(info[i][4])-1 == 0 or static_cast<int>(info[i][4])-1 == zdimension-1){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		}	
	}
	//for (int i=0;i<xdimension; ++i){
	//	for (int j=0; j<ydimension; ++j){
	//		for (int k=0; k<zdimension; ++k){
				//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][0]= " << matrixinfo[i][j][k][0] << endl;
				//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][1]= " << matrixinfo[i][j][k][1] << endl;
				//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][2]= " << matrixinfo[i][j][k][2] << endl;
			//}
		//}
	//}
	cout << "totalparticles= " << totalparticles << endl;
	cout << "xdimension= " << xdimension << endl;
	matrixparticles.resize(totalparticles);
	for (int i=0; i<totalparticles; ++i){
		matrixparticles[i].resize(xdimension);
	}
	for (int i=0; i<totalparticles; ++i){
		for (int j=0; j<xdimension; ++j){
			matrixparticles[i][j].resize(ydimension);
		}
	}
	for (int i=0; i<totalparticles; ++i){
		for (int j=0; j<xdimension; ++j){
			for (int k=0; k<ydimension; ++k){
				matrixparticles[i][j][k].resize(zdimension);
			}
		}
	}
	//
	for (int i=0; i<totalparticles; ++i){
		matrixparticles[static_cast<int>(particles[i][0])-1][static_cast<int>(particles[i][1])-1][static_cast<int>(particles[i][2])-1][static_cast<int>(particles[i][3])-1]=particles[i][4];
	}
	for (int i=0; i<totalparticles; ++i){
		for (int j=0; j<xdimension; ++j){
			for (int k=0; k<ydimension; ++k){
				for (int l=0; l<zdimension; ++l){
					cout << "matrixparticles[" << i << "][" << j << "][" << k << "][" << l << "]= " << matrixparticles[i][j][k][l] << endl;
				}
			}
		}
	}
	return 0;
}
	
