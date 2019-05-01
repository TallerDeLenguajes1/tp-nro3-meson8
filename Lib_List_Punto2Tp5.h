#ifndef LISTA_H_
#define LISTA_H_
#include <stdio.h>
#include <stdlib.h>

char Continuar();
int num_personaje(); //Funcion para elejir los personajes
int Opciones_Menu();
void Juego_Terminado(int num);
void Salir();


void Juego_Terminado(int num){
	int Turno=6;
	if (num == Turno){
		printf("\n------------------GAME OVER------------------\n");
	}
}

int Opciones_Menu(){
	int Opcion;
	printf("Elija una de estas opciones\n");

	printf("0) 1 vs 1\n");
	printf("1) Empezar Batalla\n");
	printf("2) Salir\n");
	//printf("3) Jugar\n");
	printf("Ingrese aqui: ");
	scanf("%d", &Opcion);
	fflush(stdin);
	while(Opcion > 2){
		printf("0) 1 vs 1\n");
	    printf("1) Batalla\n");
	    printf("2) Salir\n");
	    //printf("3) Jugar\n");
	    printf("Ingrese aqui: ");
		scanf("%d", &Opcion);
	    fflush(stdin);
	}
	printf("\n\n");
	return Opcion;
}

void Salir(){
	exit(0);
}

char Continuar(){
	char letra;
	printf("Desea continuar? (S/N): ");
	scanf("%c", &letra);
	fflush(stdin);
	while(letra !='S' && letra !='s' && letra !='N' && letra !='n'){
		printf("**Opcion Incorrecta**\nPor favor ingrese una Opcion valida\nDesea continuar? (S/N): ");
		scanf("%c", &letra);
	    fflush(stdin);
	}
	printf("\n\n");
	return letra;
}

int num_personaje(){
	int numero;
	printf("Elija el numero del personaje (1-8): ");
	scanf("%d", &numero);
	fflush(stdin);
	//numero=numero-1;
	while(numero > 8){
		printf("**Opcion Incorrecta**\nPor favor ingrese una Opcion valida\nElija el numero del personaje (1-6): ");
		scanf("%d", &numero);
	    fflush(stdin);
	    //numero=numero-1;
	}
	printf("\n\n");
	return numero;
}

void Pausar(){
	printf("\n---Presione enter para continuar\n\n");
	getch();
}


#endif