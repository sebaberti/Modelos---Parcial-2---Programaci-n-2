#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "p1.h"
//Generar un archivo con los equipos que tengan al menos 10 jugadores inscriptos.
//Cada registro debe tener el ID de equipo, el nombre del equipo, y la categoría del
// deporte al que pertenece el equipo.




class Punto1 {
private:
	int _idEquipo;
	char _nombre[30];
	int _catDeporte;

public:
	int getIdEquipo() { return _idEquipo; }
	const char* getNombre() { return _nombre; }
	int getCatDeporte() { return _catDeporte; }


	void setIdEquipo(int idEquipo) { _idEquipo = idEquipo; }
	void setNombre(const char* n) { strcpy(_nombre, n); }
	void setCatDep(int catDep) { _catDeporte = catDep; }



	void Mostrar() {
		cout << "EQUIPO " << _idEquipo << endl;
		cout << "NOMBRE " << _nombre << endl;
		cout << "CATEGORIA " << _catDeporte << endl;
	}
};

class ArchivoPunto1 {
private:
	char _nombre[30];
public:
	ArchivoPunto1(const char* n) { strcpy(_nombre, n); };


	Punto1 leerRegistro(int pos) {
		Punto1 reg;
		FILE* p = fopen(_nombre, "rb");
		if (p == NULL) {
			return reg;
		}
		fseek(p, pos * sizeof reg, 0);
		fread(&reg, sizeof reg, 1, p);
		fclose(p);
		return reg;
	}


	int contarRegistros() {
		FILE* p = fopen(_nombre, "rb");
		if (p == NULL) {
			return -1;
		}
		fseek(p, 0, 2);
		int cant = ftell(p) / sizeof(Punto1);
		fclose(p);
		return cant;
	}

	bool grabarRegistro(Punto1 obj) {
		FILE* p;
		p = fopen("punto1.dat", "ab");
		if (p == NULL) return false;
		bool escribio = fwrite(&obj, sizeof obj, 1, p);
		fclose(p);
		return escribio;
	}



	void mostrarArchivo() {
		Punto1 obj;
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

//Generar un archivo con los equipos que tengan al menos 10 jugadores inscriptos.
//Cada registro debe tener el ID de equipo, el nombre del equipo,
// y la categoría del deporte al que pertenece el equipo.

void PuntoA() {
	Deporte objDep;
	ArchivoDeportes objArDep("deportes.dat");

	Jugador objJug;
	ArchivoJugadores objArJug("jugadores.dat");

	Equipo objEq;
	ArchivoEquipos objArEq("equipos.dat");

	Punto1 objPunto1;
	ArchivoPunto1 objArPun1("punto1.dat");

	int tam1 = objArEq.contarRegistros();

	int tam2 = objArJug.contarRegistros();

	int tam3 = objArDep.contarRegistros();




	//EQUIPOS
	for (int i = 0; i < tam1; i++) {
		objEq = objArEq.leerRegistro(i);

		int contadorInscriptos = 0;
		//JUGADORES
		for (int j = 0; j < tam2; j++) {
			objJug = objArJug.leerRegistro(j);

			if (objEq.getIdEquipo() == objJug.getIdEquipo()) {
				contadorInscriptos++;

				if (contadorInscriptos >= 2) {
					objPunto1.setIdEquipo(objEq.getIdEquipo());
					objPunto1.setNombre(objEq.getNombre());

					//DEPORTES
					for (int x = 0; x < tam3; x++) {

						objDep = objArDep.leerRegistro(x);


						if (objDep.getIdDeporte() == objJug.getIdDeporte()) {
							objPunto1.setCatDep(objDep.getIdCtegoria());

							if (objArPun1.grabarRegistro(objPunto1) == false) {
								cout << "No se pudo crear el archivo" << endl;
								return;
							}

						}
					}
				}

			}
		}
	}
}

//Hacer un vector dinámico para listar el archivo del punto anterior.
void PuntoB() {

	ArchivoPunto1 objArP1("punto1.dat");

	int tam = objArP1.contarRegistros();


	Punto1 *vectorDinamico = new Punto1[tam];

	if (vectorDinamico == NULL) {
		cout << "No se pudo crear el arreglo" << endl;
		return exit(-1);
	}

	for (int i = 0; i < tam; i++) {
		//objP1 = objArP1.leerRegistro(i);

		vectorDinamico[i] = objArP1.leerRegistro(i);

	}

	for (int j = 0; j < tam;j++) {

		vectorDinamico[j].Mostrar();
		cout << endl;
	}

	delete []vectorDinamico;

}

//Sobrecargar el operador == para comparar un objeto Jugador con
//un objeto Deporte. Debe devolver verdadero cuando coinciden los
// Id de depor

//bool Jugador::operator ==(Deporte &obj){
//if(idDeporte == obj.getIdDeporte()) return true;
//return false;
//}


class ArchivoPuntoD {
private:
	char _nombre[30];
public:
	ArchivoPuntoD(const char* n) { strcpy(_nombre, n); };


	Deporte leerRegistro(int pos) {
		Deporte reg;
		FILE* p = fopen(_nombre, "rb");
		if (p == NULL) {
			return reg;
		}
		fseek(p, pos * sizeof reg, 0);
		fread(&reg, sizeof reg, 1, p);
		fclose(p);
		return reg;
	}


	int contarRegistros() {
		FILE* p = fopen(_nombre, "rb");
		if (p == NULL) {
			return -1;
		}
		fseek(p, 0, 2);
		int cant = ftell(p) / sizeof(Deporte);
		fclose(p);
		return cant;
	}

	bool grabarRegistro(Deporte obj) {
		FILE* p;
		p = fopen("puntoD.dat", "ab");
		if (p == NULL) return false;
		bool escribio = fwrite(&obj, sizeof obj, 1, p);
		fclose(p);
		return escribio;
	}



	void mostrarArchivo() {
		Deporte obj;
		FILE* p;
		p = fopen("puntoD.dat", "rb");
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



//Hacer un archivo con los deportes que tengan jugadores de todos los claustros.
// Los registros del archivo nuevo deben tener el mismo formato que el
// archivo de deportes.

void puntoD() {
	Deporte objDep;
	ArchivoDeportes objArDep("deportes.dat");

	Jugador objJug;
	ArchivoJugadores objArJug("jugadores.dat");

	ArchivoPuntoD objArPuntoD("puntoD.dat");


	int tamDep = objArDep.contarRegistros();
	int tamJug = objArJug.contarRegistros();

	for (int i = 0; i < tamDep; i++) {
		objDep = objArDep.leerRegistro(i);

		bool vec[4] = {};

		for (int j = 0; j < tamJug; j++) {
			objJug = objArJug.leerRegistro(j);

			if (objDep.getIdDeporte() == objJug.getIdDeporte()) {

				vec[objJug.getClaustro() - 1] = true;
			}

		}


		bool bandera = true;
		for (int x = 0; x < 4;x++) {
			if (vec[x] == false) {
				bandera = false;
				break;
			}
		}

		if (bandera == true) {
			if (objArPuntoD.grabarRegistro(objDep) == false) {
				cout << "No se pudo crear el archivo" << endl;
				return;
			}

		}
	}
}



//Crear un vector dinámico con los equipos de nivel inicial. Listar el vector.
void puntoE() {
	Equipo objEq;
	ArchivoEquipos objArEq("equipos.dat");

	Equipo* equiposNivelInicial;

	int tam = objArEq.contarRegistros();
	int con = 0;

	for (int i = 0; i < tam; i++) {
		objEq = objArEq.leerRegistro(i);


		if (objEq.getNivel() == 1) {
			con++;
		}

	}

	equiposNivelInicial = new Equipo[con];
	if (equiposNivelInicial == NULL) { cout << "No se pudo crear el vector" << endl; exit(1); }

	int indice = 0;
	for (int i = 0; i < tam; i++) {
		objEq = objArEq.leerRegistro(i);

		if (objEq.getNivel() == 1) {
			equiposNivelInicial[indice++] = objEq;
		}

	}

	cout << "Mostrando Equipos con nivel 1" << endl;
	for (int i = 0; i < con; i++) {
		cout << "Equipo: #" << i + 1 << endl;
		equiposNivelInicial[i].Mostrar();
	}

	delete[] equiposNivelInicial;
}

//Generar un archivo con los jugadores que hayan pagado más de $10000
// de matrícula y que se hayan inscripto este año. Cada registro del archivo
// debe tener el siguiente formato:
//DNI, nombre, apellido, claustro y nombre del deporte

class puntoF {
private:
	int DNI, claustro;
	char nombre[25], apellido[30], nombreDeporte[30];
public:
	int getDNI() { return DNI; }
	int getClaustro() { return claustro; }
	const char* getNombre() { return nombre; }
	const char* getApellido() { return apellido; }
	const char* getNombreDeporte() { return nombreDeporte; }


	void setDNI(int dni) { DNI = dni; }
	void setClaustro(int c) { claustro = c; }
	void setNombre(const char* n) { strcpy(nombre, n); }
	void setApellido(const char* ap) { strcpy(apellido, ap); }
	void setNombreDeporte(const char* nd) { strcpy(nombreDeporte, nd); }

	void Mostrar() {
		cout << "DNI " << DNI << endl;
		cout << "CLAUSTRO " << claustro << endl;
		cout << "NOMBRE " << nombre << endl;
		cout << "APELLIDO " << apellido << endl;
		cout << "NOMBRE DEPORTE " << nombreDeporte << endl;


	}

};

class ArchivoPuntoF {
private:
	char nombre[30];
public:
	ArchivoPuntoF(const char* n) { strcpy(nombre, n); };


	puntoF leerRegistro(int pos) {
		puntoF reg;
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
		int cant = ftell(p) / sizeof(puntoF);
		fclose(p);
		return cant;
	}

	bool grabarRegistro(puntoF obj) {
		FILE* p;
		p = fopen("PuntoF.dat", "ab");
		if (p == NULL) return false;
		bool escribio = fwrite(&obj, sizeof obj, 1, p);
		fclose(p);
		return escribio;
	}



	void mostrarArchivo() {
		puntoF obj;
		FILE* p;
		p = fopen("PuntoF.dat", "rb");
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

void PuntoFa() {
	Jugador objJug;
	ArchivoJugadores objArJug("jugadores.dat");

	Deporte objDep;
	ArchivoDeportes objArDep("deportes.dat");

	puntoF objPunF;
	ArchivoPuntoF objArPunF("PuntoF.dat");


	int tamJug = objArJug.contarRegistros();
	int tamDep = objArDep.contarRegistros();


	for (int i = 0; i < tamJug; i++) {
		objJug = objArJug.leerRegistro(i);

		if (objJug.getMatriculia() > 500 && objJug.getFechaInscirpcion().getAnio() == 2024) {
			objPunF.setDNI(objJug.getDNI());
			objPunF.setClaustro(objJug.getClaustro());
			objPunF.setNombre(objJug.getNombre());
			objPunF.setApellido(objJug.getApellido());

			for (int j = 0; j < tamDep; j++) {
				objDep = objArDep.leerRegistro(j);

				if (objDep.getIdDeporte() == objJug.getIdDeporte()) {
					objPunF.setNombreDeporte(objDep.getNombre());
					break;
				}
			}

			if (objArPunF.grabarRegistro(objPunF) == false) {
				cout << "No se pudo crear el archivo" << endl;
				return;
			}
		}
	}

}


void puntoG() {
	Jugador objJug;
	ArchivoJugadores objArJug("jugadores.dat");



	int buscarEquipo;

	Jugador* vectorJugadores;

	int tam1 = objArJug.contarRegistros();


	cout << "Ingrese el numero de equipo que desea buscar: " << endl;
	cin >> buscarEquipo;

	int contador = 0;

	for (int i = 0; i < tam1; i++) {
		objJug = objArJug.leerRegistro(i);


		if (objJug.getIdEquipo() == buscarEquipo) {
			contador++;
		}

	}


	vectorJugadores = new Jugador[contador];
	if (vectorJugadores == NULL) { cout << "No se pudo crear el vector" << endl; exit(1); }

	int indice = 0;
	for (int i = 0; i < tam1; i++) {
		objJug = objArJug.leerRegistro(i);

		if (objJug.getIdEquipo() == buscarEquipo) {
			vectorJugadores[indice++] = objJug;
		}

	}

	for (int i = 0; i < contador; i++) {
		vectorJugadores[i].Mostrar();
		cout << endl;
	}


	delete[] vectorJugadores;
}





void Menu() {
	ArchivoPunto1 obj("punto1.dat");

	ArchivoPuntoD objArD("puntoD.dat");


	Jugador objJug;
	ArchivoJugadores objArJug("jugadores.dat");


	ArchivoPuntoF objArPunF("PuntoF.dat");

	objJug.setClaustro(1);
	//objJug.Cargar();

	while (true) {
		int opc;
		system("cls");
		cout << "MENU PRINCIPAL" << endl;
		cout << "--------------" << endl;
		cout << "1 - MOSTRAR TODOS" << endl;
		cout << "2 -Generar un archivo con los equipos que tengan al menos 10 jugadores inscriptos. Cada registro debe tener el ID de equipo, el nombre del equipo, y la categoría del deporte al que pertenece el equipo" << endl;
		cout << "3- mostrar archivo nuevo" << endl;
		cout << "4- mostrar archivo nuevo con VECTOR DINAMICO" << endl;
		cout << "5- Hacer un archivo con los deportes que tengan jugadores de todos los claustros. Los registros del archivo nuevo deben tener el mismo formato que el archivo de deportes." << endl;
		cout << "6- mostrar archivo punto D" << endl;
		cout << "7- cargar jugador(para ver punto anterior)" << endl;

		cout << "8- Crear un vector dinámico con los equipos de nivel inicial. Listar el vector." << endl;

		cout << "9- sobrecargar probando" << endl;

		cout << "10- archvivo punto F" << endl;
		cout << "11- mostrar archivo punto f" << endl;

		cout << "12-Crear un vector con los jugadores pertenecientes a un equipo cuyo número de equipo se ingresa por teclado. Listar el vector " << endl;


		cout << "13= sobrevarga >" << endl;

		cout << "----------------------------------------" << endl;
		cout << "INGRESE LA OPCION: ";
		cin >> opc;
		system("cls");
		switch (opc) {
		case 1:
			mostrarTodos();
			break;
		case 2:
			PuntoA();
			break;
		case 3:
			obj.mostrarArchivo();
			break;
		case 4:
			PuntoB();
			break;
		case 5:
			puntoD();
			break;
		case 6:
			objArD.mostrarArchivo();
			break;
		case 7:
			objJug.Cargar();
			objArJug.grabarRegistro(objJug);
			break;
		case 8:
			puntoE();
			break;
		case 9:
			if (objJug == 1) {
				cout << "El jugador pertenece al claustro 1." << endl;
			}
			else {
				cout << "El jugador no pertenece al claustro 1." << endl;
			}
			break;
		case 10:
			PuntoFa();
			break;
		case 11:
			objArPunF.mostrarArchivo();
			break;
		case 12:
			puntoG();
			break;
		case 13:
			if (objJug > 2023) {
				cout << "verdadero" << endl;
			}
			else {
				cout << "false" << endl;
			}
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
