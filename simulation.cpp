#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <typeinfo>
using namespace std;
#include "simulation.h"
Beginsimulation::Beginsimulation(){
	cout << "The program is starting" << endl;
}
Particletype::Particletype(){ // constructor sin valores
	init=0;	
}
Particletype::Particletype(int times1){ // constructor con valores
	times=times1;
}
int Particletype::Openfileandsavedata() { // como guardar los datos
	string line;
	totalcells=0;
	totallines=0;
	time=1.0;
	alpha=1.0;
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
	totallines1=0;
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
	//for (int i=0; i<totalparticles; ++i){
	//	for (int j=0; j<5; ++j){
	//		cout << "particles[" << i << "][" << j << "]= " << particles[i][j] << endl;
	//	}
	//}
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
				matrixinfo[i][j][k].resize(4);
			}
		}
	}
	energypercell=0.0;
	for (int i=1; i<totallines; ++i){
		energypercell=energypercell+info[i][1];
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
		if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]<0){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=-exp((matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1])*time);
		}
		if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]>0){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=exp(-(matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1])*time);
		}
		if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]==0){
			matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=0.0;
		}
	}
	//for (int i=0;i<xdimension; ++i){
	//	for (int j=0; j<ydimension; ++j){
	//		for (int k=0; k<zdimension; ++k){
	//			cout << "matrixinfo[" << i << "][" << j << "][" << k << "][0]= " << matrixinfo[i][j][k][0] << endl;
	//			cout << "matrixinfo[" << i << "][" << j << "][" << k << "][1]= " << matrixinfo[i][j][k][1] << endl;
	//			cout << "matrixinfo[" << i << "][" << j << "][" << k << "][2]= " << matrixinfo[i][j][k][2] << endl;
	//			cout << "matrixinfo[" << i << "][" << j << "][" << k << "][3]= " << matrixinfo[i][j][k][3] << endl;
	//		}
	//	}
	//}
	//
	//cout << "totalparticles= " << totalparticles << endl;
	//cout << "xdimension= " << xdimension << endl;
	//matrixparticles.resize(totalparticles);
	//for (int i=0; i<totalparticles; ++i){
	//	matrixparticles[i].resize(xdimension);
	//}
	//for (int i=0; i<totalparticles; ++i){
	//	for (int j=0; j<xdimension; ++j){
	//		matrixparticles[i][j].resize(ydimension);
	//	}
	//}
	//for (int i=0; i<totalparticles; ++i){
	//	for (int j=0; j<xdimension; ++j){
	//		for (int k=0; k<ydimension; ++k){
	//			matrixparticles[i][j][k].resize(zdimension);
	//		}
	//	}
	//}
	//
	//for (int i=0; i<totalparticles; ++i){
	//	matrixparticles[static_cast<int>(particles[i][0])-1][static_cast<int>(particles[i][1])-1][static_cast<int>(particles[i][2])-1][static_cast<int>(particles[i][3])-1]=particles[i][4];
	//}
	//for (int i=0; i<totalparticles; ++i){
	//	for (int j=0; j<xdimension; ++j){
	//		for (int k=0; k<ydimension; ++k){
	//			for (int l=0; l<zdimension; ++l){
	//				cout << "matrixparticles[" << i << "][" << j << "][" << k << "][" << l << "]= " << matrixparticles[i][j][k][l] << endl;
	//			}
	//		}
	//	}
	//}
	return 0;
}
int Particletype::Simulation(int times, int functionform){
	cout << "times= " << times << endl;
	//cout << "times es una variable tipo " << typeid(times).name() << endl;
	matrixsimulation.resize(times);
	for (int i=0; i<times; ++i){
		matrixsimulation[i].resize(xdimension);
	}
	for (int i=0; i<times; ++i){
		for (int j=0; j<xdimension; ++j){
			matrixsimulation[i][j].resize(ydimension);
		}
	}
	for (int i=0; i<times; ++i){
		for (int j=0; j<xdimension; ++j){
			for (int k=0; k<ydimension; ++k){
				matrixsimulation[i][j][k].resize(zdimension);
			}
		}
	}
	for (int i=0; i<times; ++i){
		for (int j=0; j<xdimension; ++j){
			for (int k=0; k<ydimension; ++k){
				for (int l=0; l<zdimension; ++l){
					matrixsimulation[i][j][k][l].resize(2);
				}
			}
		}
	}
	particlepercell=0.0;
	particlepercell=totalparticles/totalcells;
	restrictionenergysuma.resize(times);
	restrictionsuma.resize(times);
	cout << "times = " << times << endl;
	if (functionform==0){ //Exponencial
		for (int i=0; i<times; ++i){
			for (int j=1; j<totallines; ++j){
				if ((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1])<0){
			matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=-exp(((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]))*time);
			matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]=-(exp(((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]))*time))*info[j][1];
				}
				if ((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1])>0){
			matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=exp(-((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]))*time);
			matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]=(exp(-((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]))*time))*info[j][1];
				}
				if ((particlepercell-matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0])+alpha*(energypercell-matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1])==0){
			matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=0.0;
				}
				restrictionsuma[i]=restrictionsuma[i]+matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0];
				restrictionenergysuma[i]=restrictionenergysuma[i]+matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1];
			}
			time=time+1.0;
		}
	}
	//if (functionform==1){ //Potencia
	//	t0=5.0;
	//	for (int i=0; i<times; ++i){
	//		for (int j=0; j<totallines; ++j){
	//			if (matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]<0){
	//		matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=-(time+t0)**((matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]));
	//			}
	//			if (matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]>0){
	//		matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=(time+t0)**(-(matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]));
	//			}
	//			if (matrixinfo[static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[j][2]-1)][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]==0){
	//		matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0]=0.0;
	//			}	
	//		}
	//		times=times+1.0;
	//	}
	//}
	else {
		cout << "Invalid form" << endl;
		return EXIT_FAILURE;
		}
	for (int i=0; i<times; ++i){
		cout << "restrictionsuma[" << i << "]= " << restrictionsuma[i] << endl;
		cout << "restrictionenergysuma[" << i << "]= " << restrictionenergysuma[i] << endl;
	}
	//for (int i=0; i<times; ++i){
	//	for (int j=0; j<xdimension; ++j){
	//		for (int k=0; k<ydimension; ++k){
	//			for (int l=0; l<zdimension; ++l){
	//				cout << "matrixsimulation[" << i << "][" << j << "][" << k << "][" << l << "][" << 0 << "]= " << matrixsimulation[i][j][k][l][0] << endl; 
	//			}
	//		}
	//	}
	//}
	return 0;
}
int Particletype::Exportdata(){
	char name[]="outputdata.dat";
	ofstream outfile(name, ios::app);
	//outfile << "time" << " ";
	//for (int j=1; j<totallines; ++j){
	//	outfile << "C"i"_particles" << " " << "C"i"_energy" << " ";
	//}
	//outfile << "R"i"_particles" << " " << "R"i"_energy" << endl;
	for (int i=0; i<times; ++i){
		outfile << i << " ";
		for (int j=1; j<totallines; ++j){
			outfile << matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][0] << " " << matrixsimulation[i][static_cast<int>(info[j][2])-1][static_cast<int>(info[j][3])-1][static_cast<int>(info[j][4])-1][1]<< " ";
		}
		//outfile << restrictionsuma[i] << " " << restrictionenergysuma[i] << endl;
		//outfile << endl;
	}
	outfile.close();
	char name1[]="restrictionsdata.dat";
	ofstream outfile1(name1, ios::app);
	for (int i=0; i<times; ++i){
		outfile1 << i << " " << restrictionsuma[i] << " " << restrictionenergysuma[i] << endl;
	}
	outfile1.close();
	return 0;
}
