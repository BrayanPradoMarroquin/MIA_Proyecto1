#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Analizador 
void Analizador(string &i);

void Analizador(string entrada){
    ifstream Archivo(entrada);

    string linea;

    while (getline(Archivo, linea))
    {
        cout<<linea<<endl;
    }
    
}