#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"jorgito", "b", "c", "d", "e", "Olaf"};
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
	int nivel; //1 a 10
	int armadura; //1 a 10
} TCaracteristicas;

typedef struct TPersonaje {
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
} TPersonaje;


typedef struct nodo {
	TPersonaje * pj;
	nodo * siguiente;
} nodo;



typedef nodo * ListaPJ;


void cargaDatos (void);
void mostrarDatos (TPersonaje * personaje);
void Cargar_Carac(void);
void Mostrar_Carac(TPersonaje * personaje);
TPersonaje * cargaPJ (void);
void muestraPJ (TPersonaje * personaje);

int peleaPJ(TPersonaje *p1, TPersonaje *p2);




ListaPJ crearListaPJ (void);
int esListaVacia (ListaPJ L);
void insertarPJ (ListaPJ *L, TPersonaje *personaje);
void mostrarListaPJ (ListaPJ *L);

nodo * selectorPJ (ListaPJ *L, int num);


// ___________________________________________________
//                      MAIN
// ___________________________________________________

int main (void) {
	int i;
	int cantPJs;
	int num1, num2;
	ListaPJ *pLista;
	nodo *pNodo1, *pNodo2;

	srand(time(NULL));

	*pLista = crearListaPJ();

	printf("Escriba la cantidad de personajes:\n");
	scanf("%d", &cantPJs);

	//if (cantPJs <0) {
	//	cantPJs *= -1; 
	//}



	for (i=0; i<cantPJs; i++) {
		insertarPJ(pLista, cargaPJ());
	}


	
	printf("\nEstos son los datos y caracteristicas de los %d personajes:\n", cantPJs);
	mostrarListaPJ(pLista);
	


	printf("Es lista nula? %s\n", esListaVacia(*pLista)?"si":"no");

	printf("Elija su personaje:\n");
	scanf("%d", &num1);
	pNodo1 = selectorPJ(pLista, num1);

	printf("Elija su contrincante:\n");
	scanf("%d", &num2);
	pNodo2 = selectorPJ(pLista, num2);

	

	if (pNodo1 == NULL || pNodo2 == NULL) {
		printf("Error\n");
	}
	else {
		printf("PJ1 vs PJ2\n");
		peleaPJ(pNodo1->pj, pNodo2->pj);	
	}

	

	return 0;
}


// ___________________________________________________
//                   DEFINICIONES
// ___________________________________________________

void cargaDatos (TPersonaje * personaje) {
	TDatos *datos;
	enum TRaza raza;

	datos = (TDatos*) malloc (sizeof(TDatos));

	//Determinar Raza
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
	
	personaje->DatosPersonales = datos;
}

void mostrarDatos (TPersonaje * personaje) {



printf("Raza: ");
switch(personaje->DatosPersonales->Raza) {
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

	printf("Nombre: %s\n", personaje->DatosPersonales->ApellidoNombre);
	printf("Edad: %d\n", personaje->DatosPersonales->edad);
	printf("Salud: %.2lf\n", personaje->DatosPersonales->Salud);

	return;
}



void Cargar_Carac(TPersonaje * personaje){
	TCaracteristicas *carac; 

	carac = (TCaracteristicas*)malloc(sizeof(TCaracteristicas));

	carac->velocidad = 1+rand()%(11-1);
	carac->destreza = 1+rand()%(6-1);
	carac->fuerza = 1+rand()%(11-1);
	carac->nivel = 1+rand()%(11-1);
	carac->armadura = 1+rand()%(11-1);

	personaje->Caracteristicas = carac;

	return;
}

void Mostrar_Carac(TPersonaje * personaje){
	printf("Velocidad: %d\n", personaje->Caracteristicas->velocidad );
	printf("Destreza: %d\n", personaje->Caracteristicas->destreza);
	printf("Fuerza: %d\n", personaje->Caracteristicas->fuerza);
	printf("Nivel: %d\n", personaje->Caracteristicas->nivel);
	printf("Armadura: %d\n", personaje->Caracteristicas->armadura);
}


TPersonaje * cargaPJ (void) {
	TPersonaje * personaje;

	personaje = (TPersonaje *) malloc(sizeof(TPersonaje));

	cargaDatos(personaje);
	Cargar_Carac(personaje);

	return personaje;
}

void muestraPJ (TPersonaje * personaje) {
	mostrarDatos(personaje);
	Mostrar_Carac(personaje);
	return;
}


int peleaPJ(TPersonaje *p1, TPersonaje *p2) {
	//Retorna 1 si gana PJ1, 2 si gana PJ2, 0 si hay empate
	int i;
	int podrDisp, podrDef, maxDP;
	double DP, efDisp, valorAtk;
	TPersonaje *pA, *pB;
	TCaracteristicas caracA, caracB;

	maxDP = 500;

	for(i=0; i<6;i++) {
		printf("\nTurno #%d\n", i+1);
		//Turno de PJ1 cuando i es par
		//Turno de PJ2 cuando i es impar
		if (i%2 == 0) {
			pA = p1;
			pB = p2;
			caracA = *(pA->Caracteristicas);
			caracB = *(pB->Caracteristicas);
		}
		else {
			pA = p2;
			pB = p1;
			caracA = *(p2->Caracteristicas);
			caracB = *(p1->Caracteristicas);
		}

		podrDisp = caracA.destreza * caracA.fuerza * caracA.nivel;
		efDisp = (double) (5 + rand()%10)/10;
		valorAtk = (double) podrDisp * efDisp;

		podrDef = caracB.armadura * caracB.velocidad;
		
		DP =  ((double)(valorAtk - podrDef)/ (double)maxDP)*100;
		
		if (DP < 0) {
			DP = 0;
		}

		if (pB->DatosPersonales->Salud > DP) {
			pB->DatosPersonales->Salud -= DP;
		}
		else {
			pB->DatosPersonales->Salud = 0;
			i = 6;
		}

		printf("%s ataca a %s\n", pA->DatosPersonales->ApellidoNombre, pB->DatosPersonales->ApellidoNombre);
		printf("Poder de disparo: %d\n", podrDisp);
		printf("Efectividad de disparo: %.2lf\n", efDisp);
		printf("Valor de ataque: %.2lf\n", valorAtk);
		printf("Poder de defensa del enemigo: %d\n", podrDef);
		printf("Danio producido: %.2lf\n", DP);
		printf("Salud de %s: %.2lf\n", pB->DatosPersonales->ApellidoNombre, pB->DatosPersonales->Salud);
	}


	printf("\nSalud de %s: %.2lf\n", p1->DatosPersonales->ApellidoNombre, p1->DatosPersonales->Salud);
	printf("\nSalud de %s: %.2lf\n", p2->DatosPersonales->ApellidoNombre, p2->DatosPersonales->Salud);

	if (p1->DatosPersonales->Salud > p2->DatosPersonales->Salud) {
		printf("\nGana %s", p1->DatosPersonales->ApellidoNombre);
		return 1;
	}
	else if (p1->DatosPersonales->Salud < p2->DatosPersonales->Salud){
		printf("\nGana %s\n", p2->DatosPersonales->ApellidoNombre);
		return 2;
	}
	else {
		printf("\nEmpate\n");
		return 0;
	}
}


ListaPJ crearListaPJ () {
	//Crea una lista vacía
	return NULL;
}

int esListaVacia (ListaPJ L){
	//Booleano
	//Retorna 1 si la lista es vacia
	return (L == NULL);
}

void insertarPJ (ListaPJ *L, TPersonaje * personaje){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	nodo *nuevo;

	nuevo = (nodo*)malloc(sizeof(nodo));

	nuevo->pj = personaje;
	nuevo->siguiente = *L;

	*L = nuevo;
	return;
}

void mostrarListaPJ (ListaPJ *L) {
	//Muestra los elementos de la lista
	int i = 0;
	ListaPJ Laux = *L;

	if (esListaVacia(*L)) {
		printf("(Sin personajes)");
	}
	else{
		while (esListaVacia(*L) != 1) {
			printf("Personaje #%d\n", i+1);
			muestraPJ((*L)->pj);
			printf("\n");
			*L = (*L)->siguiente;
			i++;
		}
		*L = Laux;
	}

	return;
}


nodo * selectorPJ (ListaPJ *L, int num) {
	//Retorna el nodo buscado. Si no se encuentra, retorna NULL
	int i=0;
	ListaPJ Laux = *L;
	while (i<num-1 && Laux != NULL) {
		Laux = Laux->siguiente;
		i++;
	}
	return Laux;
}