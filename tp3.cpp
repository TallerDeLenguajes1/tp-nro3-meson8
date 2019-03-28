#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"jorgito", "b", "c", "d", "e", "olaf"};
char Apellidos[6][10]={"f", "g", "hormiga", "i", "j"};

typedef struct TDatos {
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
} TDatos;

typedef struct TCaracteristicas{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
} TCaracteristicas;

typedef struct TPersonaje {
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
} TPersonaje;

TDatos cargaDatos ();
void mostrarDatos (TDatos datos);

int main (void) {
	TDatos pj;

	srand(time(NULL));

	pj = cargaDatos();

	mostrarDatos(pj);

	return 0;
}

TDatos cargaDatos () {

	TDatos datos;
	enum TRaza raza;

	switch(rand()%5) {
		case 0: 
			raza = Orco;
			break;
		case 1: 
			raza = Humano;
			break;
		case 2: 
			raza = Enano;
			break;
		case 3: 
			raza = Mago;
			break;
		case 4: 
			raza = Elfo;
			break;

		default: Humano;
	}

	datos.Raza = raza;

	datos.ApellidoNombre = (char *) malloc (10);

	strcpy((datos.ApellidoNombre), Nombres[rand()%6]);

	datos.edad = rand()%300;

	datos.Salud = (double)100;


	return datos;
}


void mostrarDatos (TDatos datos) {


printf("Raza: ");

switch(datos.Raza) {
		case 0: 
			printf("%s\n", "Orco");
			break;
		case 1: 
			printf("%s\n", "Humano");
			break;
		case 2: 
			printf("%s\n", "Enano");
			break;
		case 3: 
			printf("%s\n", "Mago");
			break;
		case 4: 
			printf("%s\n", "Elfo");
			break;

		default: printf("%s\n", "Humano");
	}



	
	printf("Nombre: %s\n", datos.ApellidoNombre);
	printf("Edad: %d\n", datos.edad);
	printf("Salud: %.2lf\n", datos.Salud);
	return;
}