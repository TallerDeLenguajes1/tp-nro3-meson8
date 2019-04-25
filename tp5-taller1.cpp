//#include "listah.h"
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

typedef struct Nodo{
	TPersonaje *personaje;
	int id;
	Nodo * siguiente;
}Nodo;


TDatos *cargaDatos ();
void mostrarDatos (TDatos datos);
TCaracteristicas *cargarCarac();
void pelea(TPersonaje  pj1, TPersonaje  pj2);
void Mostrar_Carac(TCaracteristicas carac);
Nodo *CargarLista(Nodo *Start);
TPersonaje seleccionar(Nodo *Start, int n);
void mostrar(TPersonaje personaje);
int main(){
	int n;
	srand(time(NULL));TDatos pj1;

	printf("Ingrese el numero de peleadores:\n");
	scanf("%d", &n);

	Nodo *Start =NULL;


	for (int i = 0; i < n; ++i)
	{
		Start=CargarLista(Start);
		puts("--------------");
	}
	

	int num;
	printf("Ingrese el personaje que quiere ver:");
	scanf("%d", &num);
	
	mostrar(seleccionar(Start, num));

	puts("Elija el primer personaje:");
	int num1, num2;
	scanf("%d", &num1);
	
	
	puts("Elija el Segundo personaje:");
	scanf("%d", &num2);
	
	
	//if (seleccionar(Start, num1) != NULL && ) {
	//	*(seleccionar(Start, num1)->personaje);

	//}
	
	pelea(seleccionar(Start, num1), seleccionar(Start, num2) );



return 0;

}


TDatos *cargaDatos () {

	TDatos *datos;
	datos=(TDatos*)malloc(sizeof(TDatos));
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

	datos->Raza = raza;

	datos->ApellidoNombre = (char *) malloc (10);

	strcpy((datos->ApellidoNombre), Nombres[rand()%6]);

	datos->edad = rand()%300;

	datos->Salud = (double)100;


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
TCaracteristicas* cargarCarac(){
	TCaracteristicas *Carac;
	Carac=(TCaracteristicas*) malloc(sizeof(TCaracteristicas));

	Carac->velocidad = 1+rand()%(11-1);
	Carac->destreza = 1+rand()%(6-1);
	Carac->fuerza = 1+rand()%(11-1);
	Carac->Nivel = 1+rand()%(11-1);
	Carac->Armadura = 1+rand()%(11-1);	
	return Carac;	
}
void Mostrar_Carac(TCaracteristicas carac){
	printf("Velocidad: %d\n", carac.velocidad );
	printf("Destreza: %d\n", carac.destreza);
	printf("Fuerza: %d\n", carac.fuerza);
	printf("Nivel: %d\n", carac.Nivel);
	printf("Armadura: %d\n", carac.Armadura);
}


void pelea(TPersonaje  pj1, TPersonaje  pj2){
		
		int i;
		int MDP=10000;
		for(i=0; i<6; i++){
			double PD1= (pj1.Caracteristicas)->destreza *  (pj1.Caracteristicas)->fuerza *  (pj1.Caracteristicas)->Nivel;
			double ED1= rand()%100;
			double VA1= PD1*ED1;
			double PDEF1= (pj1.Caracteristicas)->Armadura*(pj1.Caracteristicas)->velocidad;
			
			double DP1=(((VA1)-PDEF1)/MDP)*100;
			
			double PDEF2= (pj2.Caracteristicas)->Armadura*(pj2.Caracteristicas)->velocidad;
			double PD2=(pj2.Caracteristicas)->destreza * (pj2.Caracteristicas)->fuerza * (pj2.Caracteristicas)->Nivel;	
			double ED2= rand()%100;
			double VA2= PD2*ED2;
			double DP2=(((VA2)-PDEF2)/MDP)*100;
			if((pj2.DatosPersonales)->Salud> 0 && (pj1.DatosPersonales)->Salud >0){


				if(DP1<MDP){
					(pj1.DatosPersonales)->Salud= (pj1.DatosPersonales)->Salud- DP2;	
					printf("La vida de %s es de %.2lf\n", (pj1.DatosPersonales)->ApellidoNombre, (pj1.DatosPersonales)->Salud);	
				}
				else{
					printf("El ataque de %s fallo\n", (pj1.DatosPersonales)->ApellidoNombre);
				}
				if(DP2<MDP){
					(pj2.DatosPersonales)->Salud= (pj2.DatosPersonales)->Salud - DP1;
					printf("La vida de %s es de %.2lf\n", (pj2.DatosPersonales)->ApellidoNombre, (pj2.DatosPersonales)->Salud);
				}
				else{
					printf("El ataque de %s fallo\n", (pj2.DatosPersonales)->ApellidoNombre);
					
				}	
			}		
		}
	if((pj2.DatosPersonales)->Salud <(pj1.DatosPersonales)->Salud){
		printf("El ganador es %s!\n", (pj1.DatosPersonales)->ApellidoNombre);
		
	}
	if((pj1.DatosPersonales)->Salud < (pj2.DatosPersonales)->Salud){
		printf("El ganador es %s!\n", (pj2.DatosPersonales)->ApellidoNombre);
		
	}
	if((pj1.DatosPersonales)->Salud == (pj2.DatosPersonales)->Salud){
		printf("Es un empate!");
	}

}


Nodo *CargarLista(Nodo *Start){// los personajes
	//defino el nodo
	Nodo *nuevo=NULL;	
	nuevo=(Nodo*) malloc(sizeof(Nodo));
	nuevo->personaje=(TPersonaje*) malloc(sizeof(TPersonaje));
	//cargo los datos
	nuevo->personaje->Caracteristicas= cargarCarac();
	nuevo->personaje->DatosPersonales= cargaDatos();
	if (Start == NULL)
	{
		nuevo->id = 1;
	}
	else {
		nuevo->id= 1 + Start->id;		
	}
	//muestra los datos
	mostrarDatos(*(nuevo->personaje->DatosPersonales));
	Mostrar_Carac(*(nuevo->personaje->Caracteristicas));
	//cuenta, para luego poder recorrer la lista enlazada
	//cont++;
	//pasa al siguente nodo de la lista
	nuevo->siguiente = Start;
	Start=nuevo;
	

	return Start;
   }

TPersonaje seleccionar(Nodo *Start, int n){// le mandaria el contador
	//mostrar(*(Start->personaje));

	while(Start->id != n && Start != NULL)
	{
		Start= Start->siguiente;
		//mostrar(*(Start->personaje));
	}
	if(Start ==NULL){
		printf("No se pudo encontrar personaje");

	}
	return *Start->personaje;
  }

void mostrar(TPersonaje personaje){
	
	mostrarDatos(*(personaje.DatosPersonales));
	Mostrar_Carac(*(personaje.Caracteristicas));


}
