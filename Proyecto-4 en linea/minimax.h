typedef struct nodo{
	struct nodo **hijos; //donde guardo los hijos de posibilidades
	int *movimientos; //lista de movimentos
	int num_hijos; //cantidad de hijos con respecto a las posibilidades
	char tablero[N][N]; //copia del tablero actual
	double valor;  //donde guardo quien gana
	int nivel;   //nivel dentro del arbol
} Nodo;
void CopiaTablero(char [N][N],char [N][N]);
Nodo CreaNodo(char [N][N],int ,int );
void CreaNivel(Nodo *,char ,int );
void CreaDobleNivel(Nodo *,int );
void CreaArbol(Nodo *,int ,int );
void BorraArbol(Nodo *);
void ImprimirArbol(Nodo *);
void ValorarHojas(Nodo *);
void MiniMax(Nodo *);
int ElegirTirada(char [N][N],int );