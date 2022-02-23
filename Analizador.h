#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mk.h"

using namespace std;

//Analizador 
void Analizador(string &i);


void Analizador(string entrada){
    ifstream Archivo(entrada);

    string linea;

    while (getline(Archivo, linea))
    {
        int Estado = 0; 
        stringstream nueva(linea);
        string line;
        while (getline(nueva, line, ' '))
        {
            if (line=="mkdisk")
            {
                Estado = 1;
                cout<<"Nuevo Disco"<<endl;
            }else if (line=="rep")
            {
                Estado=2;
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
            }else if (Estado==1)
            {
                Analizadormk(line);
                //cout<<line<<endl;
            }
                
        }
    }
    
}