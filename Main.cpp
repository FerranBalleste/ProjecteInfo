#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int DIM=50;

struct temps{
	int h;
	int m;
	int s;
};
struct data{
	int dia;
	int mes;
	int any;
};
struct tAvio{
	string codi;
	string model;
	int revisio;	//1-Transit, 2-Diaria
	int estat;		//1-Pendent 2-Realitzat 3-Baixa
	data d;
	temps servei;
	temps acabat;
	int preu;
	string tecnic;
};

void temps(struct tm *info,	int&dia,	int&	mes,int&any,int&hora,int&minuts,int&segons){
	time_t t;
	time(&t);		
	info = localtime(&t);
			
	dia	= info -> tm_mday;
	mes = info -> tm_mon+1;  //es suma +1 per a fer-ho de 1-12 enlloc de 0-11
	any	= 1900 + info -> tm_year;	//	l'any	es	comença	a	comptar	a	partir	del	1900
	hora = info	-> tm_hour;
	minuts = info -> tm_min;
	segons = info -> tm_sec;
}
bool llegir_fitxer(tAvio avions[DIM], int& N,ifstream & dades){
	string linia;
	if(dades.is_open()){		
		int i=0;
		while(!dades.eof()){	//Llegir fins al final del fitxer, no llegir si no hi ha res
			//Codi
			getline(dades,linia,';');
			avions[i].codi=linia;
			//Model
			getline(dades,linia,';');
			avions[i].model=linia;
			//Revisio
			getline(dades,linia,';');
			avions[i].revisio=atoi(linia.c_str());
			//Estat
			getline(dades,linia,';');
			avions[i].estat=atoi(linia.c_str());
			//Data
			getline(dades,linia,';');
			avions[i].d.dia=atoi(linia.c_str());
			getline(dades,linia,';');
			avions[i].d.mes=atoi(linia.c_str());
			getline(dades,linia,';');
			avions[i].d.any=atoi(linia.c_str());
			//Hora Servei
			getline(dades,linia,';');
			avions[i].servei.h=atoi(linia.c_str());  //hores
			getline(dades,linia,';');
			avions[i].servei.m=atoi(linia.c_str());	//minuts
			getline(dades,linia,';');
			avions[i].servei.s=atoi(linia.c_str());	//segons
			//Hora Servei
			getline(dades,linia,';');
			avions[i].acabat.h=atoi(linia.c_str());  //hores
			getline(dades,linia,';');
			avions[i].acabat.m=atoi(linia.c_str());	//minuts
			getline(dades,linia,';');
			avions[i].acabat.s=atoi(linia.c_str());	//segons
			//Preu
			getline(dades,linia,';');
			avions[i].preu=atoi(linia.c_str());
			//Nom Tecnic
			getline(dades,linia,';');
			avions[i].tecnic=linia;	
			i++;
		}
		N=i-1;    //Resta l'error de eof
		return true;
	}
	else{
		return false;
	}
}
void escriure_avions(tAvio avions[],int N, int inf){      //Mostra el contingut de la taula d'avions per pantalla
	for(int i=inf;i<N;i++){
			cout<<"Avio: "<<i+1<<endl;
			cout<<"Codi: "<<avions[i].codi<<endl;
			cout<<"Model: "<<avions[i].model<<endl;
			cout<<"Revisio: "<<avions[i].revisio<<endl;
			cout<<"Estat: "<<avions[i].estat<<endl;
			cout<<"Data: "<<avions[i].d.dia<<" "<<avions[i].d.mes<< " " << avions[i].d.any <<endl;
			cout<<"Hora de Servei: "<<avions[i].servei.h<<" "<<avions[i].servei.m<<" "<<avions[i].servei.s<<endl;
			cout<<"Acabat: "<<avions[i].acabat.h<<" "<<avions[i].acabat.m<<" "<<avions[i].acabat.s<<endl;
			cout<<"Preu: "<<avions[i].preu<<endl;
			cout<<"Nom Tecnic: "<<avions[i].tecnic<<endl<<endl;
			}
}
void obtenir_enter(int & input){
	while (!(cin >> input)) {
	    cin.clear();
	    cin.ignore(256, '\n');
	    cout << "No es un enter, torna a intentar:  ";
	}
}
void obtenir_enter_rang(int & input, int min, int max){
	obtenir_enter(input);
	while(input<min || input>max){
		cout << "No forma part del rang, torna a intentar:  ";
		obtenir_enter(input);
	}
}
void crear_avions(tAvio avions[],int & N){
	string str;  	//string auxiliar per no escriure directament
	int enter;		//enter auxiliar per no escriure directament i poder comprovar si es correcte
	struct tm *info_temps;
	int dia,mes,any,hora,minuts,segons;
	
	cout<<"Quants avions vols crear?";
	int k;
	cin>>k;
	
	for(int i=N;i<N+k;i++){
			cout<<"Avio: "<<i+1<<endl;
			cout<<"Codi: ";
				cin.ignore();
				getline(cin,str);
				avions[i].codi=str;
			cout<<"Model: ";
				getline(cin,str);
				avions[i].model=str;
			cout<<"Revisio: (1-Transitòria, 2-Diària)	";		
				obtenir_enter_rang(enter,1,2);
				avions[i].revisio=enter;
			cout<<"Estat: (1-Pendent, 2-Realitzat, 3-Baixa)		";
				obtenir_enter_rang(enter,1,3);
				avions[i].estat=enter;
			//Dia,mes i any amb llibreria time.h
				temps(info_temps,dia,mes,any,hora,minuts,segons);
				avions[i].d.dia=dia;
				avions[i].d.mes=mes;
				avions[i].d.any=any;
			cout<<"Hora de Servei: (HMS) 		";
				obtenir_enter_rang(enter,0,23);
				avions[i].servei.h=enter;
				obtenir_enter_rang(enter,0,59);
				avions[i].servei.m=enter;
				obtenir_enter_rang(enter,0,59);
				avions[i].servei.s=enter;			
			cout<<"Acabat: (HMS) 		";
				obtenir_enter_rang(enter,0,23);
				avions[i].acabat.h=enter;
				obtenir_enter_rang(enter,0,59);
				avions[i].acabat.m=enter;
				obtenir_enter_rang(enter,0,59);
				avions[i].acabat.s=enter;
			cout<<"Preu: ";
				obtenir_enter(enter);
				avions[i].preu=enter;
			cout<<"Nom Tecnic:"; 
				cin.ignore();
				getline(cin,str);
				avions[i].tecnic=str;
			}
	N=N+k;
}
void igualar_taula(tAvio avions[],int b , int a){ //a = posicio inicial, b = posicio final
	avions[b].codi=avions[a].codi;
	avions[b].model=avions[a].model;
	avions[b].revisio=avions[a].revisio;
	avions[b].estat=avions[a].estat;
	avions[b].d.dia=avions[a].d.dia;
	avions[b].d.mes=avions[a].d.mes;
	avions[b].d.any=avions[a].d.any;
	avions[b].servei.h=avions[a].servei.h;
	avions[b].servei.m=avions[a].servei.m;
	avions[b].servei.s=avions[a].servei.s;
	avions[b].acabat.h=	avions[a].acabat.h;
	avions[b].acabat.m=avions[a].acabat.m;
	avions[b].acabat.s=avions[a].acabat.s;
	avions[b].preu=avions[a].preu;
	avions[b].tecnic=avions[a].tecnic;
}
void ordenar(tAvio avions[],int N, int opcio){    //Ordenacio per Seleccio
	int min; //Index del valor més petit
	for(int i=0;i<N-1;i++){
		min=i;
		if(opcio==1){						//Codi
			for(int k=i+1;k<N;k++){
				if(avions[k].codi<avions[min].codi)
					min=k;
			}
		}else if(opcio==2){					//Model
			for(int k=i+1;k<N;k++){
				if(avions[k].model<avions[min].model)
					min=k;
			}
		}
		if(min>i){
			igualar_taula(avions,N+1,min); //S'agafa la posició N+1 com a auxiliar per no crear una altra taula
			igualar_taula(avions,min,i);
			igualar_taula(avions,i,N+1);
		}
	}
}
int cerca(tAvio avions[],int N,int opcio,int enter,string str){	//Cerca dicotòmica
	int centre, inf=0, sup=N-1;
	while(inf<=sup){
		centre=(sup+inf)/2;
		if(opcio==1){
			if(avions[centre].codi==str){   //cerca codi
				escriure_avions(avions,centre,centre);
				cout<<"S'ha trobat l'avio:"<<endl<<endl;
				return centre;
			}else if(str < avions[centre].codi ){
		    	sup=centre-1;
		    }else {
		       inf=centre+1;
		     }
		}else if(opcio==2){
			if(avions[centre].model==str){	//cerca model
				escriure_avions(avions,centre,centre);
				cout<<"S'ha trobat l'avio:"<<endl<<endl;
				return centre;
			}else if(str < avions[centre].model ){
		    	sup=centre-1;
		    }else {
		       inf=centre+1;
		    }
		}
	}
	return -1;
}
void eliminar_element(tAvio avions[], int & N, int c){  //c = posició de l'element a eliminar
	cout<<"Segur que el vols eliminar? (Y/N)"<<endl;
	char opcio;
    cin>>opcio;
    if(opcio=='Y' || opcio=='y'){
    	for(int i=c-1; i<N; i++){
			igualar_taula(avions,i,i+1);
		}
		N=N-1;
		cout<<"Avio eliminat, per guardar surti del programa a partir del menu principal"<<endl<<endl;
	}
	else{
       	cout<<"No s'ha eliminat"<<endl<<endl;
    }
}
void guardar(tAvio avions[], int N, ofstream & dades){
	for(int i=0; i<N; i++){
		dades << avions[i].codi << ';';
		dades << avions[i].model << ';';
		dades << avions[i].revisio << ';';
		dades << avions[i].estat << ';';
		dades << avions[i].d.dia << ';';
		dades << avions[i].d.mes << ';';
		dades << avions[i].d.any << ';';
		dades << avions[i].servei.h << ';';
		dades << avions[i].servei.m << ';';
		dades << avions[i].servei.s << ';';
		dades << avions[i].acabat.h << ';';
		dades << avions[i].acabat.m << ';';
		dades << avions[i].acabat.s << ';';
		dades << avions[i].preu << ';';
		dades << avions[i].tecnic << ';';
		
	}
}
void modificar_avio(tAvio avions[],int i){
    
    int opc3;
    string str;
    int enter;
    
    while (opc3!=9){
        
        cout<< "Escull el criteri a modificar:" << endl;
        cout <<" 1.Codi " << endl; cout <<" 2.Model " << endl;
        cout <<" 3.Revisio " << endl; cout <<" 4.Estat " << endl;
        cout <<" 5.Data " << endl; cout <<" 6.Hora de servei " << endl;
        cout <<" 7.Acabat " << endl; cout <<" 8.Preu " << endl;
        cout <<" 9.Nom Tecnic " << endl;
        
        cin >> opc3;
        cout << endl;
        
        switch(opc3){
                
            case 1:
                cout << "Codi: " << endl;
                cin >> str;
                avions[i].codi=str;
                break;
                
            case 2:
                cout << "Model: " << endl;
                cin >> str;
                avions[i].codi=str;
                break;
            case 3:
                cout << "Revisio: (1-Transitoria, 2-Diaria)" << endl;
                obtenir_enter_rang(enter, 1, 2);
                avions[i].revisio=enter;
                break;
            case 4:
                cout << "Estat: " << endl;
                obtenir_enter_rang(enter, 1, 3);
                avions[i].estat=enter;
                break;
            case 5:
                cout << "Data:";
                obtenir_enter_rang(enter, 1, 31);
                avions[i].d.dia=enter;
                obtenir_enter_rang(enter, 1, 12);
                avions[i].d.mes=enter;
                obtenir_enter_rang(enter, 2000, 2200);
                avions[i].d.any=enter;
                break;
            case 6:
                cout << "Hora de Servei (hms): ";
                obtenir_enter_rang(enter, 0, 23);
                avions[i].servei.h=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].servei.m=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].servei.s=enter;
                break;
            case 7:
                cout << "Acabat (hms): ";
                obtenir_enter_rang(enter, 0, 23);
                avions[i].acabat.h=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].acabat.m=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].acabat.s=enter;
                break;
            case 8:
                cout << "Preu: ";
                obtenir_enter(enter);
                avions[i].preu=enter;
                break;
            case 9:
                cout << "Nom Tècnic";
                cin >> str;
                avions[i].tecnic=str;
                break;
        }
    }
        
}
int main(){
	tAvio avions[DIM];
	int N;
	ifstream indades("dades.txt");
	ofstream ofdades("dades2.txt");
	
	//Llegir Fitxer
	if(llegir_fitxer(avions, N, indades)){
		cout<<"S'ha obert correctament"<<endl;
		cout<<endl;
	}
	else{
		cout<<"No existeix el fitxer dades.txt";
	}
		
	int opc,opc2,pos;  //opc s'utilitza en el menu principal, opc2 en el secundari, pos es auxiliar
	int ebuscar;
    string sbuscar;
	
	while (opc!=5){
        cout << "MENU D'OPCIONS:" << endl;
        cout << " 1. Crear " << endl;
        cout << " 2. Modificar " << endl;
        cout << " 3. Eliminar " << endl;
        cout << " 4. Mostrar estadistiques " << endl;
        cout << " 5. Sortir del programa " << endl;  
        cout << "SELECCIONEU UNA OPCIO: " << endl;
        cin >> opc;
        cout<<endl;
        
        switch (opc) {
                
            case 1:
                //programa, accions, funcions	Crear
                crear_avions(avions,N);
                
                
                break;
                
            case 2:
                //programa, accions, funcions	Modificar
                cout<<"Criteri de busca per trobar avio a modificar: "<<endl;
                cout<<"1.Codi"<<endl;
                cout<<"2.Model"<<endl;
                cout<<"3.Preu"<<endl;
                cout<<"4.Mostrar tots els avions sense ordenar"<<endl;
                obtenir_enter_rang(opc2,1,4);
                switch(opc2){
					case 1:
						cout<<"Introdueix el codi a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,1,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat l'avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							modificar_avio(avions,pos);
						}
						break;
					case 2:
						cout<<"Introdueix el model a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,2,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat l'avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							modificar_avio(avions,pos);
						}
						break;
					case 3:
				
						break;
					case 4:
						break;
					default:;
				}
                break;
                
            case 3:
                //programa, accions, funcions	Eliminar
                cout<<"Criteri de busca per trobar avio a eliminar: "<<endl;
                cout<<"1.Codi"<<endl;
                cout<<"2.Model"<<endl;
                cout<<"3.Preu"<<endl;
                cout<<"4.Mostrar tots els avions sense ordenar"<<endl;
                obtenir_enter_rang(opc2,1,4);
                switch(opc2){
					case 1:
						cout<<"Introdueix el codi a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,1,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat l'avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							eliminar_element(avions,N,pos+1);  //la funcio eliminar conta la posició a partir de 1
						}
						break;
					case 2:
						cout<<"Introdueix el model a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,2,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat l'avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							eliminar_element(avions,N,pos+1);  //la funcio eliminar conta la posició a partir de 1
						}
						break;
					case 3:
						break;
					case 4:
						escriure_avions(avions,N,0);
						cout<<"Introduir posicio de l'avio a eliminar: ";
						cin>>pos;
						eliminar_element(avions,N,pos);
						break;
					default:;
				}
                break;
                
            case 4:
                //programa, accions, funcions	Mostrar Estadístiques
                escriure_avions(avions,N,0);
                
                break;
                
            case 5:
                cout<<"Estas segur que vols sortir? (Y/N)"<<endl;
                char sortir;
                cin>>sortir;
                if(sortir!='Y' && sortir!='y')
                	opc=0;
                else{
               		guardar(avions, N, ofdades);
               		cout<<"S'ha guardat correctament";
            	}
				break;
            default:;
        }// fi switch
        
        
        
    }//fi while
    
indades.close();
ofdades.close();
}
