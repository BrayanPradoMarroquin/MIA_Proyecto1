#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void escribir();

struct mkdisk
{
    int mbr_tamano;
    char mbr_fecha_creacion[17];
    int mbr_dsk_signature;
    int size;
    string fit = "BF";
    int unit = 1024*1024;
    string path;
};

mkdisk MBR;

/**
 * Formato de fecha
 * @brief Crea una fecha estándar
 * @param  {int} field
 */
string format_day_prop(int field) {
  return (field < 10 ? "0" : "") + to_string(field);
}

/**
 * Obtener fecha como string
 * @brief Retorna un string de la fecha actual
 *
 */
string get_now() {
  time_t time_now = time(0);
  tm *now = localtime(&time_now);
  string current_date =
      format_day_prop(now->tm_mday) + "/" + format_day_prop(now->tm_mon + 1) +
      "/" + to_string(now->tm_year + 1900) + " " +
      format_day_prop(now->tm_hour) + ":" + format_day_prop(now->tm_min);
  return current_date;
}

//Analizador del mkdisk
void Analizadormk(string dato){
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
        }else if (Estado==1)
        {
            MBR.size = stoi(linea);
            cout<<MBR.size<<endl;
        }else if (Estado==2)
        {
            if (linea=="K")
            {
                MBR.unit = 1024;
                cout<<linea<<endl;
            }else if (linea=="M")
            {
                MBR.unit = 1024*1024;
                cout<<linea<<endl;
            }
        }else if (Estado==3)
        {
            MBR.path = linea;
            cout<<MBR.path<<endl;
        }
    }
}

void escribir(){
    // DATOS DE PRUEBA
    int mbr_tamano = MBR.size*MBR.unit;
    string mbr_fecha_creacion = get_now(); // VER FUNCION ARRIBA
    int mbr_dsk_signature = rand() % 10; // NUMERO RANDOM

  // PARA ESCRIBIR STRINGS SE USA strcpy (SE DEBE ESCRIBIR EN EL ORDEN EN EL QUE SE DEFINIÓ EL STRUCT)
  MBR.size = mbr_tamano;
  strcpy(MBR.mbr_fecha_creacion, mbr_fecha_creacion.c_str());
  MBR.mbr_dsk_signature = mbr_dsk_signature;

  // AQUÍ ABRIMOS COMO LECTURA Y ESCRITURA (rb+) EL ARCHIVO BINARIO
  FILE *disk_file = fopen(MBR.path.c_str(), "rb+");

  // FSEEK NOS POSICIONA DENTRO DEL ARCHIVO
  fseek(disk_file, 0, SEEK_SET); // EL SEGUNDO PARAMETRO ES LA POSICIÓN (0 EN ESTE CASO)

  // CREAR UN KB DE 0
  char buffer[1024];
  for (int i = 0; i < 1024; i++)
    buffer[i] = '\0'; // AQUÍ CREAMOS UN KB DE BYTES COMO ARREGLO PARA RELLENAR

   // RELLENAR TODO EL ARCHIVO CON 0
  for (int byte_index = 0; byte_index < mbr_tamano/1024; byte_index++) // VAMOS A LLENAR 1KB A LA VEZ (ASI ES MAS RÁPIDO)
    fwrite(&buffer, 1024, 1, disk_file);

   // FSEEK NOS POSICIONA DENTRO DEL ARCHIVO
  fseek(disk_file, 0, SEEK_SET);

  // CON FWRITE GUARDAMOS EL STRUCT LUEGO DE POSICIONARNOS
  fwrite(&MBR, sizeof(MBR), 1, disk_file); // EL TERCER PAREMETRO ES LA CANTIDAD DE STRUCTS A GUARDAR (EN ESTE CASO SOLO 1)

  // CERRAR STREAM (importante)
  fclose(disk_file);
}

void EjecutarMk(){
    escribir();
    cout<<"Disco Duro creado exitosamente"<<endl;
}

