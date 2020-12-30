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
	m=1;
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

	inFile.open("cluster-2e5.dat");
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
	int ty;
	int totcajas;
	double deltax, deltay, segmentox, segmentoy, total,xmaxp, ymaxp;
	cout << "Choose one method to calculate fractal dimension:" << endl;
	cout << "Box counting, type 1" << endl;
	cout << "Exit, type 0" << endl;
	cin >> ty;
	//std::vector<vector<double> > matrixinfocopy;
	matrixinfocopy.resize(count);
	for (int i=0; i<count; i++){
		matrixinfocopy[i].resize(2);
	}
	if (ty==1){
		//for (int l=0; l<15; ++l){	
			malla.resize(m);
			for (int i=0; i<m; ++i){
				malla[i].resize(m);
			}
			for (int i=0; i<count; ++i){
				matrixinfocopy[i][0]=matrixinfo[i][0]+abs(xmin);
				matrixinfocopy[i][1]=matrixinfo[i][1]+abs(ymin);
			}
	
			for (int i=0; i<count; ++i){
				for (int j=0; j<2; ++j){
					if (matrixinfocopy[i][j]<0){
						cout << "There is a value less than zero" << endl;
						return EXIT_FAILURE;
					}
			//		cout << "la entrada matrixinfocopy["<< i <<"]["<< j <<"] es: "<< matrixinfocopy[i][j] << endl;  
				}
			}
			xmaxp=xmax;
			ymaxp=ymax;
			xmaxp=xmaxp+abs(xmin);
			ymaxp=ymaxp+abs(ymin);
			int indicex=0;
			int indicey=0;
			cout << "xmaxp= " << xmaxp << endl;
			cout << "ymaxp= " << ymaxp << endl;
		        deltax=xmaxp/m;
			deltay=ymaxp/m;
			segmentox=xmaxp/m;
			cout << "segmentox: " << segmentox << endl;
			segmentoy=ymaxp/m;
			cout << "segmentoy: " << segmentoy << endl;
			//key(count, false);
			//for (int i=0; i<count; i++){
			//	key.push_back(false);
			//}
			//key.resize(count);
			//for (int i=0; i<count; i++){
			//	key[i]=false;			
			//}
			//std::vector<bool> key(count, false);
			//for (int i=0; i<4; ++i){
			//	cout << "key[" << i << "] es: " << key[i] << endl;
			//}
			for (int i=0; i<count; i++){
				indicex=0;
				indicey=0;
				//preindicex=matrixinfocopy[i][0]/segmentox;
				//preindicey=matrixinfocopy[i][1]/segmentoy;
				indicex=floor((matrixinfocopy[i][0])/(segmentox));
				indicey=floor((matrixinfocopy[i][1])/(segmentoy));
				if (indicex==m){indicex=indicex-1;}
				if (indicey==m){indicey=indicey-1;}
				//cout << "El contador es " << i << endl;
				//cout << "indicex= " << indicex << endl;
				//cout << "indicey= " << indicey << endl;
				malla[indicex][indicey]=malla[indicex][indicey]+1;
				//for (int j=0; j<m; j++){
					//for (int k=0; k<count; k++){
					////	cout << "segmento*(i)= " << segmento*(i) << endl;
						//if (!key[k]){
					
					////	cout << "malla[" << i << "][" << j << "]= " << malla[i][j] << endl;
					////	cout << "matrixinfocopy[" << k << "][0]= " << matrixinfocopy[k][0] << endl;
							//if (matrixinfocopy[k][0]>=segmentox*(i) && matrixinfocopy[k][0]<=segmentox*(i+1)){
					////			cout << "matrixinfocopy[" << k << "][1]= " << matrixinfocopy[k][1] << endl;
								//if (matrixinfocopy[k][1]>=segmentoy*(j) && matrixinfocopy[k][1]<=segmentoy*(j+1)){
									//malla[i][j]=malla[i][j]+1;
									//key[k]=true;
								//}
							//}					
						//}
					//}
				//}
			}
			total=0;
			for (int i=0; i<m; ++i){
				for (int j=0; j<m; ++j){
					//cout << "en la caja [" << i << "][" << j << "] hay " << malla[i][j] << " partículas" << endl;
					total=total+malla[i][j];	
				}
			}
			//for (int i=0; i<count; ++i){
			//	cout << key[i] << endl;
			//}
			cout << "el número total de partículas es: " << total << endl;
		        totcajas=0;
			for (int i=0; i<m; i++){
				for (int j=0; j<m; j++){
					//cout << "malla[" << i << "][" << j << "]= " << malla[i][j] << endl;
					if (malla[i][j]!=0){ totcajas=totcajas+1;}
					//cout << "totcajas= " << totcajas << endl;
				}
			}
			cout << "El número necesario de cajas para cubrir el cluster es de: " << totcajas << " cajas" << endl;	
			//m=m-(l+1);
			//delete [] malla;
			malla.clear();

			//delete [] key;
			//key.clear();

			//delete [] matrixinfocopy;
			matrixinfocopy.clear();
			
		//}
		return 0;
	}
	else if (ty==0){return EXIT_FAILURE;}
	else {return EXIT_FAILURE;}
}	
