#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"Jorgito", "Borimir", "Conan", "Druid", "Elvish", "Olaf"};
char Apellidos[6][10]={"Jubilus", "Gomez", "Heckles", "Imir", "Juniper"};

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
TCaracteristicas cargarCarac();
//void Cargar_Carac(TCaracteristicas *puntero);
//void Mostrar_Carac(TCaracteristicas *puntero);
//void pelea(TPersonaje  datos1, TPersonaje  Datos2);
void Mostrar_Carac(TCaracteristicas carac);

int main (void) {
	TDatos pj1;
	TDatos pj2;
	TCaracteristicas carac1;
	srand(time(NULL));

	pj1 = cargaDatos();
	pj2 = cargaDatos();
	mostrarDatos(pj1);
	mostrarDatos(pj2);
	
	//puntero = (TCaracteristicas*)malloc(sizeof(TCaracteristicas));
	//Cargar_Carac(puntero);
	carac1 = cargarCarac();	
	//Mostrar_Carac(puntero);
	//mostrarDatos(pj2);
	Mostrar_Carac(carac1);
	//pelea(pj1, pj2);
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
TCaracteristicas cargarCarac(){
	TCaracteristicas Carac;
	Carac.velocidad = 1+rand()%(11-1);
	Carac.destreza = 1+rand()%(6-1);
	Carac.fuerza = 1+rand()%(11-1);
	Carac.Nivel = 1+rand()%(11-1);
	Carac.Armadura = 1+rand()%(11-1);	
	return Carac;	
}
void Mostrar_Carac(TCaracteristicas carac){
	printf("Velocidad: %d\n", carac.velocidad );
	printf("Destreza: %d\n", carac.destreza);
	printf("Fuerza: %d\n", carac.fuerza);
	printf("Nivel: %d\n", carac.Nivel);
	printf("Armadura: %d\n", carac.Armadura);
}
/*
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
}*/
/*
void pelea(TPersonaje  datos1, TPersonaje  Datos2){
		
		int i;
		int MDP=50000;
		for(i=0; i<3; i++){
			double PD1=datos1.destreza * datos1.fuerza * datos1.Nivel;
			double VA1= PD1*ED1;
			double PDEF1= datos1.Armadura*datos1.velocidad;
			double ED1= rand()%100;
			double DP1=(((VA1*ED1)-PDEF1)/MDP)*100;
			
			double PDEF2= Datos2.Armadura*Datos2.velocidad;
			double PD2=Datos2.destreza * Datos2.fuerza * Datos2.Nivel;	
			double ED2= rand()%100;
			double VA2= PD2*ED2;
			double DP2=(((VA2*ED2)-PDEF2)/MDP)*100;
			
			if(DP1<MPD){
				datos1->Salud= datos1->Salud - DP2;	
				printf("La vida de %s es de %lf\n", TPersonaje.dato1, datos1->Salud);	
			}
			else{
				printf("El ataque de %s falló\n", TPersonaje.dato1);
			}
			if(DP2<MPD){
				Datos2->Salud= Datos2->Salud - DP1;
				printf("La vida de %s es de %lf", TPersonaje.dato1, datos1->Salud);
			}
			else{
				printf("El ataque de %s falló\n", TPersonaje.Dato2);
				
			}		
		}
	if(Datos2->Salud <datos1->Salud){
		printf("El ganador es %s\n!", TPersonaje.ApellidoNombre);
		
	}
	if(datos1->Salud < Datos2->Salud){
		printf("El ganador es %s\n!", TPersonaje.ApellidoNombre);
		
	}
	else{
		printf("Es un empate!");
	}
	
}
*/
/*

void peleadores(){
	int i,peleadores;
	printf("Ingrese la cantidad de peleadores:");
	scanf("%d", &peleadores);
	struct arre[peladores];
	for(i=0; i<peleadores; i++0){
		
		
	}
	
	
	
}*/






