#ifndef AAA_H
#define AAA_H

#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_audio.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_opengl.h"

#ifndef WIN32 
#define itoa(A, B, C) sprintf(B, "%d", A)
#endif

//----------------------------------GLOBAIS-------------------------------------
#define TAM_MAPA_X_MAX 100
#define TAM_MAPA_Y_MAX 100
#define numTipos 5000
#define numPelotoes 5000
#define numCidades 500
#define numJogadores 4
#define numRacas 10
#define numMagias 500
#define numPs 50
#define mTextoComp 100
#define mTextoTama 100

typedef struct{
	int vegetacao;
	int relevo;
	int temperatura;
	int agua;
	int x;
	int y;
	}territorio;

typedef struct{
	int tipo;
	int dono;
	int quantidade;
	int movimentos;
	int nivelMagico;
	int x;
	int y;
	char nome[21];
	}pelotao;

typedef struct{
	int dono;
	int emConstr;
	int materiais;
	int magia;
	int treinamento;
	int foco;
	int treinando;
	int treinandoQuant;
	int completado;
	int raca;
	int infTreino;
	int x;
	int y;
	float crescimento;
	float populacao;
	float maxPopulacao;
	char nome[26];
	}cidade;

typedef struct{
	int dono;
	int corpo;
	int raca;
	int movimento;
	int ataque;
	int defesa;
	int vida;
	int tipoDano;
	int dano;
	int treino;
	int treino2;
	int materiais;
	int materiais2;
	int magia;
	int magia2;
	int mana;
	int nivelMagico;
	int arco;
	int montaria;
	int lanca;
	char nome[21];
	}tipo;

typedef struct{
	int tempoCid;
	int arco;
	int lanca;
	int montaria;
	int movimento;
	int ataque;
	int defesa;
	int vida;
	int dano;
	//int terrAtaque;
	//int terrDefesa;
	int penaVegetacao;
	int penaRelevo;
	int penaNeve;
	int penaDeserto;
	int elemento;
	int crescTempIdeal;
	float cidDefesa;
	float maxPop;
	float crescimento;
	float materiais;
	float treinamento;
	float magia;
	char nome[21];
	}raca;

typedef struct{
	int cor;
	int raca;
	int populacao;
	int telaX;
	int telaY;
	int x;
	int y;
	Uint32 materiais;
	Uint32 mana;
	Uint32 materiaisIni;
	Uint32 manaIni;
	char nome[21];
	}jogador;

typedef struct{
	char nome[41];
	int elemento;
	int mana;
	int alcance;
	int nivel;
	int id;
	}magia;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;
extern int FRAMES_PER_SECOND;
extern int telaCheia;

extern int TAM_TELA_X;
extern int TAM_TELA_Y;
extern int POS_TELA_X;
extern int POS_TELA_Y;
extern int velocidadeTela; // Scrollspeed

extern SDL_Event evento;
extern Uint32 tempo;
extern Uint32 tempo2;

extern TTF_Font *fonte12;
extern TTF_Font *fonte16;
extern TTF_Font *fonte20;
extern TTF_Font *fonte26;

extern SDL_Color textColor;
extern SDL_Color corVermelha;

extern char aux[100];
extern char aux2[100];

extern SDL_Surface *tela;
extern SDL_Surface *botoesImagem;
extern SDL_Surface *terrenosImagem;
extern SDL_Surface *unidadesImagem;
extern SDL_Surface *bordasImagem;
extern SDL_Surface *terrInfosImagem;
extern SDL_Surface *cidadesImagem;
extern SDL_Rect botoesI[40];
extern SDL_Rect terrenosI[20];
extern SDL_Rect unidadesI[20];
extern SDL_Rect cidadesI[20];
extern SDL_Rect bordasI[40];
extern int TAM_MAPA_X;
extern int TAM_MAPA_Y;

extern territorio mapa[][TAM_MAPA_Y_MAX];

extern tipo tipos[];
extern int numTiposUsados;
extern pelotao unidades[];
extern int numPelotoesUsados;
extern cidade cidades[];
extern jogador jogadores[];
extern int numJogadoresUsados;
extern raca racas[];
extern int numRacasUsadas;
extern magia magias[];

extern int jogadorAtual;
extern int turno;

extern int jogAlvoMagia;

extern int telaX;
extern int telaY;
extern int selecaoX;
extern int selecaoY;
extern int selecaoP;
//const extern int numPs = 50;
extern int selecaoPs[];
extern int selecaoC;
extern int listaTreino[7];
extern int listaMagias[3][5];

extern int var;
extern int editando;

extern int movDiagonal;

extern int giroB;
extern int giroC;
extern int posLista;

extern int infoCores;
extern int infoUnits;

extern int vegetacao[3];
extern int deserto[3];
extern int relevo[3];
extern int neve[3];

extern char mTexto[][mTextoTama];

extern SDL_Thread *redeThreadSaida;
extern SDL_Thread *redeThreadEntrada;

extern char mRede[50][50];
extern int online;
extern int novaSaida;
extern int esperaOnline;

extern SDLNet_SocketSet sockets;
extern TCPsocket sockOuvinte, sockConectado; /* Socket descriptor, Client socket descriptor */
extern IPaddress servIpLocal, *servIpCliente;
extern Uint16 PortaRede;
extern char servIpNome[20];

//TCPsocket sockCliente;		/* Socket descriptor */
extern IPaddress clieIpServidor;	/* Server address */
//Uint16 portaProcurada = 2000;
extern char ipProcuradoNome[20];

extern Mix_Music *click;
//------------------------------------------------------------------------------


//Base
int modulo( int n );
int maior( int n1, int n2 );
int distancia( int x, int y, int x0, int y0 );
int init_GL();
int iniciar_SDL();
int iniciar_tela();
SDL_Surface *carregar_imagem( char* arquivo );
void aplicar_superficie( int x, int y, SDL_Surface* superficie, SDL_Surface* destino, SDL_Rect* parte = NULL );
void escrever( int x, int y, char frase[30], TTF_Font* fonte = fonte12, SDL_Color cor = textColor);
void escrever_centro( int y, char frase[30], TTF_Font* fonte = fonte12, SDL_Color cor = textColor);
void controlar_frame();
void receber_texto( int tamanho, char texto[] );
int receber_numero( int tamanho, char texto[] );

//Terr
void preparar_matriz_terrenosI();
void testar_terrenos();
void alisar_mapa();
void manchar_mapa( int quantidade, int tamanho, int variacao, int intensidade, int tipo );
void preparar_mapa();
void desenhar_territorio( int x, int y, territorio terr );
void desenhar_mapa();
int espaco_terr( int x, int y );
void desenhar_infos_terr( int x, int y, int terrX, int terrY );
void selecionar_terr();
void cortar_arvores( int x, int y, int lenhador );
void queimar_vegetacao( int x, int y, int queimador );

//Botoe
void preparar_matriz_botoesI();
int botao( int x, int y, int imagem, int id );

//Menus
void preparar_matriz_bordasI();
void desenhar_bordas();
void preencher_fundo();
int atalhos( int modo );
int menu_no_jogo();
int menu_preparar_jogo();
int menu_carregar_jogo();
int menu_preferencias();
int menu_rede();
int menu_espera_jogada();
void creditos();
int menu_principal();

//Unida
void preparar_matriz_unidadesI();
void preparar_pelotoes();
void desenhar_pelotao( int x, int y, int nTipo, int nUnit = -1 );
void desenhar_pelotoes();
void desenhar_selecao();
void procurar_pelotoes_xy( int x, int y );
int procurar_pelotoes_para_juntar( int x, int y, int nTipo, int dono, int nUnit );
int procurar_inimigos_xy( int x, int y );
int procurar_unidade_vazia();
void ordenar_pelotoes();
void criar_pelotao( int x, int y, int nTipo, int dono, int quant, int movi );
void eliminar_pelotao( int N, int ordem = 1 );
void separar_pelotao( int nUnit, int quant );
void juntar_pelotao( int sec, int pri );
void redutor_movi_terr( int nUnit );
void mover_pelotao_aux( int x, int y, int nUnit );
void mover_pelotao();
void desenhar_info_unit_geral( int x, int y, int nUnit );
void desenhar_info_tipo( int x, int y, int nTipo );
void desenhar_infos_unit( int x, int y, int nUnit );
int dados_unidade( int nUnit );

//Cidad
void preparar_matriz_cidadesI();
void preparar_cidades();
void colocar_cidades_iniciais();
int procurar_cidade( int x, int y );
int procurar_cid_xy( int x, int y );
void desenhar_cidade( int x, int y, cidade cid );
void desenhar_cidades();
void calcular_cidade( int i );
void calcular_cidades();
int procurar_cidade_vazia();
void criar_cidade( int x, int y, int raca, int dono, int quant, int tempo, int nome );
void eliminar_cidade( int N );
int atacar_cidade( int nUnit, int nCid, int quemAtacou );
void desenhar_info_cid_geral( int x, int y, int nCid );
void desenhar_info_treino( int x, int y, int nCid );
void desenhar_focos( int x, int y, int nCid );
void desenhar_infos_cid( cidade cid );
int mudar_treinando( int nCid, int nTipo, int inf );
void preparar_lista_treino( int inicio, cidade cid, int total );
void girar_lista( int sentido );
void desenhar_lista_treino( int x, int y, cidade cid, int total = 0 );
int dados_cidade( int nCid );

//Magia
int tela_alvo_magia( int tipo, int nUnit, int distMax = -1 );
int magias_efeitos_terreno( int x, int y, int tipo, int intensidade, int area, int homogeneo = 0 );
void magias_efeitos_materiais( int jogador, int intensidade, float roubo = 0, int jogFeiticeiro = -1 );
void magias_efeitos_dano( int x, int y, int intensidade, int area, int modo, int elemento, int unicid = 0, int homogeneo = 0 );
void preparar_magias();
int magias_efeitos( int id, int nUnit );
int procurar_magia( int elemento, int nivel, int idAtual );
void preparar_lista_magias( int elemento );
void desenhar_lista_magias( int x, int y, int elemento );
int menu_magias( int elemento, int nUnit );

//Raca
void preparar_raca();

//Jogad
void preparar_jogadores();
void desenhar_infos_jogador( int x, int y, jogador jog );

//Sons
int carregar_sons();

//Salva
int salvar( char nome[10] = NULL );
int carregar( char nome[10] = NULL );
int salvar_preferencias();
int carregar_preferencias();

//Tipos
void preparar_tipos();
int procurar_tipo_vazio();
int procurar_editor_tipos_trava( int nTipo );
void ordenar_tipos();
void eliminar_tipo( int N, int ordem = 1 );
void calcular_tipo( int nTipo );
void calcular_tipos();
int editor_tipos();

//Jogo
void passar_turno();
void passar_jogada( int tipo );
int tela_mapa();
int jogo();

//Rede
void mRede_receber( char texto[50] );
void mRede_imprimir( int x, int y, int tipo );
void mTexto_receber( char texto[100] );
void mTexto_imprimir( int x, int y, int tipo = 0 );
int enviar_dados_rede( void *dado, int tama );
int receber_dados_rede( void *dado, int tama );
int iniciar_servidor();
int iniciar_cliente();
void enviar_turno();
void receber_turno();
int thread_rede_saida( void *data );
int thread_rede_entrada( void *data );

//Comba
int combate( int atacante, int defensor );

#endif
