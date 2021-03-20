#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// Funciones de desarrollo del juego



int main(){
	printf("                                                            \n");
	printf(ANSI_COLOR_CYAN"              Menu de juego                            \n" ANSI_COLOR_RESET);

	printf("             1 - Colocar ficha                             \n");
	printf("             2 - Rendirse                                 \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf(ANSI_COLOR_BLUE"  Por favor seleccione una opcion: "ANSI_COLOR_RESET);

		int opcion;
	scanf("%d", &opcion);
	
    switch ( opcion ){
        case 1: printf( "\n   Iniciar juego\n"   );
		return 1;
        

        case 2: printf( "\n   Gracias por jugar con LA MASTER-TEC-90000 \n"   );
				return 0;
                
		default:printf(ANSI_COLOR_RED"    \n Opcion no valida,ingrese nuevamente el numero.\n" ANSI_COLOR_RESET);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
			return main();
}

}
