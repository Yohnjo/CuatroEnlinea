#include <stdio.h>
#include "Logica.h"



/**
  * Funcion que se usa para mostrar el estado actual del tablero, funciona en 3 fases siendo cada una una linea de prints de cada fila de del tablero.
  * Recibe la matriz que representa el estado actual de juego junto a la fila que se estara dibujando. 
  * No devuelve ningún valor solo muestra el estado actual de juego.
*/
void ImprimirBloque(char partida[N][N],int fila,int repeticion){
	if (repeticion==1){
		printf("\n");
		printf("                                             -- ");
		for(int j=0;j<N;j++){
			if (partida[fila][j] != ' ') {

				if (partida[fila][j] != 'O'){
					printf(ANSI_COLOR_BGRED ANSI_COLOR_RED"-- "ANSI_COLOR_RESET);
					printf(" ");
				}
				else {
					printf(ANSI_COLOR_BGBLUE ANSI_COLOR_BLUE"-- "ANSI_COLOR_RESET);
					printf(" ");
				}
			}else printf("    ");
			printf("--- ");

		}
		ImprimirBloque(partida,fila,repeticion+1);

	}else if(repeticion==2){
		printf("\n");
		printf("                                             - ");
		for(int j=0;j<N;j++){
			

			if (partida[fila][j] != ' ') {
				if (partida[fila][j] != 'O'){
					printf(ANSI_COLOR_BGRED ANSI_COLOR_RED"---- "ANSI_COLOR_RESET);
					printf(" ");
				}
				else {
					printf(ANSI_COLOR_BGBLUE ANSI_COLOR_BLUE"---- "ANSI_COLOR_RESET);
					printf(" ");
				}
			}else printf("      ");
			if (j==6){
				printf("--");
			}else{
				printf("- ");
			}
		}
		ImprimirBloque(partida,fila,repeticion+1);
	}else if(repeticion==3){
		printf("\n");
		printf("                                             -- ");
		for(int j=0;j<N;j++){
		
			if (partida[fila][j] != ' ') {

				if (partida[fila][j] != 'O'){
					printf(ANSI_COLOR_BGRED ANSI_COLOR_RED"-- "ANSI_COLOR_RESET);
					printf(" ");
				}
				else{
					printf(ANSI_COLOR_BGBLUE ANSI_COLOR_BLUE"-- "ANSI_COLOR_RESET);
					printf(" ");
				} 
			}else printf("    ");
			printf("--- ");
		}
		
	}
}


/**
  * Primera parte de las funciones para imprimir el tablero, imprime el encabezado y luego llama una vez por fila la funcion imprimir bloque
  * Recibe la matriz que representa el estado actual de juego. 
  * No devuelve ningún valor solo muestra el estado actual de juego.
*/
void ImprimirTablero(char partida[N][N]){
	printf("\n");
	printf("\n");
	printf("                                                1       2        3       4       5       6      7\n");
	printf("                                                |       |        |       |       |       |      |\n");
	printf("                                                V       V        V       V       V       V      V\n");
	printf("                                             ----------------------------------------------------------");
	

	for(int i=0;i<N;i++) {
		ImprimirBloque(partida,i,1);
		printf("\n                                             ----------------------------------------------------------");
		
	}

}



/**
  * Funcion devuelve la cantidad total de columnas que aun no estan llenas.
  * Recibe la matriz que representa el estado actual de juego.
  * Devuelve un número que indica la cantidad de columnas no vacias.
*/
int Posibilidades(char partida[N][N]){
	int j;
	int cont = 0;

	for(j=0;j<N;j++){
		if(partida[0][j] == ' '){
			cont += 1;
		}
	}
	return cont;
}

/**
  ** Descripcion:Funcion se utiliza para verificar si se gano y forma parte de otras 2 necesarias, esta revisa cada ficha que posea al menos 4 fichas de distancia
   * entre ella y el borde del tablero horizontalmente hablando y revisando siempre su derecha unicamente.
  ** Entradas: Recibe la matriz que representa el estado actual de juego y la ficha con la cual se va a validar sea jugador o CPU.
  ** Salida: Devuelve un 1 si se encuentra que el jugador o el CPU ya gano.
*/
int verificarHorizontal(char partida[N][N],char ficha){
	int i; int j;
	for(i=0;i<N;i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i][j+1] == ficha){
					if(partida[i][j+2] == ficha){
						if(partida[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
  ** Descripcion:Funcion se utiliza para verificar si se gano y forma parte de otras 2 necesarias, esta revisa cada ficha que posea al menos 4 fichas de distancia
   * entre ella y el final del tablero y revisando siempre hacia abajo unicamente.
  ** Entradas: Recibe la matriz que representa el estado actual de juego y la ficha con la cual se va a validar sea jugador o CPU.
  ** Salida: Devuelve un 1 si se encuentra que el jugador o el CPU ya gano.
*/
int verificarVertical(char partida[N][N],char ficha){
	int i; int j;
	for(j=0;j<N;j++){
		for(i=0;i<(N-3);i++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j] == ficha){
					if(partida[i+2][j] == ficha){
						if(partida[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
  ** Descripcion:Funcion se utiliza para verificar si se gano y forma parte de otras 2 necesarias, esta revisa cada ficha que posea al menos 4 fichas de distancia
   * entre ella y el final del tablero y revisando primero si diagonal superior derecha y luego su diagonal inferior izquierda.
  ** Entradas: Recibe la matriz que representa el estado actual de juego y la ficha con la cual se va a validar sea jugador o CPU.
  ** Salida: Devuelve un 1 si se encuentra que el jugador o el CPU ya gano.
*/
int verificarDiagonales(char partida[N][N],char ficha){
	int i; int j;
	for(i=0;i<(N-3);i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j+1] == ficha){
					if(partida[i+2][j+2] == ficha){
						if(partida[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	for(i=0;i<5;i++){
		for(j=N-1;j>2;j--){
			if(partida[i][j] == ficha){
				if(partida[i+1][j-1] == ficha){
					if(partida[i+2][j-2] == ficha){
						if(partida[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

/**
  ** Descripcion:Funcion que llamada a las 3 validaciones necesarias dando la ficha que controla la cpu a estas.
  ** Entradas: Recibe la matriz que representa el estado actual de juego.
  ** Salida: Si alguna de las validaciones devuelve un valor 1 entonces la cpu ya gano por lo tanto esta funcion devolvera un 1 tambien, si no fue el caso
   * devolera un cero.	
*/
int VictoriaCPU(char partida[N][N]){
	int gano =0;
    char ficha = 'X';

	gano = verificarHorizontal(partida,ficha);
	if (gano == 1) return 1;
	gano = verificarVertical(partida,ficha);
	if (gano == 1) return 1;
	gano= verificarDiagonales(partida,ficha);
	if (gano == 1) return 1;

	return 0;
}

/**
  ** Descripcion:Funcion que llamada a las 3 validaciones necesarias dando la ficha que controla el jugador a estas.
  ** Entradas: Recibe la matriz que representa el estado actual de juego.
  ** Salida: Si alguna de las validaciones devuelve un valor 1 entonces el jugador ya gano por lo tanto esta funcion devolvera un 1 tambien, si no fue el caso
   * devolera un cero.	
*/
int VictoriaJugador(char partida[N][N]){
	int gano =0;
    char ficha = 'O';

	gano = verificarHorizontal(partida,ficha);
	if (gano == 1) return 1;
	gano = verificarVertical(partida,ficha);
	if (gano == 1) return 1;
	gano= verificarDiagonales(partida,ficha);
	if (gano == 1) return 1;

	return 0;
}

/**
  * Funcion que se usa para colocar una ficha en la posicion data por el jugador si es posible.
  * Recibe la matriz que representa el estado actual de juego junto a la posicion donde se desea 
  * colocar la ficha y la ficha que representa a que jugador pertenece.
  * No devuelve ningún valor solo cambia el estado actual de juego si es posible.
*/
void AplicarTirada(char partida[N][N],int columna, char ficha){
	int i;
	for(i=0;i<N;i++){
		if(partida[N-1-i][columna]==' '){
			partida[N-1-i][columna] = ficha;
			break;
		}
	}
}


