#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>
#include "random_data.h"
#include <random>
#include <iomanip>
using namespace std;

Randomgenerationdata::Randomgenerationdata(){
 cout << "the program is starting" << endl;
}
Particletype::Particletype(){
	particlespercell=1000.0; //potencial químico de las celdas en equilibrio
	energypercell=40; //temperatura de las celdas en equilibrio
	xdimension=3;
	ydimension=3;
	zdimension=3;
	cout << "no se introdujeron valores, procedemos a hacer la definición por default de los valoresde partículas por celda, energía por celda y el tamaño de la celda" << endl;
	cout << "Número de partículas por celda en equilibrio = " << particlespercell << endl;
	cout << "Energía por celda en el equilibrio = " << energypercell << endl;
	cout << "La malla tridimensional tendra una dimensión de " << xdimension << "X" << ydimension << "X" << zdimension << endl;
}
Particletype::Particletype(double particlespercell, int energypercell, int xdimension, int ydimension, int zdimension, int numberespectre){
	cout << "Se ha introducido los valores que se requieren" << endl;
	cout << "Potencial químico por celda en equilibrio= " << particlespercell << endl;
	cout << "Temperatura por celda en el equilibrio= " << energypercell << endl;
	cout << "La malla tridimensional tendra una dimensión de " << xdimension << "X" << ydimension << "X" << zdimension << endl;
}
int Particletype::Generationdata(double particlespercell, int energypercell, int numberespectre, int xdimension, int ydimension, int zdimension) {
	//Generador de un número aleatorio entero.
	cout << energypercell << endl;
	srand(time(NULL));
	randomnumint = 1+rand()%(101-1); 
	cout << "El numero aleatorio entero generado es = " << randomnumint << endl;
	//Generador de un número aleatorio flotante.
	//constexpr int FLOAT_MIN = 10;
	//constexpr int FLOAT_MAX = 100;
	//random_device rd;
	//default_random_engine eng(rd());
	//uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
	//randomnumdouble = floor(distr(eng));
	//cout << setprecision(10)
	//     << distr(eng) << endl;
	//cout << "El número aleatorio doble generado es = " << randomnumdouble << endl;
	cout << numberespectre << endl;
	if (numberespectre ==0 ) { //Caso de Fermi
	cout << "Ha elegido el caso de Fermi-Dirac" << endl;
		cout << "Ingrese el número de niveles de energía que puede tener el sistema" << endl;
		cin >> espectre;
		if (espectre == 0){
			cout << "No existe un espectro de energía nulo, no se puede continuar" << endl;
			return EXIT_FAILURE;
		}
		if (espectre < 0){
			cout << "No existen valores negativos para el espectro de energías, no se puede continuar." << endl;
			return EXIT_FAILURE;
		}
		int contador;
		cout << "Introduzca desde qué valor quiere empezar los niveles energéticos (iran de uno en uno aumentando su valor) " << endl;
		cin >> contador;
		int contador1=contador;
		char name[]="cellsdata.dat";
		ofstream outfile(name, ios::app);
		outfile << espectre << " "; //Guarda en el archivo cellsdata.dat en la primera entrada el número de estados energéticos accesibles
		for (int i=0; i<espectre; ++i){
			outfile << contador1  << " ";
			contador1=contador1+1;  // Guarda cada uno de los estados accesibles sobre la primera fila
		}
		//cout << particlespercell << endl; 
		double boltzmannconstant=8.6173e-5;
		double beta=1/(boltzmannconstant*energypercell);
		double temperatureenergy=0.0 ;
		double potentialnumber=0.0 ;
		contador1=contador;
		for (int i=0; i<espectre; ++i){
			//potentialnumber=round(potentialnumber)+round((exp(beta*(particlespercell-(contador1))))/(1+exp(beta*(particlespercell-(contador1)))));
			potentialnumber=round(potentialnumber)+round(1/(1+exp(beta*(-particlespercell+(contador1)))));
			temperatureenergy=temperatureenergy-((particlespercell-(contador1))*exp(beta*(particlespercell-(contador1))))/(1+exp(beta*(particlespercell-(contador1))));
		contador1=contador1+1;
		}
		outfile << potentialnumber << " " << temperatureenergy << " " << energypercell << " " << particlespercell << endl; // Guarda el número de partículas en equilibrio, la energía en equilibrio, la temperatura de la celda y el potencial químico de la celda.
		//vectorcells.resize(xdimension);
		//for (int i=0; i<xdimension; ++i){
		//	vectorcells[i].resize(ydimension);
		//}
		//for (int i=0; i<xdimension; ++i){
		//	for (int j=0; j<ydimension; ++j){
		//		vectorcells[i][j].resize(zdimension);
		//	}
		//}
		outfile << xdimension << " " << ydimension << " " << zdimension << " " << 0 << " " << 0 << endl;
		double potential;
		double temperature;
		double particlenumber=0.0;
		double energynumber=0.0;
		double beta1;
		double minpart=particlespercell-1.0;
		double maxpart=particlespercell+1.0;
		double minener=energypercell-10.0;
		double maxener=energypercell+10.0;
		contador1=contador;
		int FLOAT_MIN1 = minpart;
		int FLOAT_MAX1 = maxpart;
		int FLOAT_MIN = minener;
		int FLOAT_MAX = maxener;
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<float> distr1(FLOAT_MIN1, FLOAT_MAX1);
		uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
		//cout << "se generó la matriz" << endl;
		//cout << "xdimension= " << xdimension << endl;
		//cout << "ydimension= " << ydimension << endl;
		//cout << "zdimension= " << zdimension << endl;
		for (int i=0; i<xdimension; ++i){
			for (int j=0; j<ydimension; ++j){
				for (int k=0; k<zdimension; ++k){
					potential=floor(distr1(eng));
					temperature=floor(distr(eng));
					beta1=1/(boltzmannconstant*temperature);
					for (int i=0; i<espectre; ++i){
			particlenumber=round(particlenumber)+round((exp(beta1*(potential-(contador1))))/(1-exp(beta1*(potential-(contador1)))));
			energynumber=energynumber-((potential-(contador1))*exp(beta1*(potential-(contador1))))/(1-exp(beta1*(potential-(contador1))));
		contador1=contador1+1;
		}
					outfile << particlenumber << " " << energynumber << " " << temperature  << " " << potential  << " " << i+1 << " " << j+1 << " " << k+1 << endl;
				}
			}
		}
		outfile.close();
		return 0;
	}

	else if (numberespectre ==1 ){ //Caso de Bose
		cout << "Ha elegido el caso de Bose-Einstein" << endl;
			
		cout << "Ingrese el número de niveles de energía que puede tener el sistema" << endl;
		cin >> espectre;
		if (espectre == 0){
			cout << "No existe un espectro de energía nulo, no se puede continuar" << endl;
			return EXIT_FAILURE;
		}
		if (espectre < 0){
			cout << "No existen valores negativos para el espectro de energías, no se puede continuar." << endl;
			return EXIT_FAILURE;
		}
		int contador;
		cout << "Introduzca desde qué valor quiere empezar los niveles energéticos (iran de uno en uno aumentando su valor) " << endl;
		cin >> contador;
		int contador1=contador;
		char name[]="cellsdata.dat";
		ofstream outfile(name, ios::app);
		outfile << espectre << " "; //Guarda en el archivo cellsdata.dat en la primera entrada el número de estados energéticos accesibles
		for (int i=0; i<espectre; ++i){
			outfile << contador1  << " ";
			contador1=contador1+1;  // Guarda cada uno de los estados accesibles sobre la primera fila
		}
		//cout << particlespercell << endl; 
		double boltzmannconstant=8.6173e-5;
		double beta=1/(boltzmannconstant*energypercell);
		double temperatureenergy=0.0 ;
		double potentialnumber=0.0 ;
		contador1=contador;
		cout << energypercell;
		for (int i=0; i<espectre; ++i){
			//potentialnumber=potentialnumber+(exp(beta*(particlespercell-(contador1))))/(1-exp(beta*(particlespercell-(contador1))));
			potentialnumber=potentialnumber+(1/(-1+exp(beta*(-particlespercell+(contador1)))));
			temperatureenergy=temperatureenergy-((particlespercell-(contador1))*exp(beta*(particlespercell-(contador1))))/(1-exp(beta*(particlespercell-(contador1))));
		contador1=contador1+1;
		}
		outfile << potentialnumber << " " << temperatureenergy << " " << energypercell << " " << particlespercell << endl; // Guarda el número de partículas en equilibrio, la energía en equilibrio, la temperatura de la celda y el potencial químico de la celda.
		//vectorcells.resize(xdimension);
		//for (int i=0; i<xdimension; ++i){
		//	vectorcells[i].resize(ydimension);
		//}
		//for (int i=0; i<xdimension; ++i){
		//	for (int j=0; j<ydimension; ++j){
		//		vectorcells[i][j].resize(zdimension);
		//	}
		//}
		outfile << xdimension << " " << ydimension << " " << zdimension << " " << 0 << " " << 0 << endl;
		double potential;
		double temperature;
		double particlenumber=0.0;
		double energynumber=0.0;
		double beta1;
		contador1=contador;
		int FLOAT_MIN1 = particlespercell-1;
		int FLOAT_MAX1 = particlespercell+1;
		int FLOAT_MIN = energypercell-10;
		int FLOAT_MAX = energypercell+10;
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<float> distr1(FLOAT_MIN1, FLOAT_MAX1);
		uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
		//cout << "se generó la matriz" << endl;
		//cout << "xdimension= " << xdimension << endl;
		//cout << "ydimension= " << ydimension << endl;
		//cout << "zdimension= " << zdimension << endl;
		for (int i=0; i<xdimension; ++i){
			for (int j=0; j<ydimension; ++j){
				for (int k=0; k<zdimension; ++k){
					potential=distr1(eng);
					temperature=distr(eng);
					beta1=1/(boltzmannconstant*temperature);
					for (int i=0; i<espectre; ++i){
			particlenumber=round(particlenumber)+round((exp(beta1*(potential-(contador1))))/(1-exp(beta1*(potential-(contador1)))));
			energynumber=energynumber-((potential-(contador1))*exp(beta1*(potential-(contador1))))/(1-exp(beta1*(potential-(contador1))));
		contador1=contador1+1;
		}
					outfile << particlenumber << " " << energynumber << " " << temperature  << " " << potential  << " " << i+1 << " " << j+1 << " " << k+1 << endl;
				}
			}
		}
		outfile.close();
		return 0;
	}
}
