#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chequear_cadena(char cadena[], int largo_cadena);
void borrar_palabra(char palabra[], int largo_palabra);
void chequear_palabra(char palabra[]);

char cadena[256];
char palabra[256];

int tt_afd_minimo [6][5] = {
	{5,1,5,3,5},
	{5,2,5,3,4},
	{5,2,5,3,5},
	{0,5,5,5,5},
	{0,3,3,5,5},
	{5,5,5,5,5}
};

int main(void) {
	
	printf("Ingrese la cadena a evaluar\n");
	fgets(cadena, sizeof(cadena), stdin);
    
	int largo_cadena = strlen(cadena) - 1;
	printf("Largo cadena = %d\n", largo_cadena);
	printf("Cadena = %s\n", cadena);
		
	if(largo_cadena != 0){
		chequear_cadena(cadena, largo_cadena);
	} else {
		printf("Error - cadena vacia\n");
	}
	
	printf("Press ENTER key to exit\n");  
	getchar(); 
}

void chequear_cadena(char cadena[], int largo_cadena) {
	
	borrar_palabra(palabra,256);
	int largo_palabra, i, j;
	i = 0;
	j = 0;
	
	while(cadena[i] != '\0') {
	
		while(cadena[i] != '#' && cadena[i] != '\0') {
			palabra[j] = cadena[i];
			i += 1;
			j += 1;
		}
		
		chequear_palabra(palabra);
		//printf("%s \n", palabra);

		borrar_palabra(palabra,256);
	
		i += 1;
		j = 0;
		
	}
	return;
	
}

void borrar_palabra(char palabra[], int largo_palabra) {
	
	for(int i=0; i<largo_palabra; i++){
		palabra[i] = '\0';
	}
	
}

void chequear_palabra(char palabra[]){
	
	int estado_actual = 0;
	int estado_final;
	int i = 0;
	
	while(palabra[i] != '\0') {
		
		switch (palabra[i]) {
			case '0':
			case '1':
				estado_actual = tt_afd_minimo[estado_actual][1];
				break;
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				estado_actual = tt_afd_minimo[estado_actual][2];
				break;
			case 'B':
				estado_actual = tt_afd_minimo[estado_actual][3];
				break;
			case '.':
				estado_actual = tt_afd_minimo[estado_actual][4];
				break;
			default:
				estado_actual = 5;
		}
		i += 1;
		//printf("--> %d ", estado_actual);
	}
	
	estado_final = tt_afd_minimo[estado_actual][0];
	
	switch (estado_final){
		case 0:
			printf("%s Pertenece al lenguaje\n", palabra);
			break;
		case 5:
			printf("%s NO Pertenece al lenguaje\n", palabra);
			break;
		default:
			printf("ERROR \n");
	}
	
}
//hola#0.1#1001001B#skere#B
/*int tt_afd_minimo [6][5] = {
	{6,1,5,3,5},
	{6,2,5,3,4},
	{6,2,5,3,5},
	{0,5,5,5,5},
	{0,3,3,5,5},
	{6,5,5,5,5}
};*/



