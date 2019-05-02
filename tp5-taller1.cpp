//#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"Jorgito", "Borimir", "Conan", "Ancalagon", "Kreindor", "Olaf"};
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
TPersonaje pelea(TPersonaje  pj1, TPersonaje  pj2,Nodo *Start);
void Mostrar_Carac(TCaracteristicas carac);
Nodo *CargarLista(Nodo *Start);
Nodo  *seleccionar(Nodo *Start, int n);
//void mostrar(TPersonaje personaje);
//void mostrar(Nodo Start, int idpersonaje);
//------------------Funciones el tp5
void EliminarNodo(Nodo * nodo);
void InsertarNodo(Nodo * Start , int valor);
void InsertarAlFinal(Nodo * Start, Nodo * Nodo);
void QuitarNodoDeUnaPosicion(Nodo * Start, int posicion);
Nodo * CrearNodo(int valor);
//--------------------

int main(){
	int n;
	srand(time(NULL));TDatos pj1;
	Nodo *Start =NULL;


	for (int i = 0; i < 8; ++i)
	{
		Start=CargarLista(Start);
		puts("--------------");
	}
	
	Nodo *nodo1=seleccionar(Start, 1);
	Nodo *nodo2=seleccionar(Start, 2);
	Nodo *nodo3=seleccionar(Start, 3);
	Nodo *nodo4=seleccionar(Start, 4);
	Nodo *nodo5=seleccionar(Start, 5);
	Nodo *nodo6=seleccionar(Start, 6);
	Nodo *nodo7=seleccionar(Start, 7);
	Nodo *nodo8=seleccionar(Start, 8);
		
	printf("---Pelea del grupo 1---\n");
	TPersonaje grupo1=pelea(*nodo1->personaje, *nodo2->personaje, Start);
	printf("---Pelea del grupo 2---\n");
	TPersonaje grupo2=pelea(*nodo3->personaje, *nodo4->personaje, Start);
	printf("---Pelea del grupo 3---\n");
	TPersonaje grupo3=pelea(*nodo5->personaje, *nodo6->personaje, Start);
	printf("---Pelea del grupo 4---\n");
	TPersonaje grupo4=pelea(*nodo7->personaje, *nodo8->personaje,Start);
	
	//puts("Elija el personaje a quitar:");
	//int num3;
	//scanf("%d", &num3);
	//QuitarNodoDeUnaPosicion( Start , num3);
	//mostrar(seleccionar(Start, num3));
	printf("---Semifinal---\n");
	TPersonaje final1=pelea(grupo1, grupo2,Start);
	TPersonaje final2=pelea(grupo3, grupo4, Start);

	printf("---BATALLA FINAL---\n");
	TPersonaje ganador=pelea(final1, final2, Start);



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


TPersonaje pelea(TPersonaje  pj1, TPersonaje  pj2, Nodo *Start){
		
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
		(pj2.DatosPersonales)->Salud=(pj2.DatosPersonales)->Salud + 12;//Bonificacion de salud
		QuitarNodoDeUnaPosicion(Start,2 );
		return (pj1);
	}
	if((pj1.DatosPersonales)->Salud < (pj2.DatosPersonales)->Salud){
		printf("El ganador es %s!\n", (pj2.DatosPersonales)->ApellidoNombre);
		QuitarNodoDeUnaPosicion(Start, 1);
		(pj2.DatosPersonales)->Salud=(pj2.DatosPersonales)->Salud + 12;

		return (pj2);	
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

Nodo *seleccionar(Nodo *Start, int n){// le mandaria el contador
	//mostrar(*(Start->personaje));
	//RETORNA UN PUNTERO A NODO O null SI NO EXISTE

	while(Start->id != n && Start != NULL)
	{
		Start= Start->siguiente;
		//mostrar(*(Start->personaje));
	}
	if(Start ==NULL){
		printf("No se pudo encontrar personaje");
	}
	return Start;
  }
/*
void mostrar(TPersonaje personaje){
	mostrarDatos(*(personaje.DatosPersonales));
	Mostrar_Carac(*(personaje.Caracteristicas));
}*/
/*
void mostrar(Nodo Start, int idpersonaje){

	while(Start->id != n && Start != NULL)
	{
		Start= Start->siguiente;
		//mostrar(*(Start->personaje));
	}
	mostrarDatos(*(personaje.DatosPersonales));
	Mostrar_Carac(*(personaje.Caracteristicas));


}*/
void EliminarNodo(Nodo * nodo){
    if (!nodo) free(nodo);
    printf("Se elimino un nodo exitosamente");
}



void InsertarNodo(Nodo * Start , int valor){
    Nodo * NuevoNodo = CrearNodo(valor);
    NuevoNodo -> siguiente = Start;
    Start  = NuevoNodo ;
    printf("Se inserto un nodo al principio exitosamente");
}

/*
void InsertarAlFinal(Nodo * Start, Nodo * Nodo){
    Nodo * NuevoNodo = CrearNodo(valor);
    Nodo * Aux = Start;
    while(Aux->siguiente) 
    {
	Aux = Aux -> siguiente;
    } 
    NuevoNodo -> siguiente = Start;
    Start  = NuevoNodo ;
}
*/
void QuitarNodoDeUnaPosicion(Nodo * Start, int posicion){
	int contador = 0;
	Nodo * Aux = Start;
	Nodo * Anterior; 
    	while( contador < posicion  && Aux) 
    	{
		Anterior = Aux;
		Aux = Aux -> siguiente;
		contador++;
    	}

   	 if(!Aux)
    	{
    	Anterior -> siguiente = Aux -> siguiente;	  
		EliminarNodo(Aux);
    
    	}
	printf("Se elimino un nodo intermedio exitosamente\n");
}


Nodo * CrearNodo(int valor){
	Nodo *NNodo= (Nodo *) malloc (sizeof(Nodo));
	NNodo->id = rand() % 99;
	NNodo->siguiente = NULL;
	printf("Se creo un nodo exitosamente" );
	return NNodo;
}


