#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
#include "boxcounting.h"
Boxcountingfractaldimension::Boxcountingfractaldimension(){
	cout << "the program is starting" << endl;
}
Particletype::Particletype(){
	m=10;
}
Particletype::Particletype(int tama){
	m=tama;
}
int Particletype::Openfileandsavedata() {
	//int count;
	string line;
	//string Load;
	count=0;
	xmin=1.0e+100;
	xmax=-1.0e+100;
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
	//double **matrixinfo= new double*[count];
	//vector<vector<double> > matrixinfo(count);
	matrixinfo.resize(count);
	for (int i=0; i<count; ++i){
		//matrixinfo[i] = new double[3];
		matrixinfo[i].resize(2);
		}
	inFile.clear();
	inFile.seekg(0);
	for (int i=0; i<count; ++i){
		//matrixinfo[i][0]=i+1;
		inFile >> matrixinfo[i][0] >> matrixinfo[i][1];
		if (matrixinfo[i][0] < xmin){xmin=matrixinfo[i][0]; }
		if (matrixinfo[i][0] > xmax){xmax=matrixinfo[i][0]; }
		if (matrixinfo[i][1] < ymin){ymin=matrixinfo[i][1]; }
		if (matrixinfo[i][1] > ymax){ymax=matrixinfo[i][1]; }
	}
	
	inFile.close();
	//for (int i=0; i<count; ++i){
	//	for (int j=0; j<2; ++j){
	//		cout << "la entrada matrixinfo["<< i <<"]["<< j <<"] es: "<< matrixinfo[i][j] << endl;  
	//	}
	//}
	cout << "xmin= " << abs(xmin) << endl;
	cout << "xmax= " << xmax << endl;
	cout << "ymin= " << abs(ymin) << endl;
	cout << "ymax= " << ymax << endl;
	//for (int i=0; i<count; ++i){
		//delete [] matrixinfo[i];
	//	matrixinfo[i].clear();
	//}
	//delete [] matrixinfo;
	//matrixinfo.clear();
	return 0;
}
int Particletype::Sortdata(){
	malla.resize(m);
	for (int i=0; i<m; ++i){
		malla[i].resize(m);
	}
	for (int i=0; i<count; ++i){
		matrixinfo[i][0]=matrixinfo[i][0]+abs(xmin);
		matrixinfo[i][1]=matrixinfo[i][1]+abs(ymin);
	}
	
	for (int i=0; i<count; ++i){
		for (int j=0; j<2; ++j){
			if (matrixinfo[i][j]<0){
				cout << "There is a value less than zero" << endl;
				return EXIT_FAILURE;
			}
		//	cout << "la entrada matrixinfo["<< i <<"]["<< j <<"] es: "<< matrixinfo[i][j] << endl;  
		}
	}
	xmax=xmax+abs(xmin);
	ymax=ymax+abs(ymin);
	cout << "xmax= " << xmax << endl;
	cout << "ymax= " << ymax << endl;
	double deltax=xmax/m;
	double deltay=ymax/m;
	double segmentox=xmax/m;
	cout << "segmentox: " << segmentox << endl;
	double segmentoy=ymax/m;
	cout << "segmentoy: " << segmentoy << endl;
	std::vector<bool> key(count, false);
	//key.resize(count);
	//for (int i=0; i<count; i++){
	//	key[i]=false;			
	//}
	//for (int i=0; i<4; ++i){
	//	cout << "key[" << i << "] es: " << key[i] << endl;
	//}
	for (int i=0; i<m; i++){
		for (int j=0; j<m; j++){
			for (int k=0; k<count; k++){
			//	cout << "segmento*(i)= " << segmento*(i) << endl;
				if (!key[k]){
					
			//	cout << "malla[" << i << "][" << j << "]= " << malla[i][j] << endl;
			//	cout << "matrixinfo[" << k << "][0]= " << matrixinfo[k][0] << endl;
					if (matrixinfo[k][0]>=segmentox*(i) && matrixinfo[k][0]<=segmentox*(i+1)){
			//			cout << "matrixinfo[" << k << "][1]= " << matrixinfo[k][1] << endl;
						if (matrixinfo[k][1]>=segmentoy*(j) && matrixinfo[k][1]<=segmentoy*(j+1)){
							malla[i][j]=malla[i][j]+1;
							key[k]=true;
						}
					}					
				}
			}
		}
	}
	int total=0;
	for (int i=0; i<m; ++i){
		for (int j=0; j<m; ++j){
		//	cout << "en la caja [" << i << "][" << j << "] hay " << malla[i][j] << " partículas" << endl;
			total=total+malla[i][j];	
		}
	}
	//for (int i=0; i<count; ++i){
	//	cout << key[i] << endl;
	//}
	cout << "el número total de partículas es: " << total << endl;
	int totcajas=0;
	for (int i=0; i<m; i++){
		for (int j=0; j<m; j++){
			//cout << "malla[" << i << "][" << j << "]= " << malla[i][j] << endl;
			if (malla[i][j]!=0){ totcajas=totcajas+1;}
			//cout << "totcajas= " << totcajas << endl;
		}
	}
	cout << "El número necesario de cajas para cubrir el cluster es de: " << totcajas << " cajas" << endl;	
	return 0;
}
	
