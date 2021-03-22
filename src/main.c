#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK    "\x1b[30m"
#define ANSI_COLOR_BGRED  "\x1b[41m"
#define ANSI_COLOR_BGBLUE  "\x1b[44m"

#include "Logica.c"
#include "minimax.c"


// Funciones de desarrollo del juego
void IniciarTablero(char [N][N]);
int JuegaJugador(char [N][N],int ,char );
int JuegaCPU(char [N][N],int ,char);
void MenuPrincipal();
int menuJuego(char partida[N][N],int numero_jugador,char ficha);
int turnoJugador(char partida[N][N],int numero_jugador,char ficha);
int turnoCPU(char partida[N][N],int numero_jugador,char ficha);
void Juego();

/**
  ** Descripcion: Se llama una vez al iniciar el programa, unicamente solicita el nombre del jugador y luego lo dirige al menu principal
  ** Entradas: Recibe la matriz que representara el estado del juego.
  ** Salida: No retorna nada.
*/

char nombreJugador[30];

int main(){
	printf(ANSI_COLOR_RED"\n\n                            Hola jugador, bienvenido a 4 en linea de MASTER-TEC-90000.\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN"                            Por favor ingrese su nombre: "ANSI_COLOR_RESET);
	scanf( "%s", nombreJugador);
	MenuPrincipal();
}


/**
  ** Descripcion: Se utiliza cada vez que se desea inicar un juego nuevo, esta inicializa el tablero agregando vacios dentro de cada celda.
  ** Entradas: Recibe la matriz que representara el estado del juego.
  ** Salida: No retorna nada.
*/
void IniciarTablero(char partida[N][N]){
	int i; int j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			partida[i][j] = ' ';
		}
	}
}


/**
  ** Descripcion: Funcion que realiza el trabajo de solicitar al jugador un numero que sera la columna donde desea colocar la ficha.
  ** Entradas: Recibe el numero de jugador, el estado actual del tablero y la ficha con la que juega.
  ** Salida: retorna un cero siempre(Este numero no afecta en ningun lugar del codigo)
*/
int JuegaJugador(char partida[N][N],int numero_jugador,char ficha){
	int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

	char respuesta;
	int columna;

	printf(ANSI_COLOR_GREEN"                                                               Turno de" ANSI_COLOR_RESET " %s: ",nombreJugador);
	
	scanf("%c", &respuesta);
	columna = respuesta-'0'-1;

	if(columna <0 || columna>6){
		printf("\a");
		printf(ANSI_COLOR_RED "\n                                               Un número del 1 al 7, no puede ser tan difícil.\n\n" ANSI_COLOR_RESET);
		sleep(1);
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	else if(partida[0][columna] != ' '){
		printf("\a");
		printf(ANSI_COLOR_GREEN "\n                                              La columna %d esta llena! Selecciona otra. \n"ANSI_COLOR_RESET,columna+1);
		sleep(1);
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	AplicarTirada(partida,columna,ficha);
	return 0;
}

/**
  ** Descripcion: Funcion utilizada para que La CPU eliga una jugada y la coloque en el tablero.
  ** Entradas: Recibe el numero de jugador, el estado actual del tablero y la ficha con la que juega.
  ** Salida: retorna un cero siempre(Este numero no afecta en ningun lugar del codigo)
*/
int JuegaCPU(char partida[N][N], int dificultad,char ficha){
	printf(ANSI_COLOR_RED"\n                                              El Master esta pensando...\n\n"ANSI_COLOR_RESET);
	sleep(1);
	int columna = ElegirTirada(partida,dificultad);
	AplicarTirada(partida,columna,ficha);
	system("clear");
	ImprimirTablero(partida);
	return 0;
}

/**
  ** Descripcion: Funcion utilizada en cada turno del jugador, muestra un menu con las siguientes opciones: colocar ficha o rendirse. 
  ** Entradas: Recibe el numero de jugador, el estado actual del tablero y la ficha con la que juega.
  ** Salida: retorna un cero o un 1 dependiendo si el juego deberia continuar o no.
*/
int menuJuego(char partida[N][N],int numero_jugador,char ficha){

	printf("                                                            \n");
	printf(ANSI_COLOR_CYAN"\n                                                                     Menu de juego                            \n" ANSI_COLOR_RESET);
	printf("                                                                  1 - Colocar ficha                             \n");
	printf("                                                                  2 - Rendirse                                 \n");
	printf("\n");
	printf("\n");
	printf(ANSI_COLOR_BLUE"                                                   Por favor seleccione una opcion: "ANSI_COLOR_RESET);


	int opcion;
	scanf("%d", &opcion);
	
    switch ( opcion ){
        case 1: JuegaJugador(partida,0,'O');
		return 1;
        

        case 2: 
				system("clear");
				printf( "\n                                       %s"ANSI_COLOR_RED" decidio retirarse o, ¿habrá sido un error?.                                                        \n"ANSI_COLOR_RESET,nombreJugador);
				sleep(2);
				return 0;
                
        default:printf("\n                       %s,"ANSI_COLOR_RED " ¿otra vez intentando provocar errores?.\n" ANSI_COLOR_RESET,nombreJugador);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
			return menuJuego(partida,0,'O');
    }
}

/**
  ** Descripcion: Menu principal de la aplicacion que posee unicamente 2 opciones, salir o comenzar juego.
  ** Entradas: No posee entradas.
  ** Salida: No posee salidas.
*/
void MenuPrincipal(){
	int opcion;
	
	printf("\n\n\n\n");
	printf(ANSI_COLOR_GREEN"                                                            \n");
	printf("            #             #                                  \n");
	printf("           ##             #                                \n");
	printf("          # #   ##  ####  #      # ####   ##   #### #            \n");
	printf("         #  #  #  # #   # #        #   # #  # #    ##          \n");
	printf("        #   #  #### #   # #      # #   # #### #    ##        \n");
	printf("       ####### #    #   # #      # #   # #    #    ##            \n");
	printf("            #   ### #   # ###### # #   #  ###  #### ##          \n" ANSI_COLOR_RESET);
	printf("                                                            \n");
	printf("              1 - Jugar contra el Master                    \n");
	printf("                    2 - Salir                               \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("                                                            \n");

	printf(  "%s," ANSI_COLOR_BLUE " que deseas hacer?: " ANSI_COLOR_RESET,nombreJugador) ;
    scanf("%d", &opcion);
    switch ( opcion )
    {
        case 1: Juego();
                break;

        case 2: printf( ANSI_COLOR_CYAN"\n                        Gracias por jugar"ANSI_COLOR_RESET" %s,"ANSI_COLOR_CYAN "entretenos en alguna otra ocasión.\n\n"ANSI_COLOR_RESET,nombreJugador);
                break;
        default:printf("\n                       %s"ANSI_COLOR_RED " deja de intentar provocar fallos.\n" ANSI_COLOR_RESET,nombreJugador);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
			sleep(2);
			MenuPrincipal();
    }
}

/**
  ** Descripcion: Funcion utilizada en cada turno del jugador, llama a la funcion MenuJuego que le permite al jugador colocar una ficha o rendirse. 
  ** Entradas: Recibe el numero de jugador, el estado actual del tablero y la ficha con la que juega.
  ** Salida: retorna un cero o un 1 dependiendo si el juego deberia continuar o no.
*/
int turnoJugador(char partida[N][N],int numero_jugador,char ficha){
	int seguir = 1;
	seguir = menuJuego(partida,0,'O');
		
	if(VictoriaJugador(partida)){
		system("clear");
		ImprimirTablero(partida);
		printf("\a");
		printf(ANSI_COLOR_GREEN"                 Es un milagro, lograste ganar "ANSI_COLOR_RESET"%s!",nombreJugador);
		sleep(2);
		return 0;
	}
	system("clear");
	ImprimirTablero(partida);
	return seguir;
}

/**
  ** Descripcion: Funcion utilizada en cada turno de la CPU, llama a la funcion JuegaCPU que se encarga de seleccionar el movimiento que hara la cpu y luego revisa si esta gano.
  ** Entradas: Recibe el numero de jugador, el estado actual del tablero y la ficha con la que juega.
  ** Salida: retorna un cero o un 1 dependiendo si el juego deberia continuar o no.
*/

int turnoCPU(char partida[N][N],int numero_jugador,char ficha){
	JuegaCPU(partida,1,'X');
	
	if(VictoriaCPU(partida)){
		system("clear");
		ImprimirTablero(partida);
		printf("\n");
		printf(ANSI_COLOR_RED"                                                              Una victoria mas para el Master." ANSI_COLOR_RESET);
		sleep(2);
		return 0;
	}
	return 1;
}

/**
  ** Descripcion: Se utiliza cada vez que se desea inicar un juego nuevo, despues de definir el orden de juego la funcion llama a inicializar el tablero.
   * y comienza en un ciclo que solo se terminara cuando el juego haya terminado o el jugador se rinda.
   * El ciclo comienza mostrando el tablero y viendo si aun es posible seguir jugando, si es posible jugar entonces dependiendo del orden pide al jugador o al CPU jugar.
  ** Entradas: No posee entradas
  ** Salida: No retorna nada.
*/
void Juego(){
	srand(time(NULL));
	int orden;
	orden = rand () % (2-1+1) + 1;  


	char partida[N][N];
	IniciarTablero(partida);

	int contador_jugadas = 1;
	int seguir = 1;

	printf(ANSI_COLOR_CYAN "        Seleccionando turno..." ANSI_COLOR_RESET);
	if(orden ==1){
		printf(ANSI_COLOR_CYAN "       Comenzara jugando" ANSI_COLOR_RESET " %s\n",nombreJugador);
	}else{ printf(ANSI_COLOR_RED "       Comenzara jugando el Master.\n" ANSI_COLOR_RESET);}
	sleep(2);
	
	while (seguir ==1)
	{
		system("clear");
		ImprimirTablero(partida);
		if(Posibilidades(partida)==0){
			printf("\a");
			printf(ANSI_COLOR_CYAN "                                 Hubo un empate!" ANSI_COLOR_RESET);
			sleep(1);
			break;
		}
		if (orden ==1){
			seguir = turnoJugador(partida,0,'O');
			if (seguir==0)break;
			seguir =turnoCPU(partida,1,'X');
		}
		else {
			seguir = turnoCPU(partida,1,'X');
			if (seguir==0)break;
			seguir = turnoJugador(partida,0,'O');
		}
	}
	//system("clear");
	MenuPrincipal();
}
