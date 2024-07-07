
#include <iostream>
#include <cstring> // para poder utilizar strcpy
#include <cstdlib>

using namespace std;

#include "parcial2.h"

class punto1 {
private:
	int _codMat;
	int _tipo;
	float _importeTotal;
public:
	void Cargar() {

		cin >> _codMat;
		cin >> _tipo;
		cin >> _importeTotal;

	}

	void Mostrar() {
		cout << "CODIGO MATERIAL: " << _codMat << endl;
		cout << "TIPO DE MATERIAL: " << _tipo << endl;
		cout << "IMPORTE TOTAL: " << _importeTotal << endl;

	}

	int getCodigoMaterial() { return _codMat; }
	int getTipo() { return _tipo; }
	float getImporteTotal() { return _importeTotal; }


	void setCodigoMaterial(int cm) { _codMat = cm; }
	void setTipo(int t) { _tipo = t; }
	void setImporteTotal(float it) { _importeTotal = it; }


};


class ArchivoPunto1 {
private:
	char nombre[30];
public:
	ArchivoPunto1(const char* n) {
		strcpy(nombre, n);
	}
	punto1 leerRegistro(int pos) {
		punto1 reg;
		FILE* p = fopen(nombre, "rb");
		if (p == NULL) {
			return reg;
		}
		fseek(p, pos * sizeof reg, 0);
		fread(&reg, sizeof reg, 1, p);
		fclose(p);
		return reg;
	}

	int contarRegistros() {
		FILE* p = fopen(nombre, "rb");
		if (p == NULL) {
			return -1;
		}
		fseek(p, 0, 2);
		int cant = ftell(p) / sizeof(punto1);
		fclose(p);
		return cant;
	}

	bool grabarRegistro(punto1 reg) {
		FILE* p;
		p = fopen(nombre, "ab");
		if (p == NULL) return false;
		int escribio = fwrite(&reg, sizeof reg, 1, p);
		fclose(p);
		return escribio;
	}


	void mostrarArchivo() {
		punto1 obj;
		FILE* p;
		p = fopen("punto1.dat", "rb");
		if (p == NULL) {
			cout << "no se pudo abrir el archivo que se creo" << endl;
			exit(1);
		}
		while (fread(&obj, sizeof obj, 1, p) == true) {
			obj.Mostrar();
			cout << endl;
		}
		fclose(p);
	}
};

//Generar un archivo con el código de material, el tipo y el importe
//total de las compras para ese material, para el año actual.
//Es decir, por cada material se debe registrar el código de material,
//el tipo, y el importe total de las compras de ese material en el año actual.

void puntoA() {
	Material objMat;
	ArchivoMateriales objArMat("materiales.dat");

	Compra objCom;
	ArchivoCompras objArCom("compras.dat");

	punto1 objPunto1;
	ArchivoPunto1 objArPunto1("punto1.dat");


	int tamMat = objArMat.contarRegistros();

	int tamCom = objArCom.contarRegistros();


	for (int i = 0; i < tamMat; i++) {
		objMat = objArMat.leerRegistro(i);
		int acu = 0;


		for (int j = 0; j < tamCom; j++) {
			objCom = objArCom.leerRegistro(j);


			if (objMat.getCodigoMaterial() == objCom.getCodigoMaterial() && objCom.getFechaCompra().getAnio() == 2022) {
				acu += objCom.getImporte();
			}

		}


		objPunto1.setCodigoMaterial(objMat.getCodigoMaterial());
		objPunto1.setTipo(objMat.getTipo());
		objPunto1.setImporteTotal(acu);



		if (objArPunto1.grabarRegistro(objPunto1) == false) {
			cout << "No se pudo crear el archivo" << endl;
			return;
		}
	}
}


//La cantidad de obras de cada provincia.
void puntoB() {
	Obra objObra;
	ArchivoObras objArObras("obras.dat");

	int obrasPorProvincia[24] = {};


	int tam = objArObras.contarRegistros();


	for (int i = 0; i < tam; i++) {
		objObra = objArObras.leerRegistro(i);

		obrasPorProvincia[objObra.getProvincia() - 1]++;

	}

	for (int x = 0; x < 24; x++) {
		cout << "La cantitad de obras para la provincia: " << x + 1 << " es de " << obrasPorProvincia[x] << endl;
	}

}

//Generar un vector dinámico con todos los materiales y listar luego
//los materiales del vector que pertenezcan a un tipo que se ingresa por teclado
void puntoC() {
	Material objMat;
	ArchivoMateriales objArMat("materiales.dat");

	int buscarMaterial;


	int tam = objArMat.contarRegistros();

	Material *vectorDinamico = new Material[tam];
	if (vectorDinamico == NULL) {
		cout << "no se pudo asignar memoria" << endl;
		return exit(-1);
	}

	for (int i = 0; i < tam; i++) {
		objMat = objArMat.leerRegistro(i);

		vectorDinamico[i] = objMat;
	}


	cout << "Listar los materiales del tipo: " << endl;
	cin >> buscarMaterial;
	cout << endl;

	for (int j = 0; j < tam;j++) {
		if (buscarMaterial == vectorDinamico[j].getTipo()) {
			vectorDinamico[j].Mostrar();
			cout << endl;
		}
	}


	delete []vectorDinamico;
}



void Menu() {
	ArchivoMateriales objMat("materiales.dat");

	ArchivoCompras objCom("compras.dat");

	ArchivoProveedores objPro("proveedores.dat");

	ArchivoObras obr("obras.dat");

	ArchivoPunto1 obj("punto1.dat");

	Compra com;

	while (true) {
		int opc;
		system("cls");
		cout << "MENU PRINCIPAL" << endl;
		cout << "--------------" << endl;
		cout << "1 - Generar archivo" << endl;
		cout << "2 - mostrar archivo nuevo " << endl;

		cout << "3- mostrar compras" << endl;
		cout << "4- mostrar proveedores" << endl;
		cout << "5- mostrar materiales" << endl;


		cout << "6- la cantidad de obras de cada provincia" << endl;
		cout << "7- listar obras" << endl;


		cout << "8- Generar un vector dinámico con todos los materiales y listar luego los materiales del vector que pertenezcan a un tipo que se ingresa por teclado." << endl;




		cout << "9- El tipo de material con menos cantidad de materiales(puntoB)" << endl;




		cout << "----------------------------------------" << endl;
		cout << "INGRESE LA OPCION: ";
		cin >> opc;
		system("cls");
		switch (opc) {
		case 1:
			puntoA();
			break;
		case 2:
			obj.mostrarArchivo();
			break;
		case 3:
			objCom.listarCompras();
			break;
		case 4:
			objPro.listarProveedores();
			break;
		case 5:
			objMat.listarMateriales();

			break;
		case 6:
			puntoB();
			break;
		case 7:
			obr.listarObras();

			break;
		case 8:
			puntoC();

			break;
		case 9:

			break;

		case 0:


			return;
		default:
			cout << "LA OPCION INGRESADA NO ES CORRECTA" << endl;
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
