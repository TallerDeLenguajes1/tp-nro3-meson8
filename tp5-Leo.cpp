#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lib_List_Punto2Tp5.h"

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"Jorgito", "Daven", "Chavo", "Gerd", "Haakon", "Olaf"};
char Apellidos[6][10]={"Alfaro", "Wayne", "Harald", "Burro", "Zlatan", "Trygg"};

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
	TPersonaje *Datos_Personajes;
	Nodo *Siguiente;
	int id;
}Nodo;

//typedef Nodo *Lista;
typedef struct Lista{
	Nodo *head; //Apunta al inicio de la lista
	int id_actual;
} Lista;

//------------------------------------------------Declaracion de Funciones------------------------------------------------
void CrearLista(Lista *L);
void Menu(Lista *Lista_Per);
int esListaVacia (Lista *L);
void eliminarPrimero (Lista *Lista_Per); 
void eliminarX (Lista *Lista, int id_buscado);
void Crear_Personaje (TPersonaje ** Personaje);
void Cargar_Datos(TPersonaje *Personaje);
void Cargar_Carac(TPersonaje *Personaje);
void Mostrar_Datos (TPersonaje *Personaje);
void Mostrar_Carac(TPersonaje *Personaje);
void Muestra_Per (TPersonaje *Per);
void Mostrar_Lista (Lista *Lista);
void InsertarAlFinal (Lista *L, TPersonaje * Personaje);
void Uno_vs_Uno(Lista *L); 
Nodo *Personaje_Elejido(Lista *L, int num);
void Verif_Per(TPersonaje *Per_1, TPersonaje *Per_2, char Nom_Per1[], char Nom_Per2[]);
void Resul_enfrent(TPersonaje *Per_1, TPersonaje *Per_2);
void campeonato(Lista *L);
int tamanioLista (Lista *Lista_Per);
int Resultado_Peleas(TPersonaje *Per_1, TPersonaje *Per_2);
void Suma_Poderes(TPersonaje *Personaje);
//------------------------------------------------------------------------------------------------------------------------
int main (void) {
	Lista *Lista_Per;
	TPersonaje *Nuevo;

	int Cant_Per = 8;
	srand(time(NULL));

	//Lista_Per = NULL;
	CrearLista(Lista_Per);
	for (int i = 0; i < Cant_Per; ++i){
		Crear_Personaje (&Nuevo);
		InsertarAlFinal (Lista_Per, Nuevo);
	}
	printf("------------------------Personajes------------------------\n\n");
	Mostrar_Lista (Lista_Per);
	Pausar();
	Menu(Lista_Per);
	
	return 0;
}

void Menu(Lista *Lista_Per){
	int OP, Num_Per;
	char continuar;
	TPersonaje *Nuevo;

	do{
		OP = Opciones_Menu();
	    switch(OP){
	    	case 0:
	    	   printf("\n\n------------------------------1 vs 1--------------------------------\n\n");
	    	   Uno_vs_Uno(Lista_Per);
	    	   break;
	    	case 1:
	    	   printf("\n\n------------------------Batalla de Winterfell-----------------------\n\n");
	    	   campeonato(Lista_Per);
	    	   break;
	    	case 2:
	    	   Salir();
	    	   break;
	    	/*case 3:
	           //batalla(Lista_Per);
	           break;*/
	    }
	    printf("\n\n");
	    continuar = Continuar();
	    if(continuar =='n' || continuar=='N'){
	    	exit(0);
	    }
	}while(continuar=='S' || continuar=='s');
}

//------------------------------------------------Funciones para las listas
void CrearLista(Lista *L){
	L->head = NULL;
	L->id_actual =1;
}

void InsertarAlFinal (Lista *L, TPersonaje * Personaje){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	Nodo *nuevo, *p_aux;
	p_aux = L->head;

	nuevo = (Nodo*)malloc(sizeof(Nodo));

	nuevo->Datos_Personajes = Personaje;
	nuevo->id = L->id_actual;
	nuevo->Siguiente = NULL;

	if (esListaVacia(L)) L->head = nuevo;
	else {
		while (L->head->Siguiente != NULL) {
			L->head = L->head->Siguiente;		
		}
		L->head->Siguiente = nuevo;
		L->head = p_aux; //Regresa a la direccion original
	}
	L->id_actual++;
}
void Mostrar_Lista (Lista *Lista) {
	//Muestra los elementos de la lista
	Nodo * p_aux = Lista->head;

	if (p_aux == NULL) {
		printf("(Sin personajes)\n");
	}
	else{
		while (p_aux != NULL) {
			printf("------Personaje Nº[%d]\n", p_aux->id);
			Muestra_Per (p_aux->Datos_Personajes);
			printf("\n");
			p_aux = p_aux->Siguiente;
		}
	}
}
int esListaVacia (Lista *L){
	return (L->head == NULL);
}
int tamanioLista (Lista *Lista_Per) {
	int tama = 0;
	Nodo *p_aux = Lista_Per->head;

	while (p_aux != NULL) {
		tama++;
		p_aux= p_aux->Siguiente;
	}
	return tama;
}
void eliminarPrimero (Lista *Lista) {
	Nodo * p_aux;

	if (esListaVacia(Lista)) {
		return;
	}
	else {
		p_aux = Lista->head;
		Lista->head = Lista->head->Siguiente;
		free(p_aux);
	}
}

void eliminarX (Lista *Lista_Per, int id_buscado) {
	Nodo *p_aux, *anterior, *sig;
	p_aux = Lista_Per->head;

	if (esListaVacia(Lista_Per)) {
		printf("No hay elementos para borrar\n");
		return;
	}
	else {

		if (p_aux->Siguiente == NULL) {
			//La lista tiene un solo elemento
			if (p_aux->id == id_buscado) {
				//El elemento es el buscado
				eliminarPrimero(Lista_Per);
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
				eliminarPrimero(Lista_Per);
			}
			else {
				anterior = p_aux;
				p_aux = p_aux->Siguiente;
				sig = p_aux->Siguiente;

				while (sig != NULL && p_aux->id != id_buscado) {
					anterior = p_aux;
					p_aux = p_aux->Siguiente;
					sig = p_aux->Siguiente;					
				}

				if (p_aux->id == id_buscado) {
					//Se encontró el elemento a eliminar
					anterior->Siguiente = sig;
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
//------------------------------------------------Funciones para cargar los datos
void Crear_Personaje(TPersonaje ** Personaje) {
	*Personaje = (TPersonaje *) malloc(sizeof(TPersonaje));

	Cargar_Datos(*Personaje);
	Cargar_Carac(*Personaje);
}

void Cargar_Datos(TPersonaje *Personaje){
	TDatos *Datos = (TDatos*)malloc(sizeof(TDatos));
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

	    Datos->Raza = raza;
	    Datos->ApellidoNombre = (char *) malloc (30);
 		strcpy((Datos->ApellidoNombre), Nombres[rand()%6]);
 		strcat((Datos->ApellidoNombre), ", ");
 		strcat((Datos->ApellidoNombre), Apellidos[rand()%6]);

	    Datos->edad = rand()%300;
	    Datos->Salud = (double)100;

	    Personaje->DatosPersonales=Datos;
}
void Cargar_Carac(TPersonaje *Personaje){
	TCaracteristicas * Car = (TCaracteristicas *) malloc(sizeof(TCaracteristicas));

	Car->velocidad =1+ rand()%(10);// 1 a 10
	Car->destreza = 1+ rand()%(5); //1 a 5
	Car->fuerza =   1+ rand()%(10);//1 a 10
	Car->Nivel =    1+rand()%(10); //1 a 10
	Car->Armadura = 1+rand()%(10); //1 a 10 

	Personaje->Caracteristicas=Car;
}

void Mostrar_Datos (TPersonaje *Personaje) {

printf("Raza: ");
switch(Personaje->DatosPersonales->Raza) {
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

	printf("Nombre: %s\n", Personaje->DatosPersonales->ApellidoNombre);
	printf("Edad: %d\n", Personaje->DatosPersonales->edad);
	printf("Salud: %.2lf\n", Personaje->DatosPersonales->Salud);
}
void Mostrar_Carac(TPersonaje *Personaje){
	printf("Velocidad: %d\n", Personaje->Caracteristicas->velocidad );
	printf("Destreza: %d\n", Personaje->Caracteristicas->destreza);
	printf("Fuerza: %d\n", Personaje->Caracteristicas->fuerza);
	printf("Nivel: %d\n", Personaje->Caracteristicas->Nivel);
	printf("Armadura: %d\n", Personaje->Caracteristicas->Armadura);
}

void Muestra_Per (TPersonaje *Per) {
	Mostrar_Datos(Per);
	Mostrar_Carac(Per);
}
void Suma_Poderes(TPersonaje *Personaje){
	Personaje->Caracteristicas->velocidad = Personaje->Caracteristicas->velocidad + 10; 
	Personaje->Caracteristicas->destreza = Personaje->Caracteristicas->destreza + 10;
	Personaje->Caracteristicas->fuerza = Personaje->Caracteristicas->fuerza + 10;
	Personaje->Caracteristicas->Nivel = Personaje->Caracteristicas->Nivel + 10;
	Personaje->Caracteristicas->Armadura = Personaje->Caracteristicas->Armadura + 10;
}

//------------------------------------------------Funciones para la pelea
Nodo *Personaje_Elejido(Lista *L, int num){
	//Retorna el nodo buscado. Si no se encuentra, retorna NULL;
	Nodo *aux=L->head;
	
	while(aux != NULL){
		if (aux->id == num){
			return aux;
		}
		aux=aux->Siguiente;
	}
	return aux;
}
void Verif_Per(TPersonaje *Per_1, TPersonaje *Per_2, char Nom_Per1[], char Nom_Per2[]){
	//Verifico si es el mismo personaje

	//Por el numero del personaje
	if (Per_1==Per_2 && Per_1->DatosPersonales->ApellidoNombre == Per_2->DatosPersonales->ApellidoNombre){
		strcpy((Nom_Per1), Per_1->DatosPersonales->ApellidoNombre);
 		strcat((Nom_Per1), " [ROJO] ");
 		strcpy((Nom_Per2), Per_2->DatosPersonales->ApellidoNombre);
 		strcat((Nom_Per2), " [AZUL] ");
 		printf("\n\n | %s VS %s |\n\n", Nom_Per1, Nom_Per2);
	}
	else{
		if (Per_1->DatosPersonales->ApellidoNombre == Per_2->DatosPersonales->ApellidoNombre){
			strcpy((Nom_Per1), Per_1->DatosPersonales->ApellidoNombre);
			switch(Per_1->DatosPersonales->Raza) {
		        case 0: 
			        strcat((Nom_Per1), " [Orco] ");
			        break;
		        case 1: 
			        strcat((Nom_Per1), " [Humano] ");
			        break;
		        case 2: 
			        strcat((Nom_Per1), " [Enano] ");
			        break;
		        case 3: 
			        strcat((Nom_Per1), " [Mago] ");
			        break;
		        case 4: 
			        strcat((Nom_Per1), " [Elfo] ");
			        break;

		        default: strcat((Nom_Per1), " [Humano] ");
	        }
 		    strcpy((Nom_Per2), Per_2->DatosPersonales->ApellidoNombre);
 		    //strcat((Nom_Per2), " [AZUL] ");
 		    switch(Per_2->DatosPersonales->Raza) {
		        case 0: 
			        strcat((Nom_Per2), " [Orco] ");
			        break;
		        case 1: 
			        strcat((Nom_Per2), " [Humano] ");
			        break;
		        case 2: 
			        strcat((Nom_Per2), " [Enano] ");
			        break;
		        case 3: 
			        strcat((Nom_Per2), " [Mago] ");
			        break;
		        case 4: 
			        strcat((Nom_Per2), " [Elfo] ");
			        break;

		        default: strcat((Nom_Per2), " [Humano] ");
	        }
 		    printf("\n\n | %s VS %s |\n\n", Nom_Per1, Nom_Per2);
		}
		else{
		strcpy((Nom_Per1), Per_1->DatosPersonales->ApellidoNombre);
 		strcpy((Nom_Per2), Per_2->DatosPersonales->ApellidoNombre);
 		printf("\n\n | %s VS %s |\n\n", Nom_Per1, Nom_Per2);
	    }
	}
	Pausar();
}

//------------------------------------------------1 VS 1
void Uno_vs_Uno(Lista *L){
	int per_1, per_2;
	Nodo *N1, *N2;

	printf("--Primer contrincante\n");
	per_1 = num_personaje();
	printf("--Segundo contrincante\n");
	per_2 = num_personaje();

	N1 = Personaje_Elejido(L, per_1);
	N2 = Personaje_Elejido(L, per_2);

	//Veo si existe algun problema con los personajes
	if (N1 == NULL && N2 == NULL){
		printf("Hay problemas con los personajes\n");
		exit(0);
	}
	else{
		if (N2 == NULL){
			printf("Hay problemas con el 2do personaje\n");
		    exit(0);
		}
		else{
			if (N1 == NULL){
				printf("Hay problemas con el 1er personaje\n");
		        exit(0);
			}
			else Resul_enfrent(N1->Datos_Personajes, N2->Datos_Personajes);
		}
	}
}

void Resul_enfrent(TPersonaje *Per_1, TPersonaje *Per_2){
	int x, Max_danio = 10000;
	double efec_disparo1, efec_disparo2, danio1, salud1, danio2, salud2;
	int poder_disparo2,  valor_ataq2, poder_defensa2;
	int poder_disparo1, poder_defensa1,valor_ataq1;
	char Nom_Per1[30], Nom_Per2[30];

	salud1 = Per_1->DatosPersonales->Salud;
	salud2 = Per_2->DatosPersonales->Salud;

	Verif_Per(Per_1, Per_2, Nom_Per1, Nom_Per2);

	for (int i = 0; i < 6; ++i){
		printf("---Maximo danio: %d\n\n", Max_danio);
		printf("TURNO: %d\n", i+1);
		//Veo quien inicia atacando
		//1 Primer personaje - 2 Segundo personaje
		if((i%2)==0){x=2;}
		else x=1;

		if (x==1){
		   //Ataque del primer personaje
		   poder_disparo1 = (Per_1->Caracteristicas->destreza * Per_1->Caracteristicas->fuerza * Per_1->Caracteristicas->Nivel);
		   efec_disparo1 = (double)(1+rand()%(101-1));
		   valor_ataq1 = poder_disparo1 * efec_disparo1;

		   //Defensa del segundo personaje
		   poder_defensa2 = (Per_2->Caracteristicas->Armadura * Per_2->Caracteristicas->velocidad);
		   danio2 = (((double)valor_ataq1 - (double)poder_defensa2)/(double)Max_danio)*100;

		   if(danio2>0.0){
		   		salud2 = salud2 - danio2 ;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Nom_Per1);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s\n",Nom_Per2);
		   printf("Poder de defensa: %d\n",poder_defensa2);
		   printf("Salud: %.2lf\n",salud2);
		   printf("Danio recibido: %.2lf\n",danio2);
		    printf("\n\n");
		    if(salud2 <=0){i=6;}		
	    }
	    if (x==2){
		   //Ataque del segundo personaje
		   poder_disparo2 = (Per_2->Caracteristicas->destreza * Per_2->Caracteristicas->fuerza * Per_2->Caracteristicas->Nivel);
		   efec_disparo2 = (double)(1+rand()%(101-1));
		   valor_ataq2 = (double)poder_disparo2 * efec_disparo2;

		   //Defensa del primer personaje
		   poder_defensa1 = (Per_1->Caracteristicas->Armadura * Per_1->Caracteristicas->velocidad);
		   danio1 = (((double)valor_ataq2 - (double)poder_defensa1)/(double)Max_danio)*100;
		   if(danio1>0.0){
		   		salud1 = salud1 - danio1;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Nom_Per2);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",Nom_Per1);
		   printf("Poder de defensa: %d\n",poder_defensa1);
		   printf("Salud: %.2lf\n",salud1);
		   printf("Danio recibido: %.2lf\n",danio1);
		   printf("\n\n");
		   if(salud1 <=0){i=6;}  
	    }
	    Juego_Terminado(i);
		
	}
	if(salud2 > salud1){
		printf("|| :D Ganador: %s\n",Nom_Per2);
		printf("Salud: %.2lf\n",salud2);
	}
	else{
		if(salud1 >salud2){
		 printf("|| :D Ganador: %s\n",Nom_Per1);
		 printf("Salud: %.2lf\n",salud1);
	    }
	}
}

//------------------------------------------------BATALLA
void campeonato(Lista *L){
	int per_1, per_2, resultado;
	Nodo *N1, *N2;

	//ronda =1;
	while(tamanioLista(L) > 1){
		printf("------------------------Personajes Disponibles\n\n");
	    Mostrar_Lista (L);
		printf("--Primer contrincante\n");
	    per_1 = num_personaje();
	    printf("--Segundo contrincante\n");
	    per_2 = num_personaje();

	    while(per_1 == per_2){
	        printf("**No se puede elegir el mismo personaje**\nPor favor elija otro\n");
		    printf("--Primer contrincante\n");
	        per_1 = num_personaje();
	        printf("--Segundo contrincante\n");
	        per_2 = num_personaje();
		}
		N1 = Personaje_Elejido(L, per_1);
	    N2 = Personaje_Elejido(L, per_2);
	    //Veo si existe algun problema con los personajes
	    if (N1 == NULL && N2 == NULL){
		    printf("Hay problemas con los personajes\n");
		    exit(0);
	    }
	    else{
		    if (N2 == NULL){
			    printf("Hay problemas con el 2do personaje\n");
		        exit(0);
		    }
		    else{
			        if (N1 == NULL){
				        printf("Hay problemas con el 1er personaje\n");
		                exit(0);
			        }
			        else resultado=Resultado_Peleas(N1->Datos_Personajes, N2->Datos_Personajes);
			}
		}
		if(resultado==2){
		        printf("|| :D Ganador: %s\n",N2->Datos_Personajes->DatosPersonales->ApellidoNombre);
		        printf("Salud: %.2lf\n",N2->Datos_Personajes->DatosPersonales->Salud);
		        Suma_Poderes(N2->Datos_Personajes);
		        printf("\n|| :,( Eliminado: %s\n",N1->Datos_Personajes->DatosPersonales->ApellidoNombre);
		        eliminarX(L, per_1);
		        Pausar();
	    }
	    else{
	        printf("|| :D Ganador: %s\n",N1->Datos_Personajes->DatosPersonales->ApellidoNombre);
		    printf("Salud: %.2lf\n",N1->Datos_Personajes->DatosPersonales->Salud);
		    Suma_Poderes(N1->Datos_Personajes);
		    printf("\n|| :,( Eliminado: %s\n",N2->Datos_Personajes->DatosPersonales->ApellidoNombre);
		    eliminarX(L, per_2);
		    Pausar();
	    }
	}
	if(resultado==2){
		printf("\n|| ¡¡:D CAMPEON: %s!!\n\n",N2->Datos_Personajes->DatosPersonales->ApellidoNombre);		
	}
	else{
	    printf("\n\n|| ¡¡:D CAMPEON: %s!!\n\n",N1->Datos_Personajes->DatosPersonales->ApellidoNombre);
	}
}

int Resultado_Peleas(TPersonaje *Per_1, TPersonaje *Per_2){
	int x, Max_danio = 10000;
	double efec_disparo1, efec_disparo2, danio1, salud1, danio2, salud2;
	int poder_disparo2,  valor_ataq2, poder_defensa2;
	int poder_disparo1, poder_defensa1,valor_ataq1;
	char Nom_Per1[30], Nom_Per2[30];
	int Ganador;

	salud1 = Per_1->DatosPersonales->Salud;
	salud2 = Per_2->DatosPersonales->Salud;

	Verif_Per(Per_1, Per_2, Nom_Per1, Nom_Per2);

	for (int i = 0; i < 6; ++i){
		printf("---Maximo danio: %d\n\n", Max_danio);
		printf("TURNO: %d\n", i+1);
		//Veo quien inicia atacando
		//1 Primer personaje - 2 Segundo personaje
		if((i%2)==0){x=2;}
		else x=1;

		if (x==1){
		   //Ataque del primer personaje
		   poder_disparo1 = (Per_1->Caracteristicas->destreza * Per_1->Caracteristicas->fuerza * Per_1->Caracteristicas->Nivel);
		   efec_disparo1 = (double)(1+rand()%(101-1));
		   valor_ataq1 = poder_disparo1 * efec_disparo1;

		   //Defensa del segundo personaje
		   poder_defensa2 = (Per_2->Caracteristicas->Armadura * Per_2->Caracteristicas->velocidad);
		   danio2 = (((double)valor_ataq1 - (double)poder_defensa2)/(double)Max_danio)*100;

		   if(danio2>0.0){
		   		salud2 = salud2 - danio2 ;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Nom_Per1);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s\n",Nom_Per2);
		   printf("Poder de defensa: %d\n",poder_defensa2);
		   printf("Salud: %.2lf\n",salud2);
		   printf("Danio recibido: %.2lf\n",danio2);
		    printf("\n\n");
		    if(salud2 <=0){i=6;}		
	    }
	    if (x==2){
		   //Ataque del segundo personaje
		   poder_disparo2 = (Per_2->Caracteristicas->destreza * Per_2->Caracteristicas->fuerza * Per_2->Caracteristicas->Nivel);
		   efec_disparo2 = (double)(1+rand()%(101-1));
		   valor_ataq2 = (double)poder_disparo2 * efec_disparo2;

		   //Defensa del primer personaje
		   poder_defensa1 = (Per_1->Caracteristicas->Armadura * Per_1->Caracteristicas->velocidad);
		   danio1 = (((double)valor_ataq2 - (double)poder_defensa1)/(double)Max_danio)*100;
		   if(danio1>0.0){
		   		salud1 = salud1 - danio1;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Nom_Per2);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",Nom_Per1);
		   printf("Poder de defensa: %d\n",poder_defensa1);
		   printf("Salud: %.2lf\n",salud1);
		   printf("Danio recibido: %.2lf\n",danio1);
		   printf("\n\n");
		   if(salud1 <=0){i=6;}  
	    }
	    Juego_Terminado(i);
		
	}
	if(salud2 > salud1){
		Ganador = 2;
	}
	else{
		if(salud1 >salud2){
		 Ganador = 1;
	    }
	    else{
	    	printf("--Empate\n--Ganador decidido por Sorteo: \n");
	    	Ganador = 1+ rand()%(2);
	    } 
	}
	return Ganador;
}


