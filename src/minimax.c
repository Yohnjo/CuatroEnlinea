#include <stdio.h>
#include <stdlib.h>
#include "Logica.h"
#include "minimax.h"

void CopiaTablero(char tablero1[N][N], char tablero2[N][N]){
	int i; int j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			tablero2[i][j] = tablero1[i][j];
		}
	}
}

Nodo CreaNodo(char tablero[N][N],int nivel,int dificultad){ //construyo el nodo 
	int i; 
	int j=0;
	Nodo p; //creo el nodo donde guardo las variables 

	p.nivel = nivel; //asigno el novel
	CopiaTablero(tablero,p.tablero); //guardo el tablero dentro del nodo

	p.valor = 0;
	if (VictoriaCPU(p.tablero) || VictoriaJugador(p.tablero) || p.nivel == 2*dificultad+2){ //si el nodo a crear excede la cantidad de nodos o el tablero hay un ganador
        p.num_hijos = 0; //se reduce la cantidad de hijos a 0
	}else{
			p.num_hijos = Posibilidades(tablero); // sino le asigno la cantidad de posibles movimentos (hijos)
	}

	if (p.num_hijos != 0){ //si el nodo tiene hijos
        p.hijos = (Nodo **) malloc(p.num_hijos*sizeof(Nodo *)); //reservo la memoria
        p.movimientos = (int *) malloc(p.num_hijos*sizeof(int)); 
        for(i=0;i<N;i++){
            if(tablero[0][i] == ' '){ //si la casilla final no esta ocupada por una ficha
                p.movimientos[j] = i;//agrege los posibles movimentos
                j += 1;
            }
        }
	}


	return p;
}

void CreaNivel(Nodo *Padre,char ficha,int dificultad){//crea nodos con todas las posibilidades actuales del tablero
	int i;
	Nodo *Hijo;

	for(i=0;i<Padre->num_hijos;i++){ //creo la cantidad de hijos con respecto a las posibilidades de jugar
		Hijo = (Nodo *) malloc(sizeof(Nodo));
		CopiaTablero(Padre->tablero,Hijo->tablero); //creo una copia del tablero padre al tablero hijo
		AplicarTirada(Hijo->tablero,Padre->movimientos[i],ficha);//coloco la tirada I dentro del tablero de este hijo
		*Hijo = CreaNodo(Hijo->tablero,Padre->nivel+1,dificultad); //le asigno los elementos al hijo con un nivel inferior
		Padre->hijos[i] = Hijo;//guardo los hijos
	}
}

void CreaDobleNivel(Nodo *raiz,int dificultad){
	int i;
	CreaNivel(raiz,'X',dificultad);//crea un nivel con todas las posibilidades como hijos de la raiz
	for(i=0;i<raiz->num_hijos;i++){
		CreaNivel(raiz->hijos[i],'O',dificultad); //crea un nivel para cada hijo con las posibilidades de cada hijo los cuales tendrian otros hijos
	}
}

void CreaArbol(Nodo *raiz, int profundidad, int dificultad){ //funcion que crea el arbol y sus niveles
	CreaDobleNivel(raiz,dificultad);//creo el primer subarbol
	if(profundidad == 0) return;
	else{
		int i; 
		int j;
		for(i=0;i<raiz->num_hijos;i++){
			for(j=0;j<raiz->hijos[i]->num_hijos;j++){
				CreaArbol(raiz->hijos[i]->hijos[j],profundidad-1,dificultad);//creo un arbol recursivo para cada arbol 
			}
		}
	}
	return;
}

void BorraArbol(Nodo *raiz){
	if(raiz->num_hijos == 0){
        free(raiz);
	}
	else{
        int i;
        for (i=0;i<raiz->num_hijos;i++){
            BorraArbol(raiz->hijos[i]);
        }
        free(raiz->hijos);
        free(raiz->movimientos);
	}

	return;
}

/* void ImprimirArbol(Nodo * raiz){
    char * tab = "";
    if (raiz->nivel != 0){
        tab = (char *) malloc((2*raiz->nivel+1)*sizeof(char));
        int j; for (j=0;j<2*raiz->nivel;j++) tab[j] = ' ';
        tab[2*raiz->nivel] = '\0';
    }
    if (raiz->num_hijos == 0) printf("%sNodo (valor %lf)\n",tab,raiz->valor);
    else{
        int i;
        printf("%sNodo (valor %lf)\n",tab,raiz->valor);
        for (i=0;i<raiz->num_hijos;i++) ImprimirArbol(raiz->hijos[i]);
    }
    free(tab);
} */


//raiz tablero es partida
void ValorarHojas(Nodo *raiz){
    if (raiz->num_hijos == 0){ //si es un nodo final 
        
		if (VictoriaCPU(raiz->tablero)){
			raiz->valor = 1000; //asigna el  valor de 1000 heuristico si la victoria es del CPU
		} //return VALOR_VICTORIA;
		if (VictoriaJugador(raiz->tablero)) {
			raiz->valor = -1000; //asigna el valor de -1000 heuristico si la victoria es del jugador
			
		}
	}
    else{
        int i;
        for (i=0;i<raiz->num_hijos;i++){
            ValorarHojas(raiz->hijos[i]);//recursividad
        }
    }
}

void MiniMax(Nodo *Raiz){
    int i;
	if (Raiz->num_hijos != 0){ //si la raiz tiene hijos
        for (i=0;i<Raiz->num_hijos;i++){  //para cada hijo
            if (Raiz->hijos[i]->num_hijos != 0){ //revise si los hijos tiene hijos
                MiniMax(Raiz->hijos[i]); //recursividad por cada hijo
            }
        }

        if (Raiz->nivel %2 == 0){ // MAX si el nivel es par
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->num_hijos;i++){
                if (Raiz->hijos[i]->valor > Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor; //asigno el valor del mayor de los hijos al padre
                }
            }
        }

		if (Raiz->nivel % 2 == 1){ // Min si el nivel es impar
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->num_hijos;i++){
                if (Raiz->hijos[i]->valor < Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor; //asigno el valor del menor de los hijos al padre
                }
            }
        }

		Raiz->valor /= 2; //divido el valor euristico
	}
}

int ElegirTirada(char partida[N][N], int dificultad){
	Nodo Raiz = CreaNodo(partida,0,dificultad);
	int movimiento;
	CreaArbol(&Raiz,dificultad,dificultad);
	ValorarHojas(&Raiz);
	MiniMax(&Raiz);
	

	// Elijo random entre todas las posibilidades que son igual de buenas
	int num_tiradas_buenas = 0;
	int tiradas_buenas[7];
	int i; 
	int j=0;
	for (i=0;i<Raiz.num_hijos;i++){//reviso todos los hijos de la raiz
		if (Raiz.hijos[i]->valor == 2.0*Raiz.valor){//si el valor del hijo es el doble del padre
			num_tiradas_buenas++;//sumo una tirada buena 
			tiradas_buenas[j] = Raiz.movimientos[i];//le agrego el movimiento que corresponde a la tirada buena a la lista
			j++;
		}
	}
	int index = rand()%num_tiradas_buenas; //escojo una al azar de las jugadas que seleccione del arbol
	movimiento = tiradas_buenas[index];//asigno el movimiento que escogi
	BorraArbol(&Raiz);//borro el arbol

	return movimiento; //regreso el movimiento que voy a ingresar en el tablero
}