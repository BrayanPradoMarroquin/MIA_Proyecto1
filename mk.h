#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct mkdisk
{
    int size;
    string fit = "BF";
    int unit = 1024*1024;
    string path;
};

mkdisk MBR;

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

void EjecutarMk(){
    cout<<"Disco Duro creado exitosamente"<<endl;
}