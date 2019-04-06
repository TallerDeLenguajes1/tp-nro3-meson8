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


//Parte de Leo
void Cargar_N_per(TPersonaje *Puntero_Personajes);
void Mostrar_N_per(TPersonaje *Puntero_Personajes);
void batalla(TPersonaje *Puntero_Personajes);
void Resul_enfrent(TPersonaje *Puntero_Personajes, int per_1, int per_2);
int num_personaje();
char continuar();
//

int main (void) {
	TPersonaje *Puntero_Personajes = (TPersonaje *)malloc(sizeof(TPersonaje) * 6);
	srand(time(NULL));
	//Parte de Leo
	Cargar_N_per(Puntero_Personajes);
	printf("---Mostrar N Personajes\n\n");
    Mostrar_N_per(Puntero_Personajes);
    printf("\n\n---Batalla\n\n");
    batalla(Puntero_Personajes);
    //
	return 0;
}
/*------------------------Parte de Leo------------------------*/
//Cargar Personajes
void Cargar_N_per(TPersonaje *Puntero_Personajes){
	enum TRaza raza;
	for (int i = 0; i < 6; i++){
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

	    seguir=continuar();
	}while(seguir =='S'|| seguir =='s');
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
char continuar(){
	char seguir;
	printf("\n\nDesea continuar? (S/N): ");
	scanf("%c", &seguir);
	fflush(stdin);

	while(seguir != 'S' && seguir !='N' && seguir !='n' && seguir !='n'){
		printf("**Opcion Incorrecta**\nPor favor ingrese una Opcion valida\nDesea continuar? (S/N): ");
	    scanf("%c", &seguir);
	    fflush(stdin);
	}
	/*if(seguir == 'N'){
		exit(0);
	}*/
	return seguir;
}

void batalla(TPersonaje *Puntero_Personajes){
	int per_1, per_2;
	
	printf("--Primer contrincante\n");
	per_1 = num_personaje();
	printf("--Segundo contrincante\n");
	per_2 = num_personaje();

	printf("\n\n %s VS %s\n", Puntero_Personajes[per_1].DatosPersonales->ApellidoNombre, Puntero_Personajes[per_2].DatosPersonales->ApellidoNombre);
	Resul_enfrent(Puntero_Personajes, per_1, per_2);
}
/*
---------------------------Variables utilizadas---------------------------
x = Turno de ataque de los personajes
Max_danio = El maximo daño que pueden recibir los personajes

//Primer Personaje
poder_disparo1, efec_disparo1, valor_ataq1 //Ataque del Primer personaje
poder_defensa1 //Defensa del Primer personaje
danio1, salud1 //Resultado del enfrentamiento del Primer personaje

//Segundo Personaje
poder_disparo2, efec_disparo2, valor_ataq2 //Ataque del Segundo personaje
poder_defensa2 //Defensa del Segundo personaje
danio2, salud2 //Resultado del enfrentamiento del Segundo personaje
*/


void Resul_enfrent(TPersonaje *Puntero_Personajes, int per_1, int per_2){
	int x, Max_danio = 10000;
	double efec_disparo1, efec_disparo2, danio1, salud1, danio2, salud2;
	int poder_disparo2,  valor_ataq2, poder_defensa2;
	int poder_disparo1, poder_defensa1,valor_ataq1;

	salud1 = Puntero_Personajes[per_1].DatosPersonales->Salud;
	salud2 = Puntero_Personajes[per_2].DatosPersonales->Salud;

	for (int i = 0; i < 6; ++i){
		printf("---Maximo danio: %d\n\n", Max_danio);
		printf("TURNO: %d\n", i+1);
		//Veo quien inicia atacando
		//1 Primer personaje - 2 Segundo personaje
		if((i%2)==0){x=2;}
		else x=1;

		if (x==1){
		   //Ataque del primer personaje
		   poder_disparo1 = (Puntero_Personajes[per_1].Caracteristicas->destreza * Puntero_Personajes[per_1].Caracteristicas->fuerza * Puntero_Personajes[per_1].Caracteristicas->Nivel);
		   efec_disparo1 = (double)(1+rand()%(101-1));
		   valor_ataq1 = poder_disparo1 * efec_disparo1;

		   //Defensa del segundo personaje
		   poder_defensa2 = (Puntero_Personajes[per_2].Caracteristicas->Armadura * Puntero_Personajes[per_2].Caracteristicas->velocidad);
		   danio2 = (((double)valor_ataq1 - (double)poder_defensa2)/(double)Max_danio)*100;

		   if(danio2>0.0){
		   		salud2 = salud2 - danio2 ;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Puntero_Personajes[per_1].DatosPersonales->ApellidoNombre);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s\n",Puntero_Personajes[per_2].DatosPersonales->ApellidoNombre);
		   printf("Poder de defensa: %d\n",poder_defensa2);
		   printf("Salud: %.2lf\n",salud2);
		   printf("Danio recibido: %.2lf\n",danio2);
		    printf("\n\n");
		    if(salud2 <=0){i=6;}

		
	    }
	    if (x==2){
		   //Ataque del segundo personaje
		   poder_disparo2 = (Puntero_Personajes[per_2].Caracteristicas->destreza * Puntero_Personajes[per_2].Caracteristicas->fuerza * Puntero_Personajes[per_2].Caracteristicas->Nivel);
		   efec_disparo2 = (double)(1+rand()%(101-1));
		   valor_ataq2 = (double)poder_disparo2 * efec_disparo2;

		   //Defensa del primer personaje
		   poder_defensa1 = (Puntero_Personajes[per_1].Caracteristicas->Armadura * Puntero_Personajes[per_1].Caracteristicas->velocidad);
		   danio1 = (((double)valor_ataq2 - (double)poder_defensa1)/(double)Max_danio)*100;
		   if(danio1>0.0){
		   		salud1 = salud1 - danio1;
		   }
		   else {
		   	printf("Ataque fallido\n");
		   }

		   printf("--Atacante: %s\n",Puntero_Personajes[per_2].DatosPersonales->ApellidoNombre);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",Puntero_Personajes[per_1].DatosPersonales->ApellidoNombre);
		   printf("Poder de defensa: %d\n",poder_defensa1);
		   printf("Salud: %.2lf\n",salud1);
		   printf("Danio recibido: %.2lf\n",danio1);
		   printf("\n\n");
		   if(salud1 <=0){i=6;}  
	    }
		
	}
	if(salud2 > salud1){
		printf("Ganador: %s\n",Puntero_Personajes[per_2].DatosPersonales->ApellidoNombre);
		printf("Salud: %.2lf\n",salud2);
		exit (0);
	}
	if(salud1 >salud2){
		 printf("Ganador: %s\n",Puntero_Personajes[per_1].DatosPersonales->ApellidoNombre);
		 printf("Salud: %.2lf\n",salud1);
		 exit (0);
	}
	if(salud1==salud2){
		printf("Empate\n");
		exit (0);
	}
}

