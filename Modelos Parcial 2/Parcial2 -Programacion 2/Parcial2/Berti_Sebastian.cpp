#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;



class Pais
{
private:
    char _codigoPais[5];
    char _nombre[30];
    int _codContinente;
    int _nivelIngreso;
    int _cantHabitantes;
    float _pbi;
    bool _estado;
public:
    const char* getCodidoPais()
    {
        return _codigoPais;
    }
    const char* getNombre()
    {
        return _nombre;
    }
    int getCodigoContinente()
    {
        return _codContinente;
    }
    int getNivelIngreso()
    {
        return _nivelIngreso;
    }
    int getCantidadHabitantes()
    {
        return _cantHabitantes;
    }
    float getPbi()
    {
        return _pbi;
    }
    bool getEstado()
    {
        return _estado;
    }



    void setCodigoPais(const char* cp)
    {
        strcpy(_codigoPais, cp);
    }
    void setNombre(const char* n)
    {
        strcpy(_nombre, n);
    }
    void setCodContinente(int cc)
    {
        _codContinente = cc;
    }
    void setNivelIngreso(int ni)
    {
        _nivelIngreso = ni;
    }
    void setCantidadHabitantes(int ch)
    {
        _cantHabitantes = ch;
    }
    void setPbi(float pbi)
    {
        _pbi = pbi;
    }
    void setEstado(bool es)
    {
        _estado =es;
    }

    void Mostrar()
    {
        cout<<_codigoPais<<endl;
        cout<<_nombre<<endl;
        cout<<_codContinente<<endl;
        cout<<_nivelIngreso<<endl;
        cout<<_cantHabitantes<<endl;
        cout<<_pbi<<endl;

    }



};


class ArchivoPais
{
private:
    char nombre[30];
public:
    ArchivoPais(const char *n)
    {
        strcpy(nombre, n);
    }

    Pais leerRegistro(int pos)
    {
        Pais reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }

    int contarRegistros()
    {
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Pais);
    }

    bool grabarRegistro(Pais reg)
    {
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};


class Continente
{
private:
    int _codContinente;
    char _nombre[30];
public:

    int getCodigoContinente()
    {
        return _codContinente;
    }
    const char* getNombre()
    {
        return _nombre;
    }


    void setCodContinente(int cc)
    {
        _codContinente = cc;
    }
    void setNombre(const char* n)
    {
        strcpy(_nombre, n);
    }

    bool operator ==(const char* nombre)
    {
        if(strcmp(_nombre, nombre) == 0 ) return true;
        return false;
    }

};


class ArchivoContinente
{
private:
    char nombre[30];
public:
    ArchivoContinente(const char *n)
    {
        strcpy(nombre, n);
    }

    Continente leerRegistro(int pos)
    {
        Continente reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }

    int contarRegistros()
    {
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Continente);
    }

    bool grabarRegistro(Continente reg)
    {
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }

};



void puntoA()
{
    Pais objPais;
    ArchivoPais objArPais("paises.dat");

    int tam = objArPais.contarRegistros();

    int cantidadNivelesMas20 = 0;
    int cantidadPaisesPorNivel[5] = {0};


    for(int i = 0; i < tam; i++)
    {
        objPais = objArPais.leerRegistro(i);

        if(objPais.getEstado()== true )
        {
            cantidadPaisesPorNivel[objPais.getNivelIngreso()-1]++;
        }
    }

    for(int i = 0 ; i<5 ; i++)
    {
        if(cantidadPaisesPorNivel[i] > 20)
        {
            cantidadNivelesMas20++;
        }
    }
    cout << "La cantidad de niveles de ingresos con mas de 20 paises es " << cantidadNivelesMas20 << endl;
}




class ArchivoPuntoB
{
private:
    char _nombre[30];
public:
    ArchivoPuntoB(const char* n)
    {
        strcpy(_nombre, n);
    };


    Pais leerRegistro(int pos)
    {
        Pais reg;
        FILE* p = fopen(_nombre, "rb");
        if (p == NULL)
        {
            return reg;
        }
        fseek(p, pos * sizeof reg, 0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }


    int contarRegistros()
    {
        FILE* p = fopen(_nombre, "rb");
        if (p == NULL)
        {
            return -1;
        }
        fseek(p, 0, 2);
        int cant = ftell(p) / sizeof(Pais);
        fclose(p);
        return cant;
    }

    bool grabarRegistro(Pais obj)
    {
        FILE* p;
        p = fopen("puntoB.dat", "ab");
        if (p == NULL) return false;
        bool escribio = fwrite(&obj, sizeof obj, 1, p);
        fclose(p);
        return escribio;
    }
};


void puntoB()
{
    Pais objPais;
    ArchivoPais objArPais("paises.dat");

    Continente objCont;
    ArchivoContinente objArCont("continentes.dat");

    ArchivoPuntoB objArPunB("puntoB.dat");

    int tamPais = objArPais.contarRegistros();
    int tamCont = objArCont.contarRegistros();

    for(int i = 0 ; i < tamPais ; i++)
    {
        objPais = objArPais.leerRegistro(i);



        
        if(objPais.getPbi() <  10000000 && objPais.getEstado() == true && objPais.getCodigoContinente() == objCont.getCodigoContinente())
        {
            for(int j =0 ; j < tamCont ; j++)
            {
                objCont = objArCont.leerRegistro(j);


                if( objCont.getNombre()  == "America" )
                {
                    if(objArPunB.grabarRegistro(objPais)==false)
                    {
                        cout << "No se pudo crear el archivo" << endl;
                        return;
                    }

                }
            }
        }
    }

}


void puntoC()
{
    ArchivoPuntoB objArPuntoB("puntoB.dat");


    int tam = objArPuntoB.contarRegistros();


    if(tam <= 0 )
    {
        cout << "El archivo esta vacio" << endl;
        return;
    }

    Pais *vectorDinamico = new Pais[tam];

    if(vectorDinamico == NULL)
    {
        cout << "No se pudo asignar memoria" << endl;
        return exit(-1);
    }

    for(int i = 0; i < tam; i++)
    {
        vectorDinamico[i] = objArPuntoB.leerRegistro(i);
    }


    for (int j = 0; j < tam; j++)
    {

        vectorDinamico[j].Mostrar();
        cout << endl;
    }

    delete []vectorDinamico;

}


void Menu()
{
    while(true)
    {
        int opc;
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"--------------"<<endl;
        cout<<"1 - Calcular e informar la cantidad de niveles de ingresos con más de 20 países."<<endl;
        cout<<"2 - Generar un archivo con los países de menos de 10 millones de PBI que pertenecen al continente de nombre América. El formato de registro debe ser el mismo que el del archivo de países."<<endl;
        cout<<"3 - Listar el archivo nuevo creado usando asignación dinámica de memoria"<<endl;
        cout<<"4 - Sobrecargar un operador para alguna de las clases de los ejercicios anteriores, que sea de utilidad para la resolución de alguno de esos puntos"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"INGRESE LA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc)
        {
        case 1:
            puntoA();
            break;
        case 2:
            puntoB();
            break;
        case 3:
            puntoC();
            break;
        case 4:

            break;
        case 0:
            return ;
        default:
            cout<<"LA OPCION INGRESADA NO ES CORRECTA"<<endl;
            system("pause");
            break;
        }
        system("pause");
    }
}


int main()
{
    Menu();
    return 0;
}
