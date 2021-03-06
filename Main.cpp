#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int DIM=40;

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
struct tApi{
	string mod; //Tipus de modificaci�
	string codi;
	string model;
	data d;
	temps registre;
};

void temps(struct tm *info,	int&dia,int&mes,int&any,int&hora,int&minuts,int&segons){
	time_t t;
	time(&t);		
	info = localtime(&t);
			
	dia	= info -> tm_mday;
	mes = info -> tm_mon+1;  //es suma +1 per a fer-ho de 1-12 enlloc de 0-11
	any	= 1900 + info -> tm_year;	//	l'any	es	comenca	a	comptar	a	partir	del	1900
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
			//Hora Acabat
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
		dades.close();
		return true;
	}
	else{
		return false;
	}
}
bool llegir_api(tApi api[DIM], int& A, ifstream & ifapi){
	string linia;
	if(ifapi.is_open()){		
		int i=0;
		while(!ifapi.eof()){	//Llegir fins al final del fitxer, no llegir si no hi ha res
			//Tipus de canvi/modificaci�
			getline(ifapi,linia,';');
			api[i].mod=linia;
			//Codi
			getline(ifapi,linia,';');
			api[i].codi=linia;
			//Model
			getline(ifapi,linia,';');
			api[i].model=linia;
			//Data del registre
			getline(ifapi,linia,';');
			api[i].d.dia=atoi(linia.c_str());
			getline(ifapi,linia,';');
			api[i].d.mes=atoi(linia.c_str());
			getline(ifapi,linia,';');
			api[i].d.any=atoi(linia.c_str());
			//Hora Registre
			getline(ifapi,linia,';');
			api[i].registre.h=atoi(linia.c_str());  //hores
			getline(ifapi,linia,';');
			api[i].registre.m=atoi(linia.c_str());	//minuts
			getline(ifapi,linia,';');
			api[i].registre.s=atoi(linia.c_str());	//segons

			i++;
		}
		A=i-1;    //Resta l'error de eof
		ifapi.close();
		return true;
	}
	else{
		return false;
	}
}
void escriure_avions(tAvio avions[],int N, int inf){      //Mostra el contingut de la taula d'avions per pantalla, de inf a N
	int a;
	for(int i=inf;i<N;i++){
			cout<<"Avio: "<<i+1<<endl;
			cout<<"Codi: "<<avions[i].codi<<endl;
			cout<<"Model: "<<avions[i].model<<endl;
			cout<<"Revisio: ";
			a=avions[i].revisio;
			if(a==1)
				cout<<"Transitoria"<<endl;
			else
				cout<<"Diaria"<<endl;
			cout<<"Estat: ";
			a=avions[i].estat;
			if(a==1)
				cout<<"Pendent"<<endl;
			else if(a==2)
				cout<<"Realitzada"<<endl;
			else
				cout<<"Baixa"<<endl;
			cout<<"Data: "<<avions[i].d.dia<<" "<<avions[i].d.mes<< " " << avions[i].d.any <<endl;
			cout<<"Hora de Servei: "<<avions[i].servei.h<<" "<<avions[i].servei.m<<" "<<avions[i].servei.s<<endl;
			cout<<"Acabat: "<<avions[i].acabat.h<<" "<<avions[i].acabat.m<<" "<<avions[i].acabat.s<<endl;
			cout<<"Preu: "<<avions[i].preu<<endl;
			cout<<"Nom Tecnic: "<<avions[i].tecnic<<endl<<endl;
			}
}
void escriure_api(tApi api[],int A){
	cout<<"API:"<<endl;
	for(int i=0;i<A;i++){
		cout<<endl<<"Tipus de modificacio: "<<api[i].mod<<endl;
		cout<<"Codi: "<<api[i].codi<<endl;
		cout<<"Model: "<<api[i].model<<endl;
		cout<<"Data: "<<api[i].d.dia<<" "<<api[i].d.mes<< " " << api[i].d.any <<endl;
		cout<<"Hora de Registre: "<<api[i].registre.h<<" "<<api[i].registre.m<<" "<<api[i].registre.s<<endl<<endl;
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
void afegir_api(tApi api[], tAvio avions[], int & A, int i, string tipus){
	struct tm *info_temps;
	int dia,mes,any,hora,minuts,segons;
	
	temps(info_temps,dia,mes,any,hora,minuts,segons);
	
	api[A].mod=tipus;
	api[A].codi=avions[i].codi;
	api[A].model=avions[i].model;
	api[A].d.dia=dia;
	api[A].d.mes=mes;
	api[A].d.any=any;
	api[A].registre.h=hora;
	api[A].registre.m=minuts;
	api[A].registre.s=segons;
	
	A++;
	
}
void crear_avions(tAvio avions[], int & N, int & A, tApi api[]){
	string str;  	//string auxiliar per no escriure directament
	int enter;		//enter auxiliar per no escriure directament i poder comprovar si es correcte
	struct tm *info_temps;
	int dia,mes,any,hora,minuts,segons;
	
	cout<<"Quants avions vols crear?"<<endl;
	int k;
	cin>>k;
	cout<<endl;
	
	for(int i=N;i<N+k;i++){
			cout<<"Avio: "<<i+1<<endl;
			cout<<"Codi: ";
				cin.ignore();
				getline(cin,str);
				avions[i].codi=str;
			cout<<"Model: ";
				getline(cin,str);
				avions[i].model=str;
			cout<<"Revisio: (1-Transitoria, 2-Diaria)	";		
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
			cout<<"Nom Tecnic:"<<endl; 
				cin.ignore();
				getline(cin,str);
				avions[i].tecnic=str;
			afegir_api(api,avions,A,i,"S'ha afegit un avio");
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
		}else if(opcio==3){					//Tecnic
			for(int k=i+1;k<N;k++){
				if(avions[k].tecnic<avions[min].tecnic)
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
				cout<<"S'ha trobat l'avio:"<<endl<<endl;
				escriure_avions(avions,centre,centre);
				//Com que el codi es unic (en teoria) no necesita mostrar totes les opcions
				return centre;
			}else if(str < avions[centre].codi ){
		    	sup=centre-1;
		    }else {
		       inf=centre+1;
		     }
		}else if(opcio==2){
			if(avions[centre].model==str){	//cerca model
				inf=centre; sup=centre;
				//Trobar l'avio del mateix model amb la posici� inferior
				while(avions[inf].model==avions[centre].model && inf>=0)
					inf--;
				while(avions[sup].model==avions[centre].model && sup<=0)
					sup++;
				inf++; sup++; //Per obtenir la posicio
				cout<<"Resultat de la cerca:"<<endl<<endl;
				escriure_avions(avions,sup+1,inf);
				cout<<endl<<"Introdueix el index de l'avio a eliminar (1,2,3...) :"<<endl;
				obtenir_enter_rang(centre,inf+1,sup+1);
				return centre;
			}else if(str < avions[centre].model ){
		    	sup=centre-1;
		    }else {
		       inf=centre+1;
		    }
		}else if(opcio==3){
			if(avions[centre].tecnic==str){	//cerca tecnic
				inf=centre; sup=centre;
				//Trobar l'avio del mateix tecnic amb la posici� inferior
				while(avions[inf].tecnic==avions[centre].model && inf>=0)
					inf--;
				inf++;
				//Trobar l'avio del mateix tecnic amb la posici� superior
				while(avions[sup].model==avions[centre].model && sup<=0)
					sup++;
				sup++;
				cout<<"Resultat de la cerca:"<<endl<<endl;
				escriure_avions(avions,sup+1,inf);
				cout<<endl<<"Introdueix el index de l'avio a eliminar (1,2,3...) :"<<endl;
				obtenir_enter_rang(centre,inf+1,sup+1);
				return centre;
			}else if(str < avions[centre].tecnic ){
		    	sup=centre-1;
		    }else {
		       inf=centre+1;
		    }
		}
	}
	return -1;
}
void modificar_avio(tAvio avions[],int i, int & A, tApi api[]){
    
    int opc3;
    string str;
    int enter;
    
    while (opc3!=10){
        
        cout<<endl<< "Escull el criteri a modificar:" << endl;
        cout <<" 1.Codi " << endl; cout <<" 2.Model " << endl;
        cout <<" 3.Revisio " << endl; cout <<" 4.Estat " << endl;
        cout <<" 5.Data " << endl; cout <<" 6.Hora de servei " << endl;
        cout <<" 7.Acabat " << endl; cout <<" 8.Preu " << endl;
        cout <<" 9.Nom Tecnic " << endl;
		cout << "10.Sortir" << endl;
        
        cin >> opc3;
        cout << endl;
        
        switch(opc3){
                
            case 1:
                cout << "Codi: " << endl;
                cin >> str;
                avions[i].codi=str;
                afegir_api(api,avions,A,i,"S'ha canviat el codi");
                break;
                
            case 2:
                cout << "Model: " << endl;
                cin >> str;
                avions[i].codi=str;
                afegir_api(api,avions,A,i,"S'ha canviat el model");
                break;
            case 3:
                cout << "Revisio: (1-Transitoria, 2-Diaria)" << endl;
                obtenir_enter_rang(enter, 1, 2);
                avions[i].revisio=enter;
                afegir_api(api,avions,A,i,"S'ha canviat el tipus de revisio");
                break;
            case 4:
                cout << "Estat: " << endl;
                obtenir_enter_rang(enter, 1, 3);
                avions[i].estat=enter;
                afegir_api(api,avions,A,i,"S'ha canviat l'estat'");
                break;
            case 5:
                cout << "Data:";
                obtenir_enter_rang(enter, 1, 31);
                avions[i].d.dia=enter;
                obtenir_enter_rang(enter, 1, 12);
                avions[i].d.mes=enter;
                obtenir_enter_rang(enter, 2000, 2200);
                avions[i].d.any=enter;
                afegir_api(api,avions,A,i,"S'ha canviat la data del avio (no la data de la realitzacio del canvi)");
                break;
            case 6:
                cout << "Hora de Servei (hms): ";
                obtenir_enter_rang(enter, 0, 23);
                avions[i].servei.h=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].servei.m=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].servei.s=enter;
                afegir_api(api,avions,A,i,"S'ha canviat l'hora de servei");
                break;
            case 7:
                cout << "Acabat (hms): ";
                obtenir_enter_rang(enter, 0, 23);
                avions[i].acabat.h=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].acabat.m=enter;
                obtenir_enter_rang(enter, 0, 59);
                avions[i].acabat.s=enter;
                afegir_api(api,avions,A,i,"S'ha canviat l'hora d'acabada'");
                break;
            case 8:
                cout << "Preu: ";
                obtenir_enter(enter);
                avions[i].preu=enter;
                afegir_api(api,avions,A,i,"S'ha canviat el preu");
                break;
            case 9:
                cout << "Nom Tecnic";
                cin >> str;
                avions[i].tecnic=str;
                afegir_api(api,avions,A,i,"S'ha canviat el nom del tecnic");
                break;
			
	    case 10:
		cout << "Has triat SORTIR"<<endl<<endl;
		break;
		default:;	
        }
    }
        
}
void eliminar_element(tAvio avions[], int & N, int c, tApi api[], int & A){  //c = posicio de l'element a eliminar
	cout<<"Segur que el vols eliminar? (Y/N)"<<endl;
	char opcio;
    cin>>opcio;
    if(opcio=='Y' || opcio=='y'){
    	afegir_api(api,avions,A,c-1,"S'ha eliminat l'avio"); //S'ha d'afegir abans que s'elimini
    	for(int i=c-1; i<N; i++){
			igualar_taula(avions,i,i+1);
		}
		N=N-1;
		cout<<"Avio eliminat"<<endl<<endl;
	}
	else{
       	cout<<"No s'ha eliminat"<<endl<<endl;
    }
}
void est_revisio(tAvio avions[], int N){
	int t=0,d=0; //transitori=1, diari=2
	for(int i=0;i<N;i++){
		if(avions[i].revisio==1)
			t++;
		else
			d++;
	}
	cout<<"Hi han "<<N<<" avions: "<<t<<" transitoris i "<<d<<" diaris"<<endl;
	cout<<"% transitoris = "<<t*100/N<<"%"<<endl;
	cout<<"% diaris = "<<d*100/N<<"%"<<endl<<endl;
}
void est_estat(tAvio avions[], int N){
	int p=0,r=0, b=0; //pendent=1, realitzat=2, baixa=3
	for(int i=0;i<N;i++){
		if(avions[i].estat==1)
			p++;
		else if(avions[i].estat==2)
			r++;
		else
			b++;
	}
	cout<<"Hi han "<<N<<" avions: "<<p<<" pendents, "<<r<<" realitzats i "<<b<<" de baixa"<<endl;
	cout<<"% pendents = "<<p*100/N<<"%"<<endl;
	cout<<"% realitzats = "<<r*100/N<<"%"<<endl;
	cout<<"% baixa = "<<b*100/N<<"%"<<endl<<endl;
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
void guardar_api(tApi tapi[], int A, ofstream & api){
	for(int i=0; i<A; i++){
		api << tapi[i].mod << ';';
		api << tapi[i].codi << ';';
		api << tapi[i].model << ';';
		api << tapi[i].d.dia << ';';
		api << tapi[i].d.mes << ';';
		api << tapi[i].d.any << ';';
		api << tapi[i].registre.h << ';';
		api << tapi[i].registre.m << ';';
		api << tapi[i].registre.s << ';';
	}
}
void tancar_programa(tAvio avions[], int N, tApi api[], int A){ //Si es fica al inici del main, s'esborra el contingut dels fitxers, 
	ofstream ofdades("dades.txt");   							//per no perdre'l en cas de no guardar-se s'ha fet aquesta funcio 
	ofstream ofapi("api.txt");	
    guardar(avions, N, ofdades);
    guardar_api(api, A, ofapi);
    cout<<"S'ha guardat correctament";
    ofapi.close();
	ofdades.close();
}
int main(){
	tAvio avions[DIM];
	tApi api[10*DIM];
	int N,A;
	ifstream indades("dades.txt");
	ifstream inapi("api.txt");
	
	//Llegir Fitxer
	if(llegir_fitxer(avions, N, indades)){
		cout<<"dades.txt s'ha obert correctament"<<endl;
		cout<<endl;
	}
	else{
		cout<<"No existeix el fitxer dades.txt";
	}
	
	//Llegir Api
	if(llegir_api(api, A, inapi)){
		cout<<"api.txt s'ha obert correctament"<<endl;
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
        cout << " 4. Mostrar..." << endl;
        cout << " 5. Guardar i Sortir del programa " << endl;  
        cout << "SELECCIONEU UNA OPCIO: " << endl;
        cin >> opc;
        cout<<endl;
        
        switch (opc) {
                
            case 1:
                //programa, accions, funcions	Crear
                crear_avions(avions,N,A,api);
                break;
                
            case 2:
                //programa, accions, funcions	Modificar
                cout<<"Criteri de busca per trobar avio a modificar: "<<endl;
                cout<<"1.Codi"<<endl;
                cout<<"2.Model"<<endl;
                cout<<"3.Tecnic responsable"<<endl;
                cout<<"4.Mostrar tots els avions sense ordenar"<<endl;
                cout<<"5.Torna al menu principal"<<endl;
                obtenir_enter_rang(opc2,1,5);
                cout<<endl;
                switch(opc2){
					case 1:
						cout<<"Introdueix el codi a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,1,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							modificar_avio(avions,pos,A,api);
						}
						break;
					case 2:
						cout<<"Introdueix el model a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,2);
						pos=cerca(avions,N,2,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							modificar_avio(avions,pos,A,api);
						}
						break;
					case 3:
						cout<<"Introdueix el nom del tecnic: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,3);
						pos=cerca(avions,N,3,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							escriure_avions(avions,pos+1,pos);
							modificar_avio(avions,pos,A,api);
						}
						break;
					case 4:
						escriure_avions(avions,N,0);
						cout<<"Introduir posicio de l'avio a modificar: ";
						cin>>pos;
						modificar_avio(avions,pos-1,A,api);
						break;
					case 5:
						break;
					default:;
				}
                break;
                
            case 3:
                //programa, accions, funcions	Eliminar
                cout<<"Criteri de busca per trobar avio a eliminar: "<<endl;
                cout<<"1.Codi"<<endl;
                cout<<"2.Model"<<endl;
               	cout<<"3.Tecnic responsable"<<endl;
                cout<<"4.Mostrar tots els avions sense ordenar"<<endl;
                cout<<"5.Torna al menu principal"<<endl;
                obtenir_enter_rang(opc2,1,5);
                cout<<endl;
                switch(opc2){
					case 1:
						cout<<"Introdueix el codi a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,1);
						pos=cerca(avions,N,1,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							eliminar_element(avions,N,pos+1,api,A);  //la funcio eliminar conta la posicio a partir de 1
						}
						break;
					case 2:
						cout<<"Introdueix el model a buscar: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,2);
						pos=cerca(avions,N,2,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							eliminar_element(avions,N,pos+1,api,A);  //la funcio eliminar conta la posicio a partir de 1
						}
						break;
					case 3:
						cout<<"Introdueix el nom del tecnic: "<<endl;
						cin.ignore();
						getline(cin,sbuscar);
						ordenar(avions,N,3);
						pos=cerca(avions,N,3,0,sbuscar);
						if(pos==-1){
							cout<<"No s'ha trobat cap avio"<<endl<<endl;
						}else{
							eliminar_element(avions,N,pos+1,api,A);  //la funcio eliminar conta la posicio a partir de 1
						}
						break;
					case 4:
						escriure_avions(avions,N,0);
						cout<<"Introduir posicio de l'avio a eliminar: ";
						obtenir_enter_rang(pos,1,N);
						eliminar_element(avions,N,pos,api,A);
						break;
					case 5:
					default:;
				}
                break;
                
            case 4:
                //programa, accions, funcions	Mostrar Estadistiques
                
                cout<<"1.Llista completa dels avions"<<endl;
                cout<<"2.API"<<endl;
                cout<<"3.Estadistiques del tipus de revisio"<<endl;
                cout<<"4.Estadistiques del tipus d'estat'"<<endl;
                cout<<"5.Tornar al menu principal"<<endl;
                obtenir_enter_rang(opc2,1,5);
                cout<<endl;
				switch(opc2){
					case 1:
						cout<<"Avions:"<<endl<<endl;
						escriure_avions(avions,N,0);
						break;
					case 2:
	                	escriure_api(api,A);
	                	break;
	                case 3:
	                	est_revisio(avions,N);
	                	break;
	                case 4:
	                	est_estat(avions,N);
	                	break;
	                case 5:
	                	break;
                	default:;
            	}
                break;
                
            case 5:
                cout<<"Estas segur que vols sortir? (Y/N)"<<endl;
                char sortir;
                cin>>sortir;
                if(sortir!='Y' && sortir!='y')
                	opc=0;
                else{
                	tancar_programa(avions,N,api,A);
            	}
				break;
            default:;
        }// fi switch
        
    }//fi while

}
