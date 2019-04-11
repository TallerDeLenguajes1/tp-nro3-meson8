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
	TPersonaje pj;
	nodo * siguiente;
} nodo;


typedef nodo * ListaPJ;

TDatos * cargaDatos (void);
void mostrarDatos (TDatos *datos);

TCaracteristicas *  Cargar_Carac(void);
void Mostrar_Carac(TCaracteristicas *carac);

TPersonaje cargaPJ (void);
void muestraPJ (TPersonaje pj);

void peleaPJ(TPersonaje *p1, TPersonaje *p2);




ListaPJ crearListaPJ ();
int esListaVacia (ListaPJ L);
void insertarPJ (ListaPJ *L, TPersonaje personaje);
void mostrarListaPJ (ListaPJ L);
TPersonaje* selectorPJ (ListaPJ L, int num);

// ___________________________________________________
//                      MAIN
// ___________________________________________________

int main (void) {
	int i;
	int cantPJs;
	int num1, num2;
	ListaPJ lista;

	srand(time(NULL));

	lista = crearListaPJ();

	printf("Escriba la cantidad de personajes:\n");
	scanf("%d", &cantPJs);

	//if (cantPJs <0) {
	//	cantPJs *= -1; 
	//}



	for (i=0; i<cantPJs; i++) {
		insertarPJ(&lista, cargaPJ());
	}



	printf("\nEstos son los datos y caracteristicas de los %d personajes:\n", cantPJs);
	mostrarListaPJ(lista);
	


	printf("Elija su personaje:\n");
	scanf("%d", &num1);
	printf("Elija su contrincante:\n");
	scanf("%d", &num2);

	printf("PJ1 vs PJ2\n");
	printf("%p\n", selectorPJ(lista, num1));
	printf("%p\n", selectorPJ(lista, num2));
	peleaPJ(selectorPJ(lista, num1), selectorPJ(lista, num2));


	return 0;
}


// ___________________________________________________
//                   DEFINICIONES
// ___________________________________________________

TDatos* cargaDatos (void) {
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
	return datos;
}

void mostrarDatos (TDatos *datos) {

printf("Raza: ");
switch(datos->Raza) {
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

	printf("Nombre: %s\n", datos->ApellidoNombre);
	printf("Edad: %d\n", datos->edad);
	printf("Salud: %.2lf\n", datos->Salud);
	return;
}



TCaracteristicas* Cargar_Carac(void){
	TCaracteristicas *carac; 

	carac = (TCaracteristicas*)malloc(sizeof(TCaracteristicas));

	carac->velocidad = 1+rand()%(11-1);
	carac->destreza = 1+rand()%(6-1);
	carac->fuerza = 1+rand()%(11-1);
	carac->nivel = 1+rand()%(11-1);
	carac->armadura = 1+rand()%(11-1);

	return carac;
}
void Mostrar_Carac(TCaracteristicas *carac){
	printf("Velocidad: %d\n", carac->velocidad );
	printf("Destreza: %d\n", carac->destreza);
	printf("Fuerza: %d\n", carac->fuerza);
	printf("Nivel: %d\n", carac->nivel);
	printf("Armadura: %d\n", carac->armadura);
}


TPersonaje cargaPJ (void) {
	TPersonaje pj;

	pj.DatosPersonales =cargaDatos();
	pj.Caracteristicas = Cargar_Carac();

	return pj;
}

void muestraPJ (TPersonaje pj) {
	mostrarDatos(pj.DatosPersonales);
	Mostrar_Carac(pj.Caracteristicas);
	return;
}


void peleaPJ(TPersonaje *p1, TPersonaje *p2) {
	int i;
	int resultado; //1 si gana PJ1, 2 si gana PJ2, 0 si hay empate
	int podrDisp, podrDef, maxDP;
	double DP, efDisp, valorAtk;
	TPersonaje *pA, *pB;
	TCaracteristicas caracA, caracB;

	maxDP = 5000;
	resultado = 0;

	for(i=0; i<6;i++) {
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
		efDisp = (double) (1 + rand()%100)/100;
		valorAtk = (double) podrDisp * efDisp;
		podrDef = caracB.armadura * caracB.velocidad;
		
		DP =  ((double)(valorAtk - podrDef)/ (double)maxDP)*100;
		
		if (DP < 0) {
			DP = 0;
		}

		pB->DatosPersonales->Salud -= DP;

		printf("\nTurno #%d\n", i+1);
		printf("%s ataca a %s\n", pA->DatosPersonales->ApellidoNombre, pB->DatosPersonales->ApellidoNombre);
		printf("Poder de disparo: %d\n", podrDisp);
		printf("Efectividad de disparo: %.2lf\n", efDisp);
		printf("Valor de ataque: %.2lf\n", valorAtk);
		printf("Defensa del enemigo: %d\n", podrDef);
		printf("Danio producido: %.2lf\n", DP);
		printf("Salud de %s: %.2lf\n", pB->DatosPersonales->ApellidoNombre, pB->DatosPersonales->Salud);
	}


	printf("\nSalud de %s: %.2lf\n", p1->DatosPersonales->ApellidoNombre, p1->DatosPersonales->Salud);
	printf("\nSalud de %s: %.2lf\n", p2->DatosPersonales->ApellidoNombre, p2->DatosPersonales->Salud);

	if (p1->DatosPersonales->Salud > p2->DatosPersonales->Salud) {
		printf("\nGana %s", p1->DatosPersonales->ApellidoNombre);
	}
	else if (p1->DatosPersonales->Salud > p2->DatosPersonales->Salud){

		printf("\nGana %s\n", p2->DatosPersonales->ApellidoNombre);

	}
	else {
		printf("\nEmpate\n");
		printf("p1:\n");
		printf("p2:\n");
	}

	

	return;
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

void insertarPJ (ListaPJ *L, TPersonaje personaje){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	nodo *nuevo;

	nuevo = (nodo*)malloc(sizeof(nodo));

	nuevo->pj = personaje;
	nuevo->siguiente = *L;

	*L = nuevo;
	return;
}

void mostrarListaPJ (ListaPJ L) {
	//Muestra los elementos de la lista
	int i = 0;

	if (esListaVacia(L)) {
		printf("(Sin personajes)");
	}
	else{
		while (esListaVacia(L) != 1) {
			printf("Personaje #%d\n", i+1);
			muestraPJ(L->pj);
			printf("\n");
			L = L->siguiente;
			i++;
		}
	}

	return;
}


TPersonaje* selectorPJ (ListaPJ L, int num) {
	int i=0;
	ListaPJ Laux = L;
	while (i<num-1 && Laux != NULL) {
		printf("siguiente\n");
		Laux = Laux->siguiente;
		i++;
	}
	return &(Laux->pj);
}