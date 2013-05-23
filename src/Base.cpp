#include "AAA.h"

//------------------------------------------------------------------------------

int modulo( int n )
{
	if( n < 0 )
	{
		return n*-1;
	}
	if( n >= 0 )
	{
		return n;
	}
}

//------------------------------------------------------------------------------

int maior( int n1, int n2 )
{
	if( n1 >= n2 )
	{
		return n1;
	}
	if( n2 > n1 )
	{
		return n2;
	}
}

//------------------------------------------------------------------------------

int distancia( int x, int y, int x0, int y0 )
{
	int dist;
	
	dist = maior( modulo( x - x0 ), modulo( y - y0 ) );
	
	return dist;
}

//------------------------------------------------------------------------------

int init_GL()
{
	//Set clear color
	glClearColor( 0, 0, 0, 0 );
	
	//Set projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	//The 5th argument is near which is set to z = -1. The 6th argument is far which is set to z = 1.
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );
	
	//Initialize modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	//If there was any errors
	if( glGetError() != GL_NO_ERROR )
	{
		return -1;
	}
	
	//If everything initialized
	return 1;
}

//------------------------------------------------------------------------------

int iniciar_SDL()
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 0;
	}
	
	/*//Set up the screen
	//tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN );
	//tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_FULLSCREEN );
	
	//If there was an error in setting up the screen
	if( tela == NULL )
	{
		SCREEN_WIDTH = 800;
		SCREEN_HEIGHT = 600;
		SCREEN_BPP = 24;
		tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN );
		if( tela == NULL )
		{
		tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
		if( tela == NULL )
		{
			return 0;
		}
		}
	}*/
	
	//Initialize OpenGL 
	/*if( init_GL() == -1 )
	{ 
		return 0; 
	}*/
	
	//Initialize SDL_ttf 
	if( TTF_Init() == -1 ) 
	{ 
		return 0;
	}
	
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return 0;
	}
	
	//Set the window caption 
	SDL_WM_SetCaption( "AAA", NULL );
	
	//If everything initialized fine
	return 1;
}

//------------------------------------------------------------------------------

int iniciar_tela()
{
	
	//Set up the screen
	//tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if( telaCheia )
	{
		tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN );
	}
	else
	{
		tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
	}
	//tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_FULLSCREEN );
	
	//If there was an error in setting up the screen
	if( tela == NULL )
	{
		SCREEN_WIDTH = 800;
		SCREEN_HEIGHT = 600;
		SCREEN_BPP = 24;
		tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );
		if( tela == NULL )
		{
			tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
			if( tela == NULL )
			{
				return 0;
			}
		}
	}
}


//------------------------------------------------------------------------------

SDL_Surface *carregar_imagem( char* arquivo ) 
{
	//Temporary storage for the image that's loaded
	SDL_Surface* imagemCarregada = NULL;
	//The optimized image that will be used
	SDL_Surface* imagemOptimizada = NULL;
	
	//Load the image
	imagemCarregada = IMG_Load( arquivo );
	
		
	//If nothing went wrong in loading the image
	if( imagemCarregada != NULL )
	{
		//Create an optimized image
		imagemOptimizada = SDL_DisplayFormat( imagemCarregada );
		
		//Free the old image
		SDL_FreeSurface( imagemCarregada );
	
		//If the image was optimized just fine
		if( imagemOptimizada != NULL )
		{
			//Map the color key
			Uint32 corInvisivel = SDL_MapRGB( imagemOptimizada->format, 0xFF, 0, 0xFF );
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
			SDL_SetColorKey( imagemOptimizada, SDL_RLEACCEL | SDL_SRCCOLORKEY, corInvisivel );
		}
	}
	
	//Return the optimized image
	return imagemOptimizada;
}

//------------------------------------------------------------------------------

void aplicar_superficie( int x, int y, SDL_Surface* superficie, SDL_Surface* destino, SDL_Rect* parte )
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect posicao;
	
	//Give the offsets to the rectangle
	posicao.x = ( x * SCREEN_WIDTH ) / 1024;
	posicao.y = ( y * SCREEN_HEIGHT ) / 768;
	
	//Blit the surface
	SDL_BlitSurface( superficie, parte, destino, &posicao );
}

//------------------------------------------------------------------------------

void escrever( int x, int y, char frase[30], TTF_Font* fonte, SDL_Color cor )
{
	SDL_Surface *texto;
	texto = TTF_RenderText_Blended( fonte, frase, cor );
	aplicar_superficie( ( x * SCREEN_WIDTH ) / 1024, ( y * SCREEN_HEIGHT ) / 768, texto, tela );
	SDL_FreeSurface( texto );
}

//------------------------------------------------------------------------------

void escrever_centro( int y, char frase[30], TTF_Font* fonte, SDL_Color cor )
{
	SDL_Surface *texto;
	texto = TTF_RenderText_Blended( fonte, frase, cor );
	aplicar_superficie( ( SCREEN_WIDTH - texto->w ) / 2, y, texto, tela );
	SDL_FreeSurface( texto );
}

//------------------------------------------------------------------------------

void controlar_frame()
{
	tempo2 = SDL_GetTicks();
	tempo = tempo2-tempo;
	if( tempo < 1000 / FRAMES_PER_SECOND )
	{
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - tempo );
	}
	tempo = SDL_GetTicks();
}

//------------------------------------------------------------------------------

void receber_texto( int tamanho, char texto[] )
{
	int i = 0;
	int flag = 0;
	
	char nome[100];
	char letra = ' ';
	
	SDL_EnableUNICODE( SDL_ENABLE ); 
	
	//strcpy( nome, "           ");
	
	for( i = 0; i < tamanho; i++ )
	{
		nome[i] = ' ';
	}
	
	i = 0;
	while( flag == 0 && i < tamanho )
	{
		while( SDL_PollEvent( &evento ) )
		{
			if( evento.type == SDL_KEYDOWN )
			{
				if( evento.key.keysym.unicode == (Uint16)' ' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( ( evento.key.keysym.unicode >= (Uint16)'0' ) && ( evento.key.keysym.unicode <= (Uint16)'9' ) )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( ( evento.key.keysym.unicode >= (Uint16)'A' ) && ( evento.key.keysym.unicode <= (Uint16)'Z' ) )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( ( evento.key.keysym.unicode >= (Uint16)'a' ) && ( evento.key.keysym.unicode <= (Uint16)'z' ) )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'.' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'?' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'!' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'+' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'-' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'_' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'&' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'(' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)')' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'"' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'=' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)':' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)';' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'*' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'%' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)'#' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( evento.key.keysym.unicode == (Uint16)',' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				
				if( ( evento.key.keysym.sym == SDLK_BACKSPACE ) && ( i > 0 ) )
				{
					i--;
					letra = ' ';
					nome[i] = letra;
				}
				else if( ( evento.key.keysym.sym == SDLK_DELETE ) )
				{
					letra = ' ';
					nome[i] = letra;
				}
				else if( ( evento.key.keysym.sym == SDLK_LEFT ) && ( i > 0 ) )
				{
					i--;
				}
				else if( ( evento.key.keysym.sym == SDLK_RIGHT ) )
				{
					i++;
				}
				else if( evento.key.keysym.sym == SDLK_RETURN )
				{
					flag = 1;
				}
			}
		}
		
		aplicar_superficie( 270, 350, bordasImagem, tela, &bordasI[11] );
		escrever( 290, 370, texto, fonte16 );
		escrever( 290, 420, nome, fonte20 );
		SDL_Flip( tela );
		controlar_frame();
	}
	
	strcpy( aux2, nome );
	
	SDL_EnableUNICODE( SDL_DISABLE );
}

//------------------------------------------------------------------------------

int receber_numero( int tamanho, char texto[] )
{
	int i = 0;
	int flag = 0;
	int numero = 0;
	
	char nome[100];
	char letra = ' ';
	
	SDL_EnableUNICODE( SDL_ENABLE ); 
	
	strcpy( nome, "                ");
	
	/*for( i = 0; i < 16; i++ )
	{
		nome[i] = ' ';
	}*/
	
	i = 0;
	while( flag == 0 && i < tamanho )
	{
		while( SDL_PollEvent( &evento ) )
		{
			if( evento.type == SDL_KEYDOWN )
			{
				if( evento.key.keysym.unicode == (Uint16)' ' )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				else if( ( evento.key.keysym.unicode >= (Uint16)'0' ) && ( evento.key.keysym.unicode <= (Uint16)'9' ) )
				{
					letra = (char)evento.key.keysym.unicode;
					nome[i] = letra;
					i++;
				}
				if( ( evento.key.keysym.sym == SDLK_BACKSPACE ) && ( i > 0 ) )
				{
					i--;
					letra = ' ';
					nome[i] = letra;
					
				}
				if( evento.key.keysym.sym == SDLK_RETURN )
				{
					flag = 1;
				}
			}
		}
		
		aplicar_superficie( 270, 350, bordasImagem, tela, &bordasI[11] );
		escrever( 290, 370, texto, fonte16 );
		escrever( 290, 420, nome, fonte20 );
		SDL_Flip( tela );
		controlar_frame();
	}
	
	numero = atoi( nome );
	
	SDL_EnableUNICODE( SDL_DISABLE );
	
	return numero;
}

//------------------------------------------------------------------------------
