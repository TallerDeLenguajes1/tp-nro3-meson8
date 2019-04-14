#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"Jorgito", "Luquitas", "Chavo", "Pibe", "Maxi", "Olaf"};
char Apellidos[6][10]={"Alfaro", "Llave", "Hormiga", "Burro", "Caballo", "PP"};

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
	TPersonaje Datos_Personajes;
	Nodo *Siguiente;
}Nodo;

typedef Nodo *Lista;

//Declaracion de Funciones
TDatos *Cargar_Datos(void);
TCaracteristicas *Cargar_Carac(void);
TPersonaje Carga_Per();
void Mostrar_Datos (TDatos *datos);
void Mostrar_Carac(TCaracteristicas *carac);
void Muestra_Per (TPersonaje Per);
void Mostrar_Lista (Lista L);
int esListaVacia (Lista L);
void Crear_Per(Lista *L, TPersonaje Personaje);
void batalla(Lista L);
int num_personaje();
TPersonaje *Personaje_Elejido(Lista L, int num);
void Resul_enfrent(TPersonaje *Per_1, TPersonaje *Per_2);


int main (void) {
	Lista Lista_Per;
	int Cant_Per = 6;
	srand(time(NULL));

	Lista_Per = NULL;
	for (int i = 0; i < Cant_Per; ++i){
		Crear_Per(&Lista_Per, Carga_Per() );
	}
	printf("------------------------Personajes------------------------\n\n");
	Mostrar_Lista (Lista_Per);
	printf("\n\n------------------------Batalla-----------------------\n\n");
	batalla(Lista_Per);
	
	return 0;
}

TPersonaje Carga_Per(){
	TPersonaje Per;

	Per.DatosPersonales = Cargar_Datos();
	Per.Caracteristicas = Cargar_Carac();

	return Per;
}

void Crear_Per(Lista *L, TPersonaje Personaje){
	Nodo *nuevo;

	nuevo = (Nodo*)malloc(sizeof(Nodo));

	nuevo->Datos_Personajes = Personaje;
	nuevo->Siguiente = *L;

	*L = nuevo;
}


TDatos *Cargar_Datos(void){
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
	    Datos->ApellidoNombre = (char *) malloc (10);
 		strcpy((Datos->ApellidoNombre), Nombres[rand()%6]);
	    Datos->edad = rand()%300;
	    Datos->Salud = (double)100;

	    return Datos;
}
TCaracteristicas *Cargar_Carac(void){
	TCaracteristicas * Car = (TCaracteristicas *) malloc(sizeof(TCaracteristicas));

	Car->velocidad =1+ rand()%(10);// 1 a 10
	Car->destreza = 1+ rand()%(5); //1 a 5
	Car->fuerza =   1+ rand()%(10);//1 a 10
	Car->Nivel =    1+rand()%(10); //1 a 10
	Car->Armadura = 1+rand()%(10); //1 a 10

	return Car;
}

void Mostrar_Datos (TDatos *datos) {

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
}
void Mostrar_Carac(TCaracteristicas *carac){
	printf("Velocidad: %d\n", carac->velocidad );
	printf("Destreza: %d\n", carac->destreza);
	printf("Fuerza: %d\n", carac->fuerza);
	printf("Nivel: %d\n", carac->Nivel);
	printf("Armadura: %d\n", carac->Armadura);
}

void Muestra_Per (TPersonaje Per) {
	Mostrar_Datos(Per.DatosPersonales);
	Mostrar_Carac(Per.Caracteristicas);
}



void Mostrar_Lista (Lista L){
	int i = 0;

	if (esListaVacia(L)) {
		printf("No hay Personajes");
	}
	else{
		while (esListaVacia(L) != 1) {
			printf("------Personaje [%d]\n", i+1);
			Muestra_Per(L->Datos_Personajes);
			printf("\n");
			L = L->Siguiente;
			i++;
		}
	}
}
int esListaVacia (Lista L){
	return (L == NULL);
}

void batalla(Lista L){
	int per_1, per_2;

	printf("--Primer contrincante\n");
	per_1 = num_personaje();
	printf("--Segundo contrincante\n");
	per_2 = num_personaje();

	Resul_enfrent(Personaje_Elejido(L, per_1), Personaje_Elejido(L,per_2));
}

TPersonaje *Personaje_Elejido(Lista L, int num){
	int i=0;
	Lista aux = L;
	num = num-1;
	while (i<num && aux != NULL) {
		//printf("siguiente\n");
		aux = aux->Siguiente;
		i++;
	}
	return &(aux->Datos_Personajes);
} 
int num_personaje(){
	int numero;
	printf("Elija el numero del personaje (1-6): ");
	scanf("%d", &numero);
	fflush(stdin);
	numero=numero-1;
	while(numero > 5){
		printf("**Opcion Incorrecta**\nPor favor ingrese una Opcion valida\nDesea continuar? (S/N): ");
		scanf("%d", &numero);
	    fflush(stdin);
	    numero=numero-1;
	}
	printf("\n\n");
	return numero;
}
void Resul_enfrent(TPersonaje *Per_1, TPersonaje *Per_2){
	TCaracteristicas Carac_Per_1, Crear_Per_2;
	int x, Max_danio = 10000;
	double efec_disparo1, efec_disparo2, danio1, salud1, danio2, salud2;
	int poder_disparo2,  valor_ataq2, poder_defensa2;
	int poder_disparo1, poder_defensa1,valor_ataq1;

	salud1 = Per_1->DatosPersonales->Salud;
	salud2 = Per_2->DatosPersonales->Salud;

	printf("\n\n %s VS %s\n", Per_1->DatosPersonales->ApellidoNombre, Per_2->DatosPersonales->ApellidoNombre);

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

		   printf("--Atacante: %s\n",Per_1->DatosPersonales->ApellidoNombre);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s\n",Per_2->DatosPersonales->ApellidoNombre);
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

		   printf("--Atacante: %s\n",Per_2->DatosPersonales->ApellidoNombre);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",Per_2->DatosPersonales->ApellidoNombre);
		   printf("Poder de defensa: %d\n",poder_defensa1);
		   printf("Salud: %.2lf\n",salud1);
		   printf("Danio recibido: %.2lf\n",danio1);
		   printf("\n\n");
		   if(salud1 <=0){i=6;}  
	    }
		
	}
	if(salud2 > salud1){
		printf("Ganador: %s\n",Per_2->DatosPersonales->ApellidoNombre);
		printf("Salud: %.2lf\n",salud2);
		exit (0);
	}
	if(salud1 >salud2){
		 printf("Ganador: %s\n",Per_1->DatosPersonales->ApellidoNombre);
		 printf("Salud: %.2lf\n",salud1);
		 exit (0);
	}
	if(salud1==salud2){
		printf("Empate\n");
		exit (0);
	}
}





