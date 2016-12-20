#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

const int DIM=50;

struct temps{
	int h;
	int m;
	int s;
};
struct data{
	string dia;
	string mes;
	int any;
};
struct tAvio{
	int codi;
	string model;
	int revisio;//0-Transit, 1-Diària
	int estat;//1-Pendent 2-Realitzat 3-Baixa
	data d;
	temps servei;
	temps acabat;
	int preu;
	string tecnic;
};



int main(){
	tAvio avions[DIM];
	
	ifstream dades("dades.txt");
	string linia;
	int N;
	
	
	if(dades.is_open()){
		cout<<"Obert"<<endl;
		int i=0;
		while(!dades.eof()){
			//Codi
			getline(dades,linia,';');
			avions[i].codi=atoi(linia.c_str());
			//Model
			getline(dades,linia,';');
			avions[i].model=linia;
			//Revisió
			getline(dades,linia,';');
			avions[i].revisio=atoi(linia.c_str());
			//Estat
			getline(dades,linia,';');
			avions[i].estat=atoi(linia.c_str());
			//Data
			getline(dades,linia,';');
			avions[i].d.dia=linia;
			getline(dades,linia,';');
			avions[i].d.mes=linia;
			getline(dades,linia,';');
			avions[i].d.any=atoi(linia.c_str());
			//Hora Servei
			getline(dades,linia,';');
			avions[i].servei.h=atoi(linia.c_str());  //hores
			getline(dades,linia,';');
			avions[i].servei.m=atoi(linia.c_str());	//minuts
			getline(dades,linia,';');
			avions[i].servei.s=atoi(linia.c_str());	//segons
			//Preu
			getline(dades,linia,';');
			avions[i].preu=atoi(linia.c_str());
			//Nom Tecnic
			getline(dades,linia,';');
			avions[i].tecnic=linia;
			
			i++;
		}
		N=i-1;
		for(int i=0;i<N;i++){
			cout<<"Avio: "<<i<<endl;
			cout<<"Codi: "<<avions[i].codi<<endl;
			cout<<"Model: "<<avions[i].model<<endl;
			cout<<"Revisio: "<<avions[i].revisio<<endl;
			cout<<"Estat: "<<avions[i].estat<<endl;
			cout<<"Data: "<<avions[i].d.dia<<" "<<avions[i].d.mes<< " " << avions[i].d.any <<endl;
			cout<<"Hora de Servei: "<<avions[i].servei.h<<" "<<avions[i].servei.m<<" "<<avions[i].servei.s;
			cout<<"Preu: "<<avions[i].preu<<endl;
			cout<<"Nom Tecnic: "<<avions[i].tecnic<<endl;
			}
	}
	
	
	
	
	
	
	
	int opc;
	while (opc!=5){
        cout << "MENU D'OPCIONS:" << endl;
        cout << " 1. Crear " << endl;
        cout << " 2. Modificar " << endl;
        cout << " 3. Eliminar " << endl;
        cout << " 4. Mostrar estadistiques " << endl;
        cout << " 5. Sortir del programa " << endl;
        cout << "SELECCIONEU UNA OPCIO: " << endl;
        cin >> opc;
        
        switch (opc) {
                
            case 1:
                //programa, accions, funcions
                break;
                
            case 2:
                //programa, accions, funcions
                break;
                
            case 3:
                //programa, accions, funcions
                break;
                
            case 4:
                //programa, accions, funcions
                break;
                
            case 5:
                break;
                //el fatos ha sugerit fer una altra opció de guardar/descarregar el nou fitxer
                //les variables locals s'esborren!!!! cal declarar-les objectes del prog principal
                //no fer accions massa llargues
            default:;
        }// fi switch
        
    }//fi while
    

}
