#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*enum TRaza{Orco, Humano, Mago, Enano, Elfo}
char Nombres[6][10]={"ale", "b", "c", "d", "e"}
char Apellidos[6][10]={"f", "g", "hormiga", "i", "j"}*/

/*typedef struct TDatos {
	TRaza Raza; //nota 1
	Char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud://100
} TDatos;*/

typedef struct TCaracteristicas{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
} TCaracteristicas;

/*typedef struct TPersonaje {
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
} TPersonaje;*/


void Cargar_Carac(TCaracteristicas *puntero);
void Mostrar_Carac(TCaracteristicas *puntero);
int main () {
	TCaracteristicas *puntero;
	puntero = (TCaracteristicas*)malloc(sizeof(TCaracteristicas));
	Cargar_Carac(puntero);
	Mostrar_Carac(puntero);
	return 0;
}

void Cargar_Carac(TCaracteristicas *puntero){
	puntero->velocidad = 1+rand()%(11-1);
	puntero->destreza = 1+rand()%(6-1);
	puntero->fuerza = 1+rand()%(11-1);
	puntero->Nivel = 1+rand()%(11-1);
	puntero->Armadura = 1+rand()%(11-1);
}
void Mostrar_Carac(TCaracteristicas *puntero){
	printf("Velocidad: %d\n", puntero->velocidad );
	printf("Destreza: %d\n", puntero->destreza);
	printf("Fuerza: %d\n", puntero->fuerza);
	printf("Nivel: %d\n", puntero->Nivel);
	printf("Armadura: %d\n", puntero->Armadura);
}
//grupo2