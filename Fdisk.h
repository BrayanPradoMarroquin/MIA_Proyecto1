#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

void escribirfd();

struct Partition {
  int size = 0; 
  char name[25]; 
};

struct PMBR
{
  int mbr_tamano;
  char mbr_fecha_creacion[17];
  int mbr_dsk_signature;
  Partition partitions[4];
};

int size=0;
int unit=0;
string path;
string name;

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
            name = linea;
        }   
    }
}

void escribirfd(){
    PMBR mbr;

    FILE *disk_file = fopen(path.c_str(), "r+");
    fseek(disk_file, 0, SEEK_SET);
    fread(&mbr, sizeof(PMBR), 1, disk_file);

    // BUSCAR PARTICION LIBRE
  int partitionIndex = 0;
  for(int i =0; i < 4; i++) {
    if(mbr.partitions[i].size == 0){
      partitionIndex = i;
      break;
    }
  }

    Partition nuevaPart;
  nuevaPart.size = unit*size;
  strcpy(nuevaPart.name, name.c_str());

  mbr.partitions[partitionIndex] = nuevaPart;

  // GUARDAR
  fseek(disk_file, 0, SEEK_SET);
  fwrite(&mbr, sizeof(PMBR), 1, disk_file);

  fclose(disk_file);
}

void EjecutarFdisk(){
    escribirfd();
    cout<<"Particion creada"<<endl;
}