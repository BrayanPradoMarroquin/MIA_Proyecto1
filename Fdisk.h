#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

struct Fdisk
{
    int size;
    string unit;
    char name[25];
};

struct MkFdisk
{
    int mbr_tamano;
    char mbr_fecha_creacion[17];
    int mbr_dsk_signature;
    int size;
    string fit = "BF";
    int unit = 1024*1024;
    string path;
};


int size=0;
int unit=0;
string path;
char name[25];

void AnalizadorFdisk(string dato){
    stringstream nueva(dato);
    string linea;
    int Estado = 0;
    while (getline(nueva, linea, '='))
    {
        if (linea=="-Size")
        {
            Estado=1;
        }else if (linea=="-unit")
        {
            Estado = 2;
        }else if (linea=="-path")
        {
            Estado = 3;
        }else if (linea=="-name"){
            Estado = 4;
        }else if (Estado==1)
        {
            size = stoi(linea);
            cout<<size<<endl;
        }else if (Estado==2)
        {
            if (linea=="K")
            {
                unit = 1024;
                cout<<linea<<endl;
            }else if (linea=="M")
            {
                unit = 1024*1024;
                cout<<linea<<endl;
            }
        }else if (Estado==3)
        {
            path = linea;
            cout<<path<<endl;
        }else if (Estado==4)
        {
            //strcpy(name, linea.c_str());
            strcpy(name, linea.c_str());
        }   
    }
}

void EjecutarFdisk(){
    cout<<"Particion creada"<<endl;
}