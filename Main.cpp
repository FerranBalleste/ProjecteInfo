#include <iostream>
#include <fstream>
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
};



int main(){
	ifstream dades("dades.txt");
	string linia;
	
	
	if(dades.is_open()){
		cout<<"Obert"<<endl;
		int i=0;
		while(!dades.eof()){
			getline(dades,linia,';');
			cout<< linia;
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
