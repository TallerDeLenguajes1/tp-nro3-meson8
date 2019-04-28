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
	int id;
} nodo;

//typedef nodo * ListaPJ;


typedef struct ListaPJ {
	nodo *head; //Apunta al inicio de la lista
	int id_actual;
} ListaPJ;


void cargaDatos (TPersonaje * personaje);
void cargarCarac (TPersonaje * personaje);
void creaPJ (TPersonaje **);
void mostrarDatos (TPersonaje * personaje);
void mostrarCarac (TPersonaje * personaje);
void muestraPJ (TPersonaje * personaje);

int peleaPJ(TPersonaje *p1, TPersonaje *p2);

//FUNCIONES DE LISTA
void crearListaPJ (ListaPJ *L);
int esListaVacia (ListaPJ *L);
void insertarPJinicio (ListaPJ *L, TPersonaje *personaje);
void insertarPJfin (ListaPJ *L, TPersonaje *personaje);
void mostrarListaPJ (ListaPJ *L);
nodo * buscarPJ (ListaPJ *L, int num);
void eliminarPrimero (ListaPJ *Lista);
void eliminarX (ListaPJ *Lista, int id_buscado);

// ______________________________________________________________________________________________________

int main (void) {
	int i;
	int cantPJs;
	int num1, num2;
	ListaPJ *Lista;
	TPersonaje * nuevoPJ;
	nodo *pNodo1, *pNodo2;
	int resultado;

	srand(time(NULL));

	crearListaPJ(Lista);

	printf("Escriba la cantidad de personajes:\n");
	scanf("%d", &cantPJs);

	if (cantPJs < 0) {
		printf("Error. Eligio una cantidad negativa\n");
		return 1;
	}

	for (i=0; i<cantPJs; i++) {
		creaPJ(&nuevoPJ);
		insertarPJfin(Lista, nuevoPJ);
	}
	
	printf("\nEstos son los datos y caracteristicas de los %d personajes:\n\n", cantPJs);
	mostrarListaPJ(Lista);
	/*
	//Eliminar el tercero en la lista (prueba de funcion eliminarX())

	printf("Eliminando el tercero\n");
	eliminarX(Lista, 3);
	printf("\n");
	mostrarListaPJ(Lista);
	*/
	printf("Elija su personaje:\n");
	scanf("%d", &num1);
	pNodo1 = buscarPJ(Lista, num1);
	if (pNodo1 == NULL) {
		printf("Error, el personaje no existe en la lista\n");
		return 1;
	}

	printf("Elija su contrincante:\n");
	scanf("%d", &num2);
	pNodo2 = buscarPJ(Lista, num2);	
	if (pNodo2 == NULL) {
		printf("Error, el personaje no existe en la lista\n");
		return 1;
	}
	
	resultado = peleaPJ(pNodo1->pj, pNodo2->pj);

	if (resultado == 1) {
		printf("Ha ganado %s\n", pNodo1->pj->DatosPersonales->ApellidoNombre);
		eliminarX(Lista, num2);
	}
	else if (resultado == 2) {
		printf("Ha ganado %s\n", pNodo2->pj->DatosPersonales->ApellidoNombre);
		eliminarX(Lista, num1);
	}
	else {
		printf("Hubo empate\n");
	}

	//mostrarListaPJ(Lista);

	return 0;
}


// ______________________________________________________________________________________________________

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

void cargarCarac(TPersonaje * personaje){
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

void mostrarCarac(TPersonaje * personaje){
	printf("Velocidad: %d\n", personaje->Caracteristicas->velocidad );
	printf("Destreza: %d\n", personaje->Caracteristicas->destreza);
	printf("Fuerza: %d\n", personaje->Caracteristicas->fuerza);
	printf("Nivel: %d\n", personaje->Caracteristicas->nivel);
	printf("Armadura: %d\n", personaje->Caracteristicas->armadura);
}

void creaPJ (TPersonaje ** personaje) {
	*personaje = (TPersonaje *) malloc(sizeof(TPersonaje));

	cargaDatos(*personaje);
	cargarCarac(*personaje);

	return;
}

void muestraPJ (TPersonaje * personaje) {
	mostrarDatos(personaje);
	mostrarCarac(personaje);
	return;
}

int peleaPJ(TPersonaje *p1, TPersonaje *p2) {
	//Retorna 1 si gana PJ1, 2 si gana PJ2, 0 si hay empate
	int i, miss;
	double poder_disparo, poder_defensa, max_DP, DP, efect_disparo, valor_ataque;
	TPersonaje *pA, *pB;

	max_DP = 500;

	printf("---------------------------------\n");
	printf("%s VS %s\n \n", p1->DatosPersonales->ApellidoNombre, p2->DatosPersonales->ApellidoNombre);	

	for(i=0; i<6;i++) {
		miss = 0;

		//Turno de PJ1 cuando i es par
		//Turno de PJ2 cuando i es impar
		if (i%2 == 0) {
			pA = p1;
			pB = p2;
		}
		else {
			pA = p2;
			pB = p1;
		}

		//Calcular todos los valores necesarios para el combate
		poder_disparo = pA->Caracteristicas->destreza * pA->Caracteristicas->fuerza * pA->Caracteristicas->nivel;
		efect_disparo = ( 5 + rand()%10 ) / 10;
		valor_ataque = poder_disparo * efect_disparo;
		poder_defensa = pB->Caracteristicas->armadura * pB->Caracteristicas->velocidad;
		
		DP =  ( (valor_ataque - poder_defensa) / max_DP ) * 100;
		
		if (DP < 0) {
			//Si el daño resultó negativo, le asigna 0
			DP = 0;
			miss = 1;
		}

		if (pB->DatosPersonales->Salud > DP) {
			//Si el personaje es capaz de recibir el daño y sobrevivir
			pB->DatosPersonales->Salud -= DP;
		}
		else {
			//Si el daño es mayor a la salud del personaje
			//Asigna 0 a la salud de la víctima, para no terminar con salud negativa
			//Y termina las iteraciones para detener el combate
			pB->DatosPersonales->Salud = 0;
			i = 6; 
		}

		//Muestra en pantalla el resultado del turno
		printf("%s ataca a %s\n", pA->DatosPersonales->ApellidoNombre, pB->DatosPersonales->ApellidoNombre);
		//printf("Poder de disparo: %d\n", poder_disparo);
		//printf("Efectividad de disparo: %.2lf\n", efect_disparo);
		//printf("Valor de ataque: %.2lf\n", valor_ataque);
		//printf("Poder de defensa del enemigo: %d\n", poder_defensa);
		if (miss) {
			printf("%s evade el ataque!\n", pB->DatosPersonales->ApellidoNombre);
		}
		else {
			printf("Danio producido: %.2lf\n", DP);
		}
		printf("Salud de %s: %.2lf\n", pB->DatosPersonales->ApellidoNombre, pB->DatosPersonales->Salud);
		printf("\n");
	}
	printf("---------------------------------\n");


	//Al finalizar el combate muestra la salud de cada uno
	printf("Fin del combate\n");
	printf("Salud de %s: %.2lf\n", p1->DatosPersonales->ApellidoNombre, p1->DatosPersonales->Salud);
	printf("Salud de %s: %.2lf\n", p2->DatosPersonales->ApellidoNombre, p2->DatosPersonales->Salud);

	if (p1->DatosPersonales->Salud > p2->DatosPersonales->Salud) {
		//Gana el primer personaje
		return 1;
	}
	else if (p1->DatosPersonales->Salud < p2->DatosPersonales->Salud) {
		//Gana el segundo personaje
		return 2;
	}
	else {
		//Hubo empate
		return 0;
	}
}

void crearListaPJ (ListaPJ *Lista) {
	//Crea una lista vacía
	Lista->head = NULL;
	Lista->id_actual = 1;
	return;
}

int esListaVacia (ListaPJ *Lista){
	//Booleano
	//Retorna 1 si la lista es vacia
	return (Lista->head == NULL);
}

void insertarPJinicio (ListaPJ *Lista, TPersonaje * personaje){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	nodo *nuevo;

	nuevo = (nodo*)malloc(sizeof(nodo));

	nuevo->pj = personaje;
	nuevo->id = Lista->id_actual;
	nuevo->siguiente = Lista->head;
	Lista->head = nuevo;
	Lista->id_actual++;
	return;
}

void insertarPJfin (ListaPJ *Lista, TPersonaje * personaje){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	nodo *nuevo, *p_aux;
	p_aux = Lista->head;

	nuevo = (nodo*)malloc(sizeof(nodo));

	nuevo->pj = personaje;
	nuevo->id = Lista->id_actual;
	nuevo->siguiente = NULL;

	if (esListaVacia(Lista))
	{
		Lista->head = nuevo;
	}
	else {
		while (Lista->head->siguiente != NULL) {
			Lista->head = Lista->head->siguiente;		
		}
		Lista->head->siguiente = nuevo;
		Lista->head = p_aux; //Regresa a la direccion original
	}
	Lista->id_actual++;
	return;
}

void mostrarListaPJ (ListaPJ *Lista) {
	//Muestra los elementos de la lista
	nodo * p_aux = Lista->head;

	if (p_aux == NULL) {
		printf("(Sin personajes)\n");
	}
	else{
		while (p_aux != NULL) {
			printf("Personaje #%d\n", p_aux->id);
			muestraPJ(p_aux->pj);
			printf("\n");
			p_aux = p_aux->siguiente;
		}
	}

	return;
}

nodo * buscarPJ (ListaPJ *Lista, int id_buscado) {
	//Retorna el nodo buscado. Si no se encuentra, retorna NULL;
	nodo * p_aux = Lista->head;
	while (p_aux != NULL) {
		if (p_aux->id == id_buscado) {
			return p_aux;
		}
		p_aux = p_aux->siguiente;
	}
	return p_aux;
}

void eliminarPrimero (ListaPJ *Lista) {
	nodo * p_aux;

	if (esListaVacia(Lista)) {
		return;
	}
	else {
		p_aux = Lista->head;
		Lista->head = Lista->head->siguiente;
		free(p_aux);
		return;
	}
}

void eliminarX (ListaPJ *Lista, int id_buscado) {
	nodo *p_aux, *anterior, *sig;
	p_aux = Lista->head;

	if (esListaVacia(Lista)) {
		printf("No hay elementos para borrar\n");
		return;
	}
	else {

		if (p_aux->siguiente == NULL) {
			//La lista tiene un solo elemento
			if (p_aux->id == id_buscado) {
				//El elemento es el buscado
				eliminarPrimero(Lista);
			}
			else {
				//El elemento no es el buscado
				printf("No se encontro el elemento\n");
			}
		}
		else {
			//La lista tiene mas de un elemento
			if (p_aux->id == id_buscado){
				//El elemento a borrar es el primero
				eliminarPrimero(Lista);
			}
			else {
				anterior = p_aux;
				p_aux = p_aux->siguiente;
				sig = p_aux->siguiente;

				while (sig != NULL && p_aux->id != id_buscado) {
					anterior = p_aux;
					p_aux = p_aux->siguiente;
					sig = p_aux->siguiente;					
				}

				if (p_aux->id == id_buscado) {
					//Se encontró el elemento a eliminar
					anterior->siguiente = sig;
					free(p_aux);
				}
				else {
					//No se encontró el elemento a eliminar
					printf("No se encontro el elemento\n");
				}

			}

		}

	}

}