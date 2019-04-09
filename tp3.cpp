    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][10]={"jorgito", "bartolito", "cavo", "dingo", "elmo", "Olaf"};
char Apellidos[6][10]={"fausto", "gomez", "hormiga", "indio", "jacinto"};

typedef struct TDatos {
	TRaza Raza; //nota 1
	char *Apellido, *Nombre; //nota 2
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
	for (int i = 0; i < 6; ++i){
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
	    Puntero_Personajes[i].DatosPersonales->edad = rand()%300;
	    Puntero_Personajes[i].DatosPersonales->Salud = (double)100;
	    Puntero_Personajes[i].DatosPersonales->Nombre = (char *) malloc (10);
	    strcpy((Puntero_Personajes[i].DatosPersonales->Nombre), Nombres[rand()%6]);
	    Puntero_Personajes[i].DatosPersonales->Apellido = (char *)malloc(10);
	    strcpy((Puntero_Personajes[i].DatosPersonales->Apellido), Apellidos[rand()%6]);

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
	printf("¿Cuantos Personajes desea mostrar?(1-6) \n");

		i=num_personaje()+1;
		
		for (int j = 0; j < i; ++j)
		{
		
	    //Datos Personales
			printf("--------Personaje num: %d--------\n",j+1);
	    switch(Puntero_Personajes[j].DatosPersonales->Raza){
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
	    printf("Nombre: %s\n", Puntero_Personajes[j].DatosPersonales->Nombre);
	    printf("Apellido: %s\n", Puntero_Personajes[j].DatosPersonales->Apellido);
	    printf("Edad: %d\n", Puntero_Personajes[j].DatosPersonales->edad);
	    printf("Salud: %.2lf\n", Puntero_Personajes[j].DatosPersonales->Salud);
	    //Caracteristicas
	    printf("Velocidad: %d\n", Puntero_Personajes[j].Caracteristicas->velocidad );
	    printf("Destreza: %d\n", Puntero_Personajes[j].Caracteristicas->destreza);
	    printf("Fuerza: %d\n", Puntero_Personajes[j].Caracteristicas->fuerza);
	    printf("Nivel: %d\n", Puntero_Personajes[j].Caracteristicas->Nivel);
	    printf("Armadura: %d\n\n", Puntero_Personajes[j].Caracteristicas->Armadura);
	    printf("------------------------------------\n");
		}
	}

//El numero del personaje
int num_personaje(){
	int numero;
	scanf("%d", &numero);
	fflush(stdin);
	while(numero > 6){
		printf("Numero incorrecto \nElija un numero del 1 al 6 \n");
		scanf("%d", &numero);
	    fflush(stdin);
	}
	numero=numero-1;
	printf("\n\n");
	return numero;
}
/*-------------------------------------------------------------*/
/*REGLAS DEL JUEGO*/

/*
Elejir 2 personajes para que compitan entre ellos. Cada uno tendra
3 ataques que iran debilitando al oponente. Al final de dichas 
rondas el que mejor salud tenga sera el ganador (puede haber
empate).
*/
/*
--Valores de Ataque:
. Poder de disparo: destreza * fuerza * nivel;
. Efectividad del disparo: Un numero aleatorio entre 1-100. 
Considerarlo como valor conceptual.
. Valor de Ataque: Poder de disparo * Efectividad del disparo.
--Valores de defensa:
. Poder de defensa: armadura * velocidad;
--Resultado del enfrentamiento
. Maximo daño provocable: 5000
. Daño provocado: ((valor ataque * Efectividad del disparo - poder de defensa)/5000)*100;
. Actualizar salud: Daño provocado--
*/

void batalla(TPersonaje *Puntero_Personajes){
	int per_1, per_2;
	
	printf("--Primer contrincante\n");
	per_1 = num_personaje();
	printf("--Segundo contrincante\n");
	per_2 = num_personaje();

	printf("\n\n %s %s Vs %s %s\n", Puntero_Personajes[per_1].DatosPersonales->Nombre, Puntero_Personajes[per_1].DatosPersonales->Apellido, Puntero_Personajes[per_2].DatosPersonales->Nombre, Puntero_Personajes[per_2].DatosPersonales->Apellido);
	Resul_enfrent(Puntero_Personajes, per_1, per_2);
}

void Resul_enfrent(TPersonaje *Puntero_Personajes, int per_1, int per_2){
	int x, Max_danio = 50000;
	int poder_disparo1, valor_ataq1; //Ataque del Primer personaje
	double efec_disparo1, efec_disparo2; 
	int poder_defensa1; //Defensa del Primer personaje
	int poder_disparo2, valor_ataq2; //Ataque del Segundo personaje
	int poder_defensa2; //Defensa
	int danio1, salud1; //Resultado del enfrentamiento del Primer personaje
	int danio2, salud2; //Resultado del enfrentamiento del Segundo personaje

	salud1 = Puntero_Personajes[per_1].DatosPersonales->Salud;
	salud2 = Puntero_Personajes[per_2].DatosPersonales->Salud;

		   //Defensa del primer personaje
		   poder_defensa1 = (Puntero_Personajes[per_1].Caracteristicas->Armadura * Puntero_Personajes[per_1].Caracteristicas->velocidad);
		   //Defensa del segundo personaje
		   poder_defensa2 = (Puntero_Personajes[per_2].Caracteristicas->Armadura * Puntero_Personajes[per_2].Caracteristicas->velocidad);
	for (int i = 0; i < 6; ++i){
		printf("--------Round %d --------\n",i+1);
		//Veo quien inicia atacando
		//1 Primer personaje - 2 Segundo personaje
		if((i%2)==0){x=2;}
		else x=1;

		if (x==1){
		   //Ataque del primer personaje
		   poder_disparo1 = (Puntero_Personajes[per_1].Caracteristicas->destreza * Puntero_Personajes[per_1].Caracteristicas->fuerza * Puntero_Personajes[per_1].Caracteristicas->Nivel);
		   efec_disparo1 =(double) (rand()%100)/100;
		   valor_ataq1 = poder_disparo1 * efec_disparo1;
		   printf("--Ataque: %s %s\n",Puntero_Personajes[per_1].DatosPersonales->Nombre, Puntero_Personajes[per_1].DatosPersonales->Apellido);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s %s\n",Puntero_Personajes[per_2].DatosPersonales->Nombre, Puntero_Personajes[per_2].DatosPersonales->Apellido);
		   printf("Poder de defensa: %d\n",poder_defensa2);


		   if (poder_defensa2 > valor_ataq1)
		   {
		   	danio2 = 0;
		   	poder_defensa2=poder_defensa2 - valor_ataq1;
		   printf("Daño: %d\n",danio2);
			   }
		   else {
		   	danio2 = (valor_ataq1  - poder_defensa2);
		   	poder_defensa2 = poder_defensa2 - valor_ataq1;
		   printf("Daño: %d\n",danio2);
		   }
		   salud2 = salud2 - danio2;

		   printf("Salud: %d\n",salud2);
		    printf("\n\n");

		    if (salud2<=0)
		    {
		    	i=6;
		    }
		   
	    }
	    if (x==2){
		   //Ataque del segundo personaje
		   poder_disparo2 = (Puntero_Personajes[per_2].Caracteristicas->destreza * Puntero_Personajes[per_2].Caracteristicas->fuerza * Puntero_Personajes[per_2].Caracteristicas->Nivel);
		   efec_disparo2 =(double) (rand()%100)/100;;
		   valor_ataq2 = poder_disparo2 * efec_disparo2;
		   printf("--Ataque: %s %s\n",Puntero_Personajes[per_2].DatosPersonales->Nombre, Puntero_Personajes[per_2].DatosPersonales->Apellido);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",Puntero_Personajes[per_1].DatosPersonales->Nombre);
		   printf("Poder de defensa: %d\n",poder_defensa1);

		   if (poder_defensa1 > valor_ataq2)
		   {
		   	danio1 = 0;
		   	poder_defensa1=poder_defensa1 - valor_ataq2;
		   printf("Daño: %d\n",danio1);

		   }
		   else {
		   	danio1 = (valor_ataq2 - poder_defensa1);
		   	poder_defensa1 = poder_defensa1 - valor_ataq2;
		   printf("Daño: %d\n",danio1);
		   }

		   salud1 = salud1 - danio1;

		   printf("Salud: %d\n",salud1);
		   printf("\n\n");

		  
		    if (salud1<=0)
		    {
		    	i=6;
		    }

	    }
		
	}
	if(salud2 < salud1){
		   	printf("Ganador: %s %s\n",Puntero_Personajes[per_1].DatosPersonales->Nombre, Puntero_Personajes[per_1].DatosPersonales->Apellido);
	switch(Puntero_Personajes[per_1].DatosPersonales->Raza){
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
		  
		   	printf("Edad: %d\n",Puntero_Personajes[per_1].DatosPersonales->edad);
		   }
	 else if(salud1 < salud2){
		   	printf("Ganador: %s %s\n",Puntero_Personajes[per_2].DatosPersonales->Nombre ,Puntero_Personajes[per_2].DatosPersonales->Apellido);
		 switch(Puntero_Personajes[per_1].DatosPersonales->Raza){
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
		   	printf("Edad: %d\n",Puntero_Personajes[per_2].DatosPersonales->edad);
		   }
	else if(salud1 == salud2){
		printf("Empate\n");
	}
}
