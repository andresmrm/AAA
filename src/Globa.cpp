#include "AAA.h"

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
int SCREEN_BPP = 32;
int FRAMES_PER_SECOND = 30;
int telaCheia = 1;

int TAM_TELA_X = 700;
int TAM_TELA_Y = 700;
int POS_TELA_X = 10;
int POS_TELA_Y = 10;
int velocidadeTela = 10; // Scrollspeed

SDL_Event evento;
Uint32 tempo = 0;
Uint32 tempo2 = 0;

TTF_Font *fonte12 = NULL;
TTF_Font *fonte16 = NULL;
TTF_Font *fonte20 = NULL;
TTF_Font *fonte26 = NULL;

SDL_Color textColor = { 255, 255, 255 };
SDL_Color corVermelha = { 255, 0, 0 };

char aux[100];
char aux2[100];

SDL_Surface *tela = NULL;
SDL_Surface *botoesImagem = NULL;
SDL_Surface *terrenosImagem = NULL;
SDL_Surface *unidadesImagem = NULL;
SDL_Surface *bordasImagem = NULL;
SDL_Surface *terrInfosImagem = NULL;
SDL_Surface *cidadesImagem = NULL;
SDL_Rect botoesI[40];
SDL_Rect terrenosI[20];
SDL_Rect unidadesI[20];
SDL_Rect cidadesI[20];
SDL_Rect bordasI[40];
int TAM_MAPA_X = 20;
int TAM_MAPA_Y = 20;

territorio mapa[TAM_MAPA_X_MAX][TAM_MAPA_Y_MAX];

tipo tipos[numTipos];
int numTiposUsados = 5000;
pelotao unidades[numPelotoes];
int numPelotoesUsados = 5000;
cidade cidades[numCidades];
jogador jogadores[numJogadores];
int numJogadoresUsados = 2;
raca racas[numRacas];
int numRacasUsadas = 6;
magia magias[numMagias];

int jogadorAtual = 0;
int turno = 0;

int jogAlvoMagia = -1;

int telaX = 350;
int telaY = 350;
int selecaoX = -1;
int selecaoY = -1;
int selecaoP = -1;
//const int numPs = 50;
int selecaoPs[numPs];
int selecaoC = -1;
int listaTreino[7];
int listaMagias[3][5];

int var = 0;
int editando = -1;

int movDiagonal = 1;

int giroB = 0;
int giroC = 0;
int posLista = 0;

int infoCores = 1;
int infoUnits = 1;

int vegetacao[3];
int deserto[3];
int relevo[3];
int neve[3];

char mTexto[mTextoComp][mTextoTama];

SDL_Thread *redeThreadSaida = NULL;
SDL_Thread *redeThreadEntrada = NULL;

char mRede[50][50];
int online = 0;
int novaSaida = 0;
int esperaOnline = 0;

SDLNet_SocketSet sockets;
TCPsocket sockOuvinte, sockConectado; /* Socket descriptor, Client socket descriptor */
IPaddress servIpLocal, *servIpCliente;
Uint16 PortaRede = 2000;
char servIpNome[20];

//TCPsocket sockCliente;	/* Socket descriptor */
IPaddress clieIpServidor;	/* Server address */
//Uint16 portaProcurada = 2000;
char ipProcuradoNome[20];

Mix_Music *click = NULL;
