#include <iostream>
#include <fstream>
using namespace std;

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
}