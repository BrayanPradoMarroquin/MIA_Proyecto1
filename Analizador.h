#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mk.h"
#include "Fdisk.h"

using namespace std;

//Analizador General
void Analizador(string &i);


void Analizador(string entrada){
    ifstream Archivo(entrada);

    string linea;
//Primera pasada detectar comando
    while (getline(Archivo, linea))
    {
        int Estado = 0; 
        stringstream nueva(linea);
        string line;

        //Segunda pasada para leer comandos y guardar informacion
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
                Estado=4;
                cout<<"Disco Removido"<<endl;
            }else if (line=="fdisk")
            {
                Estado = 3;
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
            }else if (Estado==3)
            {
                AnalizadorFdisk(line);
                //cout<<"Hola"<<endl;
            }else if (Estado==4)
            {
                Analizadormk(line);
            }
            
            

                
        }
        
        stringstream nueva2(linea);
        string line2;
        //Tercera pasada, ejecutar comandos
        while (getline(nueva2, line2, ' '))
        {
            if (line2=="mkdisk")
            {
                EjecutarMk();
                break;
            }else if (line2=="rep")
            {
                cout<<"Reporte Generado Exitosamente :D "<<endl;
            }else if (line2=="rmdisk")
            {
                rmdisk();
                cout<<"Disco Removido"<<endl;
            }else if (line2=="fdisk")
            {
                EjecutarFdisk();
                break;
            }else if (line2=="mount")
            {
                cout<<"Disco Montado"<<endl;
            }else if (line2=="unmount")
            {
                cout<<"Disco desmontado"<<endl;
            }else if (line2=="mkfs")
            {
                cout<<"Formateo de Disco"<<endl;
            }
        }
           
    }
    
}