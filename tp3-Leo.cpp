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
	int Nivel; //1 a 10
	int Armadura; //1 a 10
} TCaracteristicas;

typedef struct TPersonaje {
	TDatos * DatosPersonales;
	TCaracteristicas * Caracteristicas;
} TPersonaje;


//Parte de Leo
void Cargar_N_per(TPersonaje *Puntero_Personajes);
void Mostrar_N_per(TPersonaje *Puntero_Personajes);
int num_personaje();
void continuar(char seguir);
//

int main (void) {
	TPersonaje *Puntero_Personajes = (TPersonaje *)malloc(sizeof(TPersonaje) * 6);
	srand(time(NULL));


	//Parte de Leo
	Cargar_N_per(Puntero_Personajes);
	printf("---Mostrar N Personajes\n\n");
    Mostrar_N_per(Puntero_Personajes);
    //
	return 0;
}
/*------------------------Parte de Leo------------------------*/
//Cargar Personajes
void Cargar_N_per(TPersonaje *Puntero_Personajes){
	enum TRaza raza;
	for (int i = 0; i < sizeof(TPersonaje); ++i){
		Puntero_Personajes[i].DatosPersonales = (TDatos *)malloc(sizeof(TDatos));
	    Puntero_Personajes[i].Caracteristicas = (TCaracteristicas *)malloc(sizeof(TCaracteristicas));
	    //Datos Personales
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

	    Puntero_Personajes[i].DatosPersonales->Raza = raza;
	    Puntero_Personajes[i].DatosPersonales->ApellidoNombre = (char *) malloc (10);
	    strcpy((Puntero_Personajes[i].DatosPersonales->ApellidoNombre), Nombres[rand()%6]);
	    Puntero_Personajes[i].DatosPersonales->edad = rand()%300;
	    Puntero_Personajes[i].DatosPersonales->Salud = (double)100;

		//Caracteristicas
		Puntero_Personajes[i].Caracteristicas->velocidad = 1+rand()%(11-1);
		Puntero_Personajes[i].Caracteristicas->destreza = 1+rand()%(6-1);
		Puntero_Personajes[i].Caracteristicas->fuerza = 1+rand()%(11-1);
		Puntero_Personajes[i].Caracteristicas->Nivel = 1+rand()%(11-1);
		Puntero_Personajes[i].Caracteristicas->Armadura = 1+rand()%(11-1);
	}
}
//Mostrar Personajes
void Mostrar_N_per(TPersonaje *Puntero_Personajes){
	int i;
	char seguir ='S';

	do{
		i=num_personaje();
		printf("---Personaje N° : [%d]\n", i+1);
	    //Datos Personales
	    switch(Puntero_Personajes[i].DatosPersonales->Raza){
		    case 0: 
			    printf("Raza: %s\n", "Orco");
			    break;
		    case 1: 
			    printf("Raza: %s\n", "Humano");
			    break;
		    case 2: 
			    printf("Raza: %s\n", "Enano");
			    break;
		    case 3: 
			    printf("Raza: %s\n", "Mago");
			    break;
		    case 4: 
			    printf("Raza: %s\n", "Elfo");
			    break;

		    default: printf("Raza: %s\n", "Humano");
	    }
	    printf("Nombre: %s\n", Puntero_Personajes[i].DatosPersonales->ApellidoNombre);
	    printf("Edad: %d\n", Puntero_Personajes[i].DatosPersonales->edad);
	    printf("Salud: %.2lf\n", Puntero_Personajes[i].DatosPersonales->Salud);
	    //Caracteristicas
	    printf("Velocidad: %d\n", Puntero_Personajes[i].Caracteristicas->velocidad );
	    printf("Destreza: %d\n", Puntero_Personajes[i].Caracteristicas->destreza);
	    printf("Fuerza: %d\n", Puntero_Personajes[i].Caracteristicas->fuerza);
	    printf("Nivel: %d\n", Puntero_Personajes[i].Caracteristicas->Nivel);
	    printf("Armadura: %d\n", Puntero_Personajes[i].Caracteristicas->Armadura);

	    continuar(seguir);
	}while(seguir =='S');
}

//El numero del personaje
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
//Si el usuario desea continuar con el programa
void continuar(char seguir){
	printf("\n\nDesea continuar? (S/N): ");
	scanf("%c", &seguir);
	fflush(stdin);

	while(seguir != 'S' && seguir !='N'){
		printf("**Opcion Incorrecta**\nPor favor ingrese una Opcion valida\nDesea continuar? (S/N): ");
	    scanf("%c", &seguir);
	    fflush(stdin);
	}
	if(seguir == 'N'){
		exit(0);
	}
}
/*-------------------------------------------------------------*/

