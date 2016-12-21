#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
const int DIM=50;
//aaaaaaaa
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
	string codi;
	string model;
	int revisio;//0-Transit, 1-DiÃ ria
	int estat;//1-Pendent 2-Realitzat 3-Baixa
	data d;
	temps servei;
	temps acabat;
	int preu;
	string tecnic;
};
bool llegir_fitxer(tAvio avions[DIM], int& N,ifstream & dades){
	string linia;
	if(dades.is_open()){		
		int i=0;
		while(!dades.eof()){
			//Codi
			getline(dades,linia,';');
			avions[i].codi=linia;
			//Model
			getline(dades,linia,';');
			avions[i].model=linia;
			//RevisiÃ³
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
		N=i;
		return true;
	}
	else{
		return false;
	}
}
void escriure_avions(tAvio avions[],int N){
	for(int i=0;i<N;i++){
			cout<<"Avio: "<<i<<endl;
			cout<<"Codi: "<<avions[i].codi<<endl;
			cout<<"Model: "<<avions[i].model<<endl;
			cout<<"Revisio: "<<avions[i].revisio<<endl;
			cout<<"Estat: "<<avions[i].estat<<endl;
			cout<<"Data: "<<avions[i].d.dia<<" "<<avions[i].d.mes<< " " << avions[i].d.any <<endl;
			cout<<"Hora de Servei: "<<avions[i].servei.h<<" "<<avions[i].servei.m<<" "<<avions[i].servei.s<<endl;
			cout<<"Preu: "<<avions[i].preu<<endl;
			cout<<"Nom Tecnic: "<<avions[i].tecnic<<endl;
			}
}
bool mirar_num(string aux, int min, int max){
	int a=atoi(aux.c_str());
	if(a>=min && a<=max){
		return true;
	}
	else return false;
}
void mirar_string(string & aux){
	char a;
	cout<<"Es correcte?  Y/N";
	cin>>a;
	while(a!='Y' && a!='y'){
		cout<<"Torna a escriure"<<endl;
		cin>>aux;
		cout<<"Es correcte?  Y/N";
		cin>>a;
	}
}
void crear_avions(tAvio avions[],int & N){
	cout<<"Quants avions vols crear?";
	string aux;
	int k;
	cin>>k;
	for(int i=N;i<N+k;i++){
			cout<<"Avio: "<<i<<endl;
			cout<<"Codi: ";
				cin>>aux;
				mirar_string(aux);
				avions[i].codi=aux;
			cout<<"Model: ";
				cin>>aux;
				mirar_string(aux);
				avions[i].model=aux;
			cout<<"Revisio: 0-Transit�ria, 1-Di�ria";		cin>>avions[i].revisio;
			cout<<"Estat: 0-Pendent, 1-Realitzat, 2-Baixa";	cin>>avions[i].estat;
			cout<<"Data: Dia/Mes/Any";						cin>>avions[i].d.dia>>avions[i].d.mes>>avions[i].d.any;
			cout<<"Hora de Servei: HMS";					cin>>avions[i].servei.h>>avions[i].servei.m>>avions[i].servei.s;
			cout<<"Preu: ";									cin>> avions[i].preu;
			cout<<"Nom Tecnic:";
				cin>>aux;
				mirar_string(aux);
				avions[i].tecnic=aux;
			}
	N=N+k;
}

int main(){
	tAvio avions[DIM];
	int N;
	ifstream dades("dades.txt");
	
	//Llegir Fitxer
	if(llegir_fitxer(avions, N, dades)){
		cout<<"S'ha obert correctament"<<endl;
		escriure_avions(avions,N);
	}
	else{
		cout<<"No existeix el fitxer";
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
                //programa, accions, funcions	Crear
                crear_avions(avions,N);
                
                
                break;
                
            case 2:
                //programa, accions, funcions	Modificar
                break;
                
            case 3:
                //programa, accions, funcions	Eliminar
                break;
                
            case 4:
                //programa, accions, funcions	Mostrar Estad�stiques
                escriure_avions(avions,N);
                
                break;
                
            case 5:
                cout<<"Estas segur que vols sortir? Y/N"<<endl;
                char sortir;
                cin>>sortir;
                if(sortir!='Y' && sortir!='y')
                	opc=0;
				break;
            default:;
        }// fi switch
        
        
        dades.close();
    }//fi while
    

}
