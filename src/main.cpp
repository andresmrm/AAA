#include "AAA.h"

/*
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_thread.h"
#include <time.h>
*/

/*#include <time.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_audio.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_opengl.h"*/

/*-lmingw32
-lSDLmain
-lSDL
-lSDL_image
-lSDL_ttf
-lSDL_mixer
-lSDL_net
../lib/libopengl32.a
*/

//------------------------------------------------------------------------------

int main( int argc, char* args[] )
{
	srand(time (0));
	
	if( iniciar_SDL() == 0 )
	{
		return 1;
	}
	
	neve[0] = 0;
	neve[1] = 10;
	neve[2] = 10;
	relevo[0] = 0;
	relevo[1] = 10;
	relevo[2] = 10;
	deserto[0] = 0;
	deserto[1] = 10;
	deserto[2] = 10;
	vegetacao[0] = 0;
	vegetacao[1] = 10;
	vegetacao[2] = 10;
	
	preparar_matriz_botoesI();
	preparar_matriz_bordasI();
	preparar_matriz_terrenosI();
	preparar_matriz_unidadesI();
	preparar_matriz_cidadesI();
	preparar_magias();
	preparar_raca();
	preparar_jogadores();
	carregar_sons();
	
	carregar_preferencias();
	iniciar_tela();
	
	botoesImagem = carregar_imagem( "botoes.png" );
	bordasImagem = carregar_imagem( "bordas.png" );
	cidadesImagem = carregar_imagem( "cidades.png" );
	terrenosImagem = carregar_imagem( "terrenos.png" );
	unidadesImagem = carregar_imagem( "unidades.png" );
	
	fonte12 = TTF_OpenFont( "verdana.ttf", 12 );
	fonte16 = TTF_OpenFont( "verdana.ttf", 16 ); 
	fonte20 = TTF_OpenFont( "verdana.ttf", 20 );
	fonte26 = TTF_OpenFont( "verdana.ttf", 26 ); 
	
	int i;
	for( i = 0; i < numPs; i++ )
	{
		selecaoPs[i] = -1;
	}
	
	while( var != -1 )
	{
		//preparar_mapa(),colocar_cidades_iniciais(),jogo();
		//menu_preparar_jogo();
		
		menu_principal();
		if( var == 1 )
		{
			menu_preparar_jogo();
			
			if( var == 1 )
			{
				preparar_tipos();
				preparar_pelotoes();
				preparar_cidades();
				calcular_cidades();
				jogadorAtual = 0;
			
				preparar_mapa();
				colocar_cidades_iniciais();
				ordenar_tipos();
				ordenar_pelotoes();
				
				jogo();
			}
		}
		else if( var == 2 )
		{
			menu_carregar_jogo();
		}
		else if( var == 3 )
		{
			menu_preferencias();
		}
		else if( var == 4 )
		{
			creditos();
		}
		else if( var == 5 )
		{
			while( var != -2 && var != -1 )
			{
				menu_rede();
				if( var == 1 )
				{
					var = 0;
					iniciar_servidor();
				}
				else if( var == 2 )
				{
					var = 0;
					iniciar_cliente();
				}
				
				if( online == 2 )
				{
					menu_espera_jogada();
					passar_jogada( 0 );
					jogo();
				}
			}
		}
	}
	
	//Finalizar
	salvar_preferencias();
	
	SDL_FreeSurface( botoesImagem );
	SDL_FreeSurface( unidadesImagem );
	SDL_FreeSurface( bordasImagem );
	SDL_FreeSurface( terrenosImagem );
	SDL_FreeSurface( cidadesImagem );
	
	TTF_CloseFont( fonte12 );
	TTF_CloseFont( fonte16 );
	TTF_CloseFont( fonte20 );
	TTF_CloseFont( fonte26 );
	TTF_Quit();
	
	//SDLNet_TCP_Close( sockCliente );
	SDLNet_TCP_Close( sockConectado );
	SDLNet_TCP_Close( sockOuvinte );
	SDLNet_Quit();
	
	Mix_FreeMusic( click );
	Mix_CloseAudio();
	
	SDL_KillThread( redeThreadSaida );
	SDL_KillThread( redeThreadEntrada );
	SDL_Quit();
	
	return 0;
}
