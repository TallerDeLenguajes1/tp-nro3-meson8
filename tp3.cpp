    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[6][11]={"Harry", "Lord", "Rubeus", "Albus", "Hermione", "Severus"};
char Apellidos[6][11]={"Potter", "Voldemort", "Hagrid", "Dumbledore", "Granger", "Snape"};

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

typedef struct Nodo{
	TPersonaje personajes;
	Nodo * Siguiente;
}Nodo;

int mostrarpjs();
int recorrernodo();
void crearnodo();
TDatos * cargaDatos (void);
TCaracteristicas *  Cargar_Carac(void);
Nodo * elegirpj(int pjnum);
Nodo * choicevs(int numdepjs);
void batalla(Nodo * pja, Nodo * pjb);
void Resul_enfrent(TPersonaje pj1, TPersonaje pj2);
void liberar();
//
	Nodo * start=NULL;

int main (void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int numdepjs;
	srand(time(NULL));
	numdepjs=mostrarpjs();
	choicevs(numdepjs);
	liberar();

	return 0;
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

void batalla(Nodo * pj1, Nodo * pj2){

	printf("\n\n %s %s Vs %s %s\n", pj1->personajes.DatosPersonales->Nombre,pj1->personajes.DatosPersonales->Apellido,pj2->personajes.DatosPersonales->Nombre,pj2->personajes.DatosPersonales->Apellido);
	Resul_enfrent(pj1->personajes,pj2->personajes);
}

void Resul_enfrent(TPersonaje pj1, TPersonaje pj2){
	int x;
	int poder_disparo1, valor_ataq1; //Ataque del Primer personaje
	double efec_disparo1, efec_disparo2; 
	int poder_defensa1; //Defensa del Primer personaje
	int poder_disparo2, valor_ataq2; //Ataque del Segundo personaje
	int poder_defensa2; //Defensa
	int danio1, salud1; //Resultado del enfrentamiento del Primer personaje
	int danio2, salud2; //Resultado del enfrentamiento del Segundo personaje

	salud1 = pj1.DatosPersonales->Salud;
	salud2 = pj2.DatosPersonales->Salud;

	//Defensa del primer personaje
	poder_defensa1 = (pj1.Caracteristicas->Armadura * pj1.Caracteristicas->velocidad);
	//Defensa del segundo personaje
	poder_defensa2 = (pj2.Caracteristicas->Armadura * pj2.Caracteristicas->velocidad);
	for (int i = 0; i < 6; ++i){
		printf("--------Round %d --------\n",i+1);
		//Veo quien inicia atacando
		//1 Primer personaje - 2 Segundo personaje
		if((i%2)==0){x=2;}
		else x=1;

		if (x==1){
		   //Ataque del primer personaje
		   poder_disparo1 = (pj1.Caracteristicas->destreza * pj1.Caracteristicas->fuerza * pj1.Caracteristicas->Nivel);
		   efec_disparo1 =(double) (rand()%100)/100;
		   valor_ataq1 = poder_disparo1 * efec_disparo1;
		   printf("--Ataque: %s %s\n",pj1.DatosPersonales->Nombre, pj1.DatosPersonales->Apellido);
		   printf("Poder de disparo: %d\n",poder_disparo1);
		   printf("Efectividad: %.2lf\n",efec_disparo1);
		   printf("Valor: %d\n",valor_ataq1);
		   //
		   printf("--Defensa: %s %s\n",pj2.DatosPersonales->Nombre, pj2.DatosPersonales->Apellido);
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
		   poder_disparo2 = (pj2.Caracteristicas->destreza * pj2.Caracteristicas->fuerza * pj2.Caracteristicas->Nivel);
		   efec_disparo2 =(double) (rand()%100)/100;;
		   valor_ataq2 = poder_disparo2 * efec_disparo2;
		   printf("--Ataque: %s %s\n",pj2.DatosPersonales->Nombre, pj2.DatosPersonales->Apellido);
		   printf("Poder de disparo: %d\n",poder_disparo2);
		   printf("Efectividad: %.2lf\n",efec_disparo2);
		   printf("Valor: %d\n",valor_ataq2);
		   //
		   printf("--Defensa: %s\n",pj1.DatosPersonales->Nombre);
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
		   	printf("Ganador: %s %s\n",pj1.DatosPersonales->Nombre, pj1.DatosPersonales->Apellido);
	switch(pj1.DatosPersonales->Raza){
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
		  
		   	printf("Edad: %d\n",pj1.DatosPersonales->edad);
		   }
	 else if(salud1 < salud2){
		   	printf("Ganador: %s %s\n",pj2.DatosPersonales->Nombre ,pj2.DatosPersonales->Apellido);
		 switch(pj2.DatosPersonales->Raza){
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
		   	printf("Edad: %d\n",pj2.DatosPersonales->edad);
		   }
	else if(salud1 == salud2){
		printf("Empate\n");
	}
}


TDatos* cargaDatos (void) {
	TDatos *datos;
	enum TRaza raza;
	int random=rand()%6;

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


	datos->Nombre = (char *) malloc (11);
	strcpy((datos->Nombre), Nombres[random]);
	datos->Apellido = (char *) malloc (11);
	strcpy((datos->Apellido), Apellidos[random]);


	datos->edad = rand()%300;

	datos->Salud = (double)100;
	return datos;
}


TCaracteristicas* Cargar_Carac(void){
	TCaracteristicas *carac; 

	carac = (TCaracteristicas*)malloc(sizeof(TCaracteristicas));

	carac->velocidad = 1+rand()%(11-1);
	carac->destreza = 1+rand()%(6-1);
	carac->fuerza = 1+rand()%(11-1);
	carac->Nivel = 1+rand()%(11-1);
	carac->Armadura = 1+rand()%(11-1);

	return carac;
}

void crearnodo(){
	Nodo * nuevo = (Nodo *)malloc(sizeof(Nodo));
	nuevo->personajes.Caracteristicas=Cargar_Carac();
	nuevo->personajes.DatosPersonales=cargaDatos();
	if (start == NULL)
	{
		start=nuevo;
		nuevo->Siguiente=NULL;
	}
	else {
		nuevo->Siguiente=start;
		start=nuevo;
	}
}

int recorrernodo(){
	Nodo * recorrer = start;
	int cont=1;
	while(recorrer != NULL){
		printf("----Personaje num %d----\n",cont);

			printf("Raza: ");
switch(recorrer->personajes.DatosPersonales->Raza) {
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

		printf("Nombre: %s\n", recorrer->personajes.DatosPersonales->Nombre);
		printf("Apellido: %s\n", recorrer->personajes.DatosPersonales->Apellido);
		printf("Edad: %d\n", recorrer->personajes.DatosPersonales->edad);
		printf("Salud: %.2lf\n", recorrer->personajes.DatosPersonales->Salud);
		printf("Velocidad: %d\n", recorrer->personajes.Caracteristicas->velocidad );
		printf("Destreza: %d\n", recorrer->personajes.Caracteristicas->destreza);
		printf("Fuerza: %d\n", recorrer->personajes.Caracteristicas->fuerza);
		printf("Nivel: %d\n", recorrer->personajes.Caracteristicas->Nivel);
		printf("Armadura: %d\n\n",recorrer->personajes.Caracteristicas->Armadura);
		
		recorrer=recorrer->Siguiente;
		cont++;
	}
	return(cont-1);
}
	int mostrarpjs(){
		int numdepjs,num;
	printf("Cuantos personajes desea mostrar?\n");
	scanf("%d",&num);
	while(num>6 || 0>=num){
		printf("Numero incorrecto, elija un numero entre 1 y 6\n");
		scanf("%d",&num);
	}
	for (int i = 0; i < num; ++i){
		crearnodo();
	}
	numdepjs=recorrernodo();
	return(numdepjs);
	}
Nodo * elegirpj(int pjnum){
	int i=1;
	Nodo * extraer=start;
	while(pjnum>i){
		extraer=extraer->Siguiente;
		i++;
	}
	printf("Usted eligio al personaje: %s\n",extraer->personajes.DatosPersonales->Nombre );
	return (extraer);
};
void liberar()
{
    struct Nodo *reco = start;
    struct Nodo *bor;
    while (reco != NULL)
    {
        bor = reco;
        reco = reco->Siguiente;
        free(bor);
    }
}
	Nodo * choicevs(int numdepjs){
	int pjnum;
	printf("Elija el Primer contrincante\n");
	scanf("%d",&pjnum);
	while (pjnum>numdepjs || 0>=pjnum){
		printf("\nNumero incorrecto ingrese un numero entre 1 y %d\n",numdepjs);
		scanf("%d",&pjnum);
	}
	Nodo * pj1=elegirpj(pjnum);
	printf("\nElija el Segundo contrincante\n");
	scanf("%d",&pjnum);
	while (pjnum>numdepjs || 0>=pjnum){
		printf("\nNumero incorrecto ingrese un numero entre 1 y %d\n",numdepjs);
		scanf("%d",&pjnum);
	}	
	Nodo * pj2=elegirpj(pjnum);
	batalla(pj1, pj2);	
	return 0;
	}