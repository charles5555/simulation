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
	particlespercell=1000;
	energypercell=40;
	xdimension=3.0;
	ydimension=3.0;
	zdimension=3.0;
	cout << "no se introdujeron valores, procedemos a hacer la definición por default de los valoresde partículas por celda, energía por celda y el tamaño de la celda" << endl;
	cout << "Número de partículas por celda en equilibrio = " << particlespercell << endl;
	cout << "Energía por celda en el equilibrio = " << energypercell << endl;
	cout << "La malla tridimensional tendra una dimensión de " << xdimension << "X" << ydimension << "X" << zdimension << endl;
}
Particletype::Particletype(int particlespercell, int energypercell, double xdimension, double ydimension, double zdimension, int numberespectre){
	cout << "Se ha introducido los valores que se requieren" << endl;
	cout << "Número de partículas por celda en equilibrio (o potencial químico por cada celda)= " << particlespercell << endl;
	cout << "Energía por celda en el equilibrio (o temperatura por celda)= " << energypercell << endl;
	cout << "La malla tridimensional tendra una dimensión de " << xdimension << "X" << ydimension << "X" << zdimension << endl;
}
int Particletype::Generationdata(int particlespercell, int numberespectre, double xdimension, double ydimension, double zdimension) {
	//Generador de un número aleatorio entero.
	cout << particlespercell << endl;
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
	if (numberespectre ==0 ) { //Caso de espectro de energía continuo
	cout << "Ha elegido el caso del espectro de energía continuo" << endl;
	}
	else if (numberespectre ==1 ){ //Caso de espectro de energía discreto
		cout << "Ha elegido el caso de espectro de energía dicreto" << endl;
			
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
		int contador=1;
		char name[]="cellsdata.dat";
		ofstream outfile(name, ios::app);
		outfile << espectre << " "; //Guarda en el archivo cellsdata.dat en la primera entrada el número de estados energéticos accesibles
		for (int i=0; i<espectre; ++i){
			outfile << contador  << " ";
			contador=contador+1;  // Guarda cada uno de los estados accesibles sobre la primera fila
		}
		//cout << particlespercell << endl; 
		outfile << particlespercell << " "; // Guarda el número de partículas por celda (o el potencial químico) de las celdas en equilibrio.
		outfile << energypercell << endl; // Guarda la temperatura de las celdas en el equilibrio (o la energía).
		vectorcells.resize(static_cast<int>(xdimension));
		for (int i=0; i<static_cast<int>(xdimension); ++i){
			vectorcells[i].resize(static_cast<int>(ydimension));
		}
		for (int i=0; i<static_cast<int>(xdimension); ++i){
			for (int j=0; j<static_cast<int>(ydimension); ++j){
				vectorcells[i][j].resize(static_cast<int>(zdimension));
			}
		}
		constexpr int FLOAT_MIN1 = 1;
		constexpr int FLOAT_MAX1 = 10;
		constexpr int FLOAT_MIN = 200;
		constexpr int FLOAT_MAX = 300;
		random_device rd;
		default_random_engine eng(rd());
		uniform_real_distribution<float> distr1(FLOAT_MIN1, FLOAT_MAX1);
		uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
		//cout << "se generó la matriz" << endl;
		//cout << "xdimension= " << xdimension << endl;
		//cout << "ydimension= " << ydimension << endl;
		//cout << "zdimension= " << zdimension << endl;
		for (int i=0; i<static_cast<int>(xdimension); ++i){
			for (int j=0; j<static_cast<int>(ydimension); ++j){
				for (int k=0; k<static_cast<int>(zdimension); ++k){
					outfile << floor(distr1(eng)) << " " << floor(distr(eng)) << " " << i+1 << " " << j+1 << " " << k+1 << endl;
				}
			}
		}
		outfile.close();
	}
	return 0;
}
