#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Analizador 
void Analizador(string &i);


void Analizador(string entrada){
    ifstream Archivo(entrada);

    string linea;

    while (getline(Archivo, linea))
    {
        stringstream nueva(linea);
        string line;
        while (getline(nueva, line, ' '))
        {
            if (line=="mkdisk")
            {
                
                cout<<"Nuevo Disco"<<endl;
            }else if (line=="rep")
            {
                cout<<"Reporte Generado"<<endl;
            }else if (line=="rmdisk")
            {
                cout<<"Disco Removido"<<endl;
            }else if (line=="fdisk")
            {
                cout<<"Busqueda de Disco"<<endl;
            }else if (line=="mount")
            {
                cout<<"Disco Montado"<<endl;
            }else if (line=="unmount")
            {
                cout<<"Disco desmontado"<<endl;
            }else if (line=="mkfs")
            {
                cout<<"Formateo de Disco"<<endl;
            }    
        }
    }
    
}