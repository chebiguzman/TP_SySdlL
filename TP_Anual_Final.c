#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chequear_cadena(char cadena[]);
void borrar_palabra(char palabra[], int largo_palabra);

char cadena[256];
char palabra[256];
/*
	La Columna 0 indica la lectura de los caracteres 1 y 0.
	La Columna 1 indica la lectura de los caracteres 2-9.
	La Columna 2 indica la lectura del caracter .
	La Columna 3 indica la lectura del caracter B
	La Columna 4 indica la lectura del centinela #
	
	Las Filas 0-4 indican los estados 0-4
	La Fila 5 indica el estado de rechazo , que es el 5
	
	| 0,1 | 2-9 |  .  |  B  |  #  |
	|  1  |  5  |  3  |  5  |  0  |
	|  2  |  5  |  3  |  4  |  0  |
	|  2  |  5  |  3  |  5  |  0  |
	|  5  |  5  |  5  |  5  |  0  |
	|  3  |  3  |  5  |  5  |  0  |
	|  5  |  5  |  5  |  5  |  0  |
	
*/
int tt_afd_minimo [6][5] = {
	{1,5,3,5,0},
	{2,5,3,4,0},
	{2,5,3,5,0},
	{5,5,5,5,0},//estado 3 de aceptacion
	{3,3,5,5,0},//estado 4 de aceptacion
	{5,5,5,5,0}
};

int main(void) {
	
	printf("Programa que reconoce las palabras del \nlenguaje generado por la expresion regular: %c", 10);
	printf("[01]\\.[0-9]?|[01]*B %c %c", 10, 10);
	
	printf("Ingrese la cadena a evaluar\n"); //Las palabras de la cadena deben estar separadas por un centinela '#'
	fgets(cadena, sizeof(cadena), stdin); //   Ej: hola#0.1#10B#1001#B#0.
    
	int largo_cadena = strlen(cadena) - 1;
	printf("Largo cadena = %d \n %c", largo_cadena, 10);
	//printf("Cadena = %s\n", cadena);
	
	if(largo_cadena != 0){
		chequear_cadena(cadena);
	} else {
		printf("Error - cadena vacia\n");
	}
	
	printf("%cPresione ENTER para salir \n", 10);  
	getchar(); 
}

void borrar_palabra(char palabra[], int largo_palabra) {
	
	for(int i=0; i<largo_palabra; i++){
		palabra[i] = '\0';
	}
	
}

void chequear_cadena(char cadena[]){
	
	int estado_actual = 0;
	int estado_final;
	int i = 0;
	int j = 0;
	
	borrar_palabra(palabra,256);
	
	while(cadena[i] != 10) { //10 es el valor ascii de VT(vertical tab), que será el último caracter de la cadena ingresada
		
		switch (cadena[i]) {
			case '0': case '1':
				palabra[j] = cadena[i];
				j += 1;
				estado_actual = tt_afd_minimo[estado_actual][0];
				break;
			case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				palabra[j] = cadena[i];
				j += 1;
				estado_actual = tt_afd_minimo[estado_actual][1];
				break;
			case 'B':
				palabra[j] = cadena[i];
				j += 1;
				estado_actual = tt_afd_minimo[estado_actual][2];
				break;
			case '.':
				palabra[j] = cadena[i];
				j += 1;
				estado_actual = tt_afd_minimo[estado_actual][3];
				break;
			case '#': //caso centinela, imprimo la palabra y la evaluacion
				estado_final = estado_actual;
				estado_actual = tt_afd_minimo[estado_actual][4];
				switch (estado_final){
					case 3: case 4:
						printf("%s \t\t Pertenece al lenguaje.\n", palabra);
						break;
					case 1: case 2:
						printf("%s \t\t NO Pertenece al lenguaje, palabra incompleta.\n", palabra);
						break;
					case 5:
						printf("%s \t\t NO Pertenece al lenguaje, contiene caracteres que no estan en el alfabeto.\n", palabra);
						break;
					default:
						printf("ERROR \t\t El centinela no separa ninguna palabra.\n");
				}
				borrar_palabra(palabra,256);
				j = 0;
				break;
			default:
				palabra[j] = cadena[i];
				j += 1;
				estado_actual = 5;
		}//FIN switch
		i += 1;
		
	}//FIN while(cadena[i] != '\0')

	//Imprimo la última palabra
	if(cadena[(i-1)] != '#') {
		
		estado_final = estado_actual;

		switch (estado_final){
			case 3: case 4:
				printf("%s \t\t Pertenece al lenguaje\n", palabra);
				break;
			case 1: case 2:
				printf("%s \t\t NO Pertenece al lenguaje, palabra incompleta\n", palabra);
				break;
			case 5:
				printf("%s \t\t NO Pertenece al lenguaje, contiene caracteres que no estan en el alfabeto\n", palabra);
				break;
			default:
				printf("ERROR \t\t El centinela no separa ninguna palabra.\n");
		}
	}
	
}



