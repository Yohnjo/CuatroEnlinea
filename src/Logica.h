/* Variables que es necesario definir en el juego */
#define N 7


void ImprimirTablero(char [N][N]);
void ImprimirBloque(char [N][N],int ,int );
int verificarHorizontal(char [N][N],char );
int verificarVertical(char [N][N],char );
int verificarDiagonales(char [N][N],char );
int Posibilidades(char [N][N]);
int VictoriaCPU(char partida[N][N]);
int VictoriaJugador(char partida[N][N]);
void AplicarTirada(char [N][N],int ,char );

