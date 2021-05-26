#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <typeinfo>
#include <math.h>
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
int Particletype::Openfileandsavedata(string infiledata) { // como guardar los datos
	string line;
	totalcells=0;
	totallines=-1;
	time=1.0;
	alpha=1.0;
	
	ifstream inFile;
	inFile.open(infiledata); // abre el archivo cellsdata.dat
	if (!inFile) {
		cout << "Unable to open file" << endl;
		return EXIT_FAILURE;
	}
	while(getline(inFile, line)){ // cuenta el número de lineas que tiene el archivo
		totallines+=1;
	}
	totalcells=totallines-1; 
	cout << "The total number of cells is: " << totalcells << endl;
	info.resize(totallines-1);
	potentialenergy.resize(totallines-1);
	info1.resize(totallines-1); // se arma la matriz info donde guardaremos la información del archivo
	for (int i=0; i<totallines-1; ++i){
		info[i].resize(2);// este vector lleva la información del número de partículas y la energía de la celda
		info1[i].resize(3);// este vector lleva la información de las entradas de la celda en los ejes coordenados
		potentialenergy[i].resize(2); // este vector lleva la información de la temperatura y el potencial químico de las celdas
	}
	inFile.clear();
	inFile.seekg(0);
	inFile >> energyspectre;
	vectorenergyspectre.resize(energyspectre);
	for (int i=0; i<energyspectre; ++i){
		inFile >> vectorenergyspectre[i]; 
	}
	//cout << "funciona" << endl;
	particlespercell=0;
	energypercell=0.0;
	inFile >> particlespercell;// partículas de las celdas en equilibrio
	inFile >> energypercell1; // energía de las celdas en equilibrio
	inFile >> meantemperature;// temperatura de las celdas en equilibrio
	inFile >> meanpotential; // potencial químico de las celdas en equilibrio
	totalparticles=totalcells*particlespercell;
	inFile >> xdimension;
	inFile >> ydimension;
	inFile >> zdimension;
	inFile >> cero1;
	inFile >> cero2;
	for (int i=0; i<totallines-1; ++i){
		//inFile >> info[i][0] >> info[i][1] >> info[i][2] >> info[i][3] >> info[i][4];
		inFile >> info[i][0] >> info[i][1] >> potentialenergy[i][0] >> potentialenergy[i][1] >> info1[i][0] >> info1[i][1] >> info1[i][2];
		//cout << info[i][0] << info1[i][0]<<endl;
	} // se guarda la información en la matriz info
	inFile.close();
	//for (int i=0; i<totallines; ++i){
	//	for (int j=0; j<2; ++j){
	//		cout << "potentialenergy["<< i << "]["<< j << "]= " << potentialenergy[i][j] << endl;
	//	}
	//}
	//for (int i=0; i<totallines-1; ++i){
		//cout << "info["<< i << "]["<< 0 << "]= " << info[i][0] <<  "      " << "info[" << i << "][" << 1 << "]= " << info[i][1] << "      " << "info1[" << i << "][" << 0 << "]= " << info1[i][0] << "      " << "info1[" << i << "][" << 1 << "]= " << info1[i][1] << "      " << "info1[" << i << "][" << 2 << "]= " << info1[i][2] << endl;
	//}
	

	for (int i=0; i<energyspectre; ++i){
		cout << "vectorenergyspectre[" << i << "]= " << vectorenergyspectre[i] << endl;
	}	
	return 0;
}
int Particletype::Sortdata() {
	//xdimension=info[0][0]; //definimos las dimensiones de cada eje que tiene el archivo .dar
	//ydimension=info[0][1];
	//zdimension=info[0][2];
	cout << "xd= " << xdimension << endl;
	cout << "yd= " << ydimension << endl;
	cout << "zd= " << zdimension << endl;
	//cout << "totallines= " << totallines << endl;
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
				matrixinfo[i][j][k].resize(6);
			}
		}
	}
	totalenergy=0.0;
	for (int i=0; i<totallines-1; ++i){
		totalenergy=totalenergy+info[i][1];
		//**matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]=info[i][0];
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][0]=info[i][0];
		//**matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]=info[i][1];
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][1]=info[i][1];
		//**matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][4]=0.0;
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][3]=potentialenergy[i][0]; //lleva la información de la temperatura de la celda	
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][4]=0.0;
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][5]=potentialenergy[i][1]; // lleva la información del potencial químico de la celda
		//if (static_cast<int>(info[i][2])-1 == 0 or static_cast<int>(info[i][2])-1 == xdimension-1){
			//matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		//}
		//if (static_cast<int>(info[i][3])-1 == 0 or static_cast<int>(info[i][3])-1 == ydimension-1){
			//matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		//}
		//if (static_cast<int>(info[i][4])-1 == 0 or static_cast<int>(info[i][4])-1 == zdimension-1){
			//matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][2]-=1;
		//}
		//if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]<0){
			//matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=-exp((matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1])*time);	
			//cout << "There is an exponential argument that is less to zero, check it out" << endl;
			//return EXIT_FAILURE;
		//}
		//if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]>0){
		//	matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=exp(-(matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1])*time);
		//}
		//if (matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][0]+alpha*matrixinfo[static_cast<int>(info[i][2]-1)][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][1]==0){
		//	matrixinfo[static_cast<int>(info[i][2])-1][static_cast<int>(info[i][3])-1][static_cast<int>(info[i][4])-1][3]=0.0;
		//}
	}
	energypercell=totalenergy/totalcells;
	//double constboltzmann=1.380649e-23;
	//double constboltzmann=1.0;
	//meantemperature=1;
	//double meanconst=3*(meantemperature);
	//particlespercell=totalparticles/totalcells;
	cout << "todo bien hasta aquí" << endl;	
	//vectorsign.resize(totallines-1);
	for (int i=0; i<totallines-1; ++i){
		//matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][2]=(meanpotential*particlespercell)-(potentialenergy[i][1]*(meantemperature/potentialenergy[i][0])*info[i][0])-((energypercell1)-((meantemperature/potentialenergy[i][0])*info[i][1]));
		matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][2]=(meanpotential)-(potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*info[i][1]));
		//vectorsign[i]=particlespercell-info[i][0]-energypercell1+info[i][1];
		//cout << "vectorsign[" << i << "]= " << vectorsign[i] << endl;
		cout << "matrixinfo[" << info1[i][0]-1 << "][" << info1[i][1]-1 << "][" << info1[i][2]-1 << "][" << 2 << "]= " << matrixinfo[info1[i][0]-1][info1[i][1]-1][info1[i][2]-1][2] << endl;
	}
	
	//cout << "matrix[" << 0 << "][" << 0 << "][" << 0 << "][" << 2 << "]= " << matrixinfo[0][0][0][2] << endl;
	cout << "todo bien hasta aquí parte 2" << endl;
	for (int i=0; i<xdimension; ++i){
		for (int j=0; j<ydimension; ++j){
			for (int k=0; k<zdimension; ++k){
				//cout << "matrix[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << endl;
				if (k != 0){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i][j][k-1][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i][j][k-1][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i][j][k-1][5]*(meantemperature/matrixinfo[i][j][k-1][3]))))-((energypercell1)-((meantemperature/matrixinfo[i][j][k-1][3])*matrixinfo[i][j][k-1][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno porque k es distinto de 0" << endl;
				}
				
				//cout << "matrix[" << i << "][" << j << "][" << k << "][" << 2 << "]= " << matrixinfo[i][j][k][4] << endl;
				if (k != zdimension-1){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i][j][k+1][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i][j][k+1][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i][j][k+1][5]*(meantemperature/matrixinfo[i][j][k+1][3]))))-((energypercell1)-((meantemperature/matrixinfo[i][j][k+1][3])*matrixinfo[i][j][k+1][1]));
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+(((meanpotential/meantemperature)*particlespercell)-((potentialenergy[i][1]/potentialenergy[i][0])*matrixinfo[i][j][k+1][0]))-(((1/meantemperature)*energypercell1)-((1/potentialenergy[i][0])*matrixinfo[i][j][k+1][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno en z porque k no llegó al máximo" << endl;
				}
				if (j !=0){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i][j-1][k][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i][j-1][k][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i][j-1][k][5]*(meantemperature/matrixinfo[i][j-1][k][3]))))-((energypercell1)-((meantemperature/matrixinfo[i][j-1][k][3])*matrixinfo[i][j-1][k][1]));
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+(((meanpotential/meantemperature)*particlespercell)-((potentialenergy[i][1]/potentialenergy[i][0])*matrixinfo[i][j-1][k][0]))-(((1/meantemperature)*energypercell1)-((1/potentialenergy[i][0])*matrixinfo[i][j-1][k][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno en y porque j=0" << endl;
				}
				if (j != ydimension-1){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i][j+1][k][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i][j+1][k][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i][j+1][k][5]*(meantemperature/matrixinfo[i][j+1][k][3]))))-((energypercell1)-((meantemperature/matrixinfo[i][j+1][k][3])*matrixinfo[i][j+1][k][1]));
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+(((meanpotential/meantemperature)*particlespercell)-((potentialenergy[i][1]/potentialenergy[i][0])*matrixinfo[i][j+1][k][0]))-(((1/meantemperature)*energypercell1)-((1/potentialenergy[i][0])*matrixinfo[i][j+1][k][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno en y porque j  no alcanzó el máximo" <<  endl;
				}
				if (i != 0){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i-1][j][k][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i-1][j][k][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i-1][j][k][5]*(meantemperature/matrixinfo[i-1][j][k][3]))))-((energypercell1)-((meantemperature/matrixinfo[i-1][j][k][3])*matrixinfo[i-1][j][k][1]));
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+(((meanpotential/meantemperature)*particlespercell)-((potentialenergy[i][1]/potentialenergy[i][0])*matrixinfo[i-1][j][k][0]))-(((1/meantemperature)*energypercell1)-((1/potentialenergy[i][0])*matrixinfo[i-1][j][k][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno en x porque i=0" << endl;
				}
				if (i != xdimension-1){
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential*particlespercell)-((potentialenergy[i][1]*(meantemperature/potentialenergy[i][0]))*matrixinfo[i+1][j][k][0]))-((energypercell1)-((meantemperature/potentialenergy[i][0])*matrixinfo[i+1][j][k][1]));
					matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+((meanpotential)-((matrixinfo[i+1][j][k][5]*(meantemperature/matrixinfo[i+1][j][k][3]))))-((energypercell1)-((meantemperature/matrixinfo[i+1][j][k][3])*matrixinfo[i+1][j][k][1]));
					//matrixinfo[i][j][k][2]=matrixinfo[i][j][k][2]+(((meanpotential/meantemperature)*particlespercell)-((potentialenergy[i][1]/potentialenergy[i][0])*matrixinfo[i+1][j][k][0]))-(((1/meantemperature)*energypercell1)-((1/potentialenergy[i][0])*matrixinfo[i+1][j][k][1]));
					matrixinfo[i][j][k][4]=matrixinfo[i][j][k][4]+1;
					//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 4 << "]= " << matrixinfo[i][j][k][4] << " subió uno en x porque i no alcanzó el máximo" << endl;	
				}
				//cout << "matrixinfo[" << i << "][" << j << "][" << k << "][" << 2 << "]= " << matrixinfo[i][j][k][2] << endl;
				//cout << "termina ciclo en k" << endl;
			}
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
	cout << "times es una variable tipo " << typeid(times).name() << endl;
	cout << "xdimension= " << xdimension << endl;
	cout << "matrixsimulation.resize " << matrixsimulation.size() << endl << std::flush;
	matrixsimulation.resize(times);
	cout << "hola1" << endl << std::flush;
	for (int i=0; i<times; ++i){
		matrixsimulation[i].resize(xdimension);
	}
	cout << "hola2 " << endl << std::flush;
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
					matrixsimulation[i][j][k][l].resize(4);
				}
			}
		}
	}
	cout << "hola" << endl;
	energypercell=totalenergy/totalcells;
	//particlespercell=totalparticles/totalcells;
	restrictionenergysuma.resize(times);
	restrictionsuma.resize(times);
	double timereference=0.001;
	cout << energypercell1 << endl;
	cout << "times = " << times << endl;
	//for (int i=0; i<times; ++i){
	//	for (int j=0; j<xdimension; ++j){
	//		for (int k=0; k<ydimension; ++k){
	//			for (int l=0; l<zdimension; ++l){
	//				for (int o=0; o<2; ++o){
	//					matrixsimulation[i][j][k][l][o]=0;
	//				}
	//			}
	//		}
	//	}
	//}
	//cout << "info[1][2]= " << info[1][2] << endl;
	//cout << "info[1][3]= " << info[1][3] << endl;
	//cout << "info[1][4]= " << info[1][4] << endl;
	//cout << "matrixsimulation[0][0][0][0][0]= " << matrixsimulation[0][0][0][0][0] << endl;
	cout << "matrixinfo[0][0][0][2]= " << matrixinfo[2][0][0][2] << endl;
	if (functionform==0){ //Exponencial
		for (int i=0; i<times; ++i){
			for (int j=0; j<totallines-1; ++j){
				//if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]>0){
				if (matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]>0){
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=round((particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i));
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]=exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i);
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][3]=(energypercell-info[j][1])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i);
					//cout << "matrixsimulation[][][][][3]= " << matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2] << endl;
					//matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]=floor((particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*i));
					//if (energypercell1-info[j][1]>0 & particlespercell-info[j][0]>0){
					//	for (int k=0; k<energyspectre; ++k){
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]<0 & particlespercell-info[j][0]<0){
					//	for (int k=0; k<energyspectre; ++k){
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]<0 & particlespercell-info[j][0]>0){
					//	for (int k=0; k<energyspectre; ++k){
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]-(particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]>0 & particlespercell-info[j][0]<0){
					//	for (int k=0; k<energyspectre; ++k){
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]-(particlespercell-info[j][0])*exp(-(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
				}
				//if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]<0){
				if (matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]<0){
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=round((particlespercell-info[j][0])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i));
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]=exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i);
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][3]=(energypercell1-info[j][1])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i);
					//cout << "matrixsimulation[][][][][3]= " << matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][3] << endl;


					//if (energypercell1-info[j][1]>0 & particlespercell-info[j][0]>0){
					//	for (int k=0; k<energyspectre; ++k){			
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]<0 & particlespercell-info[j][0]<0){
					//	for (int k=0; k<energyspectre; ++k){			
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]<0 & particlespercell-info[j][0]>0){
					//	for (int k=0; k<energyspectre; ++k){			
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]-(particlespercell-info[j][0])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
					//if (energypercell1-info[j][1]>0 & particlespercell-info[j][0]<0){
					//	for (int k=0; k<energyspectre; ++k){			
					//		matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]-(particlespercell-info[j][0])*exp((matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*(timereference)*i)*vectorenergyspectre[k];
					//	}
					//}
				}	
				//if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]==0){
				//	matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=0.0;
				//	matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]=0.0;
				//	matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=0.0;
				//}
				//if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]>0){
				//	cout << "las particulas están en equilibrio" << endl;
				//	return EXIT_FAILURE;
				//}
				//if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]<0){
				//	cout << "las particulas están en equilibrio" << endl;
				//	return EXIT_FAILURE;
				//}
				//if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]==0){
				//	cout << "la energía está en equilibrio" << endl;
				//	return EXIT_FAILURE;
				//}
				//if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]==0){
				//	cout << "la energía está en equilibrio" << endl;
				//	return EXIT_FAILURE;
				//}
				//if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]<0){
				//	cout << "las partículas y la energía no tienen el mismo signo" << endl;
				//	return EXIT_FAILURE;
				//}
				//if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]>0){
				//	cout << "las partículas y la energía no tienen el mismo signo" << endl;
				//	return EXIT_FAILURE;
				//}
				restrictionsuma[i]=round(restrictionsuma[i])+round(matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]);
				restrictionenergysuma[i]=restrictionenergysuma[i]+matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1];
			}
			time=time+1.0;
		}
	}
	else if (functionform==1){ //Potencia
		for (int i=0; i<times; ++i){
			for (int j=0; j<totallines-1; ++j){
				if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]>0){
					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=(particlespercell-info[j][0])*(pow(i-t0,matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]));
					for (int k=0; k<energyspectre; ++k){
						matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*(pow(i-t0,(matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2])*vectorenergyspectre[k]));
					}
				}
				if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]<0){

					matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=(particlespercell-info[j][0])*(pow(i-t0,matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]));
					for (int k=0; k<energyspectre; ++k){			
						matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]=matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1]+(particlespercell-info[j][0])*(pow(i-t0,matrixinfo[info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]*vectorenergyspectre[k]));
					}
				}
				if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]==0){
			matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]=0.0;
				}
				if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]>0){
					cout << "las particulas están en equilibrio" << endl;
					return EXIT_FAILURE;
				}
				if (particlespercell-info[j][0]==0 && energypercell1-info[j][1]<0){
					cout << "las particulas están en equilibrio" << endl;
					return EXIT_FAILURE;
				}
				if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]==0){
					cout << "la energía está en equilibrio" << endl;
					return EXIT_FAILURE;
				}
				if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]==0){
					cout << "la energía está en equilibrio" << endl;
				}
				if (particlespercell-info[j][0]>0 && energypercell1-info[j][1]<0){
					cout << "las partículas y la energía no tienen el mismo signo" << endl;
					return EXIT_FAILURE;
				}
				if (particlespercell-info[j][0]<0 && energypercell1-info[j][1]>0){
					cout << "las partículas y la energía no tienen el mismo signo" << endl;
					return EXIT_FAILURE;
				}
				restrictionsuma[i]=restrictionsuma[i]+matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0];
				restrictionenergysuma[i]=restrictionenergysuma[i]+matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][1];
			}
			time=time+1.0;
		}
	}
	else if(functionform !=0 && functionform!=1){
		cout << "Invalid form" << endl;
		return EXIT_FAILURE;
		}
	for (int i=0; i<times; ++i){
		//cout << "restrictionsuma[" << i << "]= " << restrictionsuma[i] << endl;
	//	cout << "restrictionenergysuma[" << i << "]= " << restrictionenergysuma[i] << endl;
	}
	for (int i=0; i<times; ++i){
		for (int j=0; j<xdimension; ++j){
			for (int k=0; k<ydimension; ++k){
				for (int l=0; l<zdimension; ++l){
					cout << "matrixsimulation[" << i << "][" << j << "][" << k << "][" << l << "][" << 0 << "]= " << matrixsimulation[i][j][k][l][0] << endl; 
				}
			}
		}
	}
	return 0;
}
int Particletype::Exportdata(){
	cout << "vamos a imprimir datos" << endl;
	char name[]="outputdata.dat";
	ofstream outfile(name, ios::app);
	//for (int i=0; i<times; ++i){
		//for (int j=1; j<totallines; ++j){
	//	cout << "Matrixsimulation[" << i << "][0][0][2][0] = " << matrixsimulation[i][0][0][2][0] << endl;
		//}
	//}
	//outfile << "time" << " ";
	//for (int j=1; j<totallines; ++j){
	//	outfile << "C"i"_particles" << " " << "C"i"_energy" << " ";
	//}
	//outfile << "R"i"_particles" << " " << "R"i"_energy" << endl;
	for (int i=0; i<times; ++i){
		outfile << i << " ";
		for (int j=0; j<totallines-1; ++j){
			outfile << matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][0]  << " " << matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][2]<< " " << matrixsimulation[i][info1[j][0]-1][info1[j][1]-1][info1[j][2]-1][3]<< " ";
		}
		//outfile << restrictionsuma[i] << " " << restrictionenergysuma[i] << endl;
		outfile << endl;
		//outfile << endl;
	}
	outfile.close();
	char name1[]="restrictionsdata.dat";
	ofstream outfile1(name1, ios::app);
	for (int i=0; i<times; ++i){
		outfile1 << i << " " << restrictionsuma[i] << endl; //" " << restrictionenergysuma[i] << endl;
	}
	outfile1.close();
	return 0;
}
