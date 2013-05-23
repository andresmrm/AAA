#include "AAA.h"

//------------------------------------------------------------------------------

void mRede_receber( char texto[50] )
{
	int i;
	
	for( i = 48; i >= 0; i-- )
	{
		strcpy( mRede[i+1], mRede[i] );
	}
	strcpy( mRede[0], texto );
}

//------------------------------------------------------------------------------

void mRede_imprimir( int x, int y, int tipo )
{
	int i;
	
	if( tipo )
	preencher_fundo();
	
	for( i = 0; i < 50; i++ )
	{
		escrever( x, y + i * 20, mRede[i], fonte16, corVermelha );
	}
	
	if( tipo )
	SDL_Flip( tela );
}

//------------------------------------------------------------------------------

void mTexto_receber( char texto[100] )
{
	int i;
	
	for( i = mTextoTama-2; i >= 0; i-- )
	{
		strcpy( mTexto[i+1], mTexto[i] );
	}
	strcpy( mTexto[0], texto );
}

//------------------------------------------------------------------------------

void mTexto_imprimir( int x, int y, int tipo )
{
	int i;
	
	if( tipo )
	preencher_fundo();
	
	for( i = 0; i < mTextoTama; i++ )
	{
		escrever( x, y + i * 20, mTexto[i] );
	}
	
	if( tipo )
	SDL_Flip( tela );
}

//------------------------------------------------------------------------------

int enviar_dados_rede( void *dado, int tama )
{
		if( SDLNet_TCP_Send( sockConectado, (void *)dado, tama) < tama )
		{
			mRede_receber( "Erro! Não conseguir enviar tudo!" );
			mRede_imprimir( 50, 50, 1 );
			mRede_receber( SDLNet_GetError() );
			mRede_imprimir( 50, 50, 1 ); 
			SDL_Delay( 1000 );
			return -1;
		}
}

//------------------------------------------------------------------------------

int receber_dados_rede( void *dado, int tama )
{
	int quit = 0;
	
	while( quit == 0 )
	{
		if( SDLNet_TCP_Recv( sockConectado, dado, tama ) > 0 )
		{
			quit = 1;
		}
	}
}

//----------------------------SERVIDOR------------------------------------------

int iniciar_servidor()
{
	int x = 50;
	int y = 50;
	
	mRede_receber( "Abrindo Rede..." );
	mRede_imprimir( x, y, 1 );
	
	int len;
	int quit, quit2;
	char teste[100];

	//PortaRede = receber_numero( 4, "PORTA de escuta:" );

	if( SDLNet_Init() < 0 )
	{
		mRede_receber( "Erro! Não carregar NET!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 );
		return -1;
	}
	
	//Preenche "ip" com um IP, NULL é o nome a procurar na rede e 2000 a porta de escuta 
	if( SDLNet_ResolveHost( &servIpLocal, NULL, PortaRede ) < 0 )
	{
		mRede_receber( "Erro! Não ter IP!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 );
		return -1;
	}
	
	if( !strcpy( servIpNome, "NaoSei"/*SDLNet_ResolveIP( &servIpLocal )*/ ) )
	{
		mRede_receber( "Erro! Não converter próprio IP!" );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 );
		return -1;
	}
	
	/*strcpy( aux, "IP: " );
	itoa( SDLNet_Read32(&ip.host), aux2, 10);
	strcat( aux, aux2);*/
		
	strcpy( aux, "IP: " );
	itoa( SDLNet_Read32( servIpNome ), aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	strcpy( aux, "IP Nome: " );
	strcat( aux, servIpNome );
	mRede_receber( aux );

	strcpy( aux, "Porta: " );
	itoa( SDLNet_Read16(&servIpLocal.port), aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	mRede_imprimir( x, y, 1 );
		
	//Open a connection with the IP provided (listen on the host's port)
	if( !( sockOuvinte = SDLNet_TCP_Open(&servIpLocal) ) )
	{
		mRede_receber( "Erro! Não conseguir abrir Socket Ouvinte!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 );
		return -1;
	}
	
	mRede_receber( "Rede aguardando..." );
	mRede_imprimir( x, y, 1 );
	
	//------------------------------------------------------------------------------
	
	//Wait for a connection, send data and term
	var = 0;
	quit = 0;
	while( quit == 0 && var == 0 )
	{
		while( SDL_PollEvent( &evento ) )
		{
			if( evento.type == SDL_KEYDOWN )
			{
			atalhos(10);
			}
		}

		//This check the sd if there is a pending connection.
		//If there is one, accept that, and open a new socket for communicating 
		//Ouve o Socket e retorna NULL se não a nada, ou o TCPsocket do cliente conectando
		//*Não use em um socket que já está conectado!*
		if( ( sockConectado = SDLNet_TCP_Accept( sockOuvinte ) ) )
		{
			mRede_receber( "Cliente connectando..." );
			mRede_imprimir( x, y, 1 );
		
					//Now we can communicate with the client using csd socket
					//sd will remain opened waiting other connections
		
					//Get the remote address
					if( ( servIpCliente = SDLNet_TCP_GetPeerAddress( sockConectado ) ) )
					{
						//Print the address, converting in the host format
						mRede_receber( " - CONECTADO - " );
				mRede_imprimir( x, y, 1 );
				strcpy( aux, "IP: " );
				itoa( SDLNet_Read32(&servIpCliente->host), aux2, 10);
				strcat( aux, aux2);
				mRede_receber( aux );
				mRede_imprimir( x, y, 1 );
				strcpy( aux, "Porta: " );
				itoa( SDLNet_Read16(&servIpCliente->port), aux2, 10);
				strcat( aux, aux2);
				mRede_receber( aux );
				mRede_imprimir( x, y, 1 );
			}
					else
					{
				mRede_receber( "Erro! Não conseguir ler IP do Cliente!" );
				mRede_imprimir( x, y, 1 );
				mRede_receber( SDLNet_GetError() );
				mRede_imprimir( x, y, 1 );
				return -1;
			}
		
			mRede_receber( "Cliente connectado" );
			mRede_imprimir( x, y, 1 );
			SDL_Delay( 2000 );
			
			mRede_receber( "Recebendo dado..." );
			mRede_imprimir( x, y, 1 );
			
			quit2 = 0;
			while( quit2 == 0 )
			{
				//Recebe dado do Socket, garda no segundo termo e com o tamanho máximo de bytes do terceiro termo
				if( SDLNet_TCP_Recv( sockConectado, teste, 100 ) > 0 )
				{
					mTexto_receber( teste );
		
					strcpy( teste, "Servidor Conectado" );
					len = strlen( teste ) + 1;
					
					SDL_Delay( 1000 );
					
					mRede_receber( "Enviando dado..." );
					mRede_imprimir( x, y, 1 );
					
					if( SDLNet_TCP_Send( sockConectado, (void *)teste, len) < len )
					{
						mRede_receber( "Erro! Não conseguir enviar tudo!" );
						mRede_imprimir( x, y, 1 );
						mRede_receber( SDLNet_GetError() );
						mRede_imprimir( x, y, 1 ); 
						SDL_Delay( 1000 );
						return -1;
					}
					mTexto_receber( teste );
					
					mRede_receber( "Rede estabelecida" );
					mRede_imprimir( x, y, 1 );
					
					online = 1;
					quit = 1;
					quit2 = 1;
					
					sockets = SDLNet_AllocSocketSet( 1 );
					if( !sockets )
					{
						mRede_receber( "Erro! Não criar pacote de sockets!" );
						mRede_imprimir( x, y, 1 );
						mRede_receber( SDLNet_GetError() );
						mRede_imprimir( x, y, 1 ); 
						SDL_Delay( 1000 );
						return -1;
					}
					if( SDLNet_TCP_AddSocket( sockets, sockConectado ) == -1 )
					{
						mRede_receber( "Erro! Não adicionar socket a pacote!" );
						mRede_imprimir( x, y, 1 );
						mRede_receber( SDLNet_GetError() );
						mRede_imprimir( x, y, 1 ); 
						SDL_Delay( 1000 );
						return -1;
					}
					
					redeThreadSaida = SDL_CreateThread( thread_rede_saida, NULL );
					redeThreadEntrada = SDL_CreateThread( thread_rede_entrada, NULL );
				}
			}
		}
		SDL_Delay( 250 );
	}
}

//---------------------------CLIENTE--------------------------------------------

int iniciar_cliente()
{
	int x = 50;
	int y = 50;
	
	mRede_receber( "Abrindo Rede..." );
	mRede_imprimir( x, y, 1 );    
		
	int quit, len;
	char teste[100];
		
	//Receber porta e IP a serem procurados
	//receber_texto( 19, "IP do servidor:" );
	//strcpy( ipProcuradoNome, aux2 );
	
	//PortaRede = receber_numero( 4, "PORTA do servidor:" );
	
	strcpy( aux, "IP: " );
	strcat( aux, ipProcuradoNome );
	mRede_receber( aux );
	mRede_imprimir( x, y, 1 );  
	
	strcpy( aux, "Porta: " );
	itoa( PortaRede, aux2, 10);
	strcat( aux, aux2 );
	mRede_receber( aux );
	mRede_imprimir( x, y, 1 ); 
	
	if( SDLNet_Init() < 0 )
	{
		mRede_receber( "Erro! Não carregar NET!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 ); 
		return -1;
	}
		
	mRede_receber( "Procurando Servidor..." );
	mRede_imprimir( x, y, 1 ); 
		
	//Resolve the host we are connecting to
	if( SDLNet_ResolveHost( &clieIpServidor, ipProcuradoNome, PortaRede ) < 0 )
	{
		mRede_receber( "Erro! Servidor não encontrado!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 ); 
		SDL_Delay( 1000 );
		return -1;
	}

	//Open a connection with the IP provided (listen on the host's port)
	if( !( sockConectado = SDLNet_TCP_Open(&clieIpServidor) ) )
	{
		mRede_receber( "Erro! Não conseguir usar IP recebido!" );
		mRede_imprimir( x, y, 1 );
		mRede_receber( SDLNet_GetError() );
		mRede_imprimir( x, y, 1 );
		SDL_Delay( 1000 );
		return -1;
	}
	
	mRede_receber( "Conecção Estabelecida" );
	mRede_imprimir( x, y, 1 );
	
	//-------------------------------------------------------------------------- 
	quit = 0;
	while( quit == 0 )
	{
		strcpy( teste, "Cliente Conectado" );
		len = strlen( teste ) + 1;
		
		SDL_Delay( 1000 );
		
		mRede_receber( "Enviando dado..." );
		mRede_imprimir( x, y, 1 );
		
		if( SDLNet_TCP_Send( sockConectado, (void *)teste, len) < len )
		{
			mRede_receber( "Erro! Não conseguir enviar tudo!" );
			mRede_imprimir( x, y, 1 );
			mRede_receber( SDLNet_GetError() );
			mRede_imprimir( x, y, 1 ); 
			SDL_Delay( 1000 );
			return -1;
		}
		
		mRede_receber( "Recebendo dado..." );
		mRede_imprimir( x, y, 1 );
		
		while( quit == 0 )
		{
			if( SDLNet_TCP_Recv( sockConectado, teste, 100 ) > 0 )
			{
				mTexto_receber( teste );
				
				mRede_receber( "Rede estabelecida" );
				mRede_imprimir( x, y, 1 );
				
				online = 2;
				quit = 1;
				
				sockets = SDLNet_AllocSocketSet( 1 );
				if( !sockets )
				{
					mRede_receber( "Erro! Não criar pacote de sockets!" );
					mRede_imprimir( x, y, 1 );
					mRede_receber( SDLNet_GetError() );
					mRede_imprimir( x, y, 1 ); 
					SDL_Delay( 1000 );
					return -1;
				}
				if( SDLNet_TCP_AddSocket( sockets, sockConectado ) == -1 )
				{
					mRede_receber( "Erro! Não adicionar socket a pacote!" );
					mRede_imprimir( x, y, 1 );
					mRede_receber( SDLNet_GetError() );
					mRede_imprimir( x, y, 1 ); 
					SDL_Delay( 1000 );
					return -1;
				}
				redeThreadSaida = SDL_CreateThread( thread_rede_saida, NULL );
				redeThreadEntrada = SDL_CreateThread( thread_rede_entrada, NULL );
			}
			SDL_Delay( 250 );
		}
	}
}

//------------------------------------------------------------------------------

void enviar_turno()
{
	int i;
	int x;
	int y;
	int cont;
	int num;

	mRede_receber( "Enviando dados do turno..." );
	
	//Mapa
	for( y = 0; y < TAM_MAPA_Y; y++ )
	{
		for( x = 0; x < TAM_MAPA_X; x++ )
		{
			//enviar_dados_rede( &mapa[x][y], sizeof(territorio) );
			num = (mapa[x][y].agua * 1000) + (mapa[x][y].relevo * 100) + (mapa[x][y].temperatura * 10) + (mapa[x][y].vegetacao * 1);
			enviar_dados_rede( &num, sizeof(int) );
			num = (mapa[x][y].x * 100) + (mapa[x][y].y * 1);
			enviar_dados_rede( &num, sizeof(int) );
		}
	}
	
	//Turno
	enviar_dados_rede( &turno, sizeof(int) );
	enviar_dados_rede( &jogadorAtual, sizeof(int) );
	
	//Tipos
	cont = 0;
	for( i = 0; i < numTipos ; i++ )
	{
		if( tipos[i].raca >= 0 )
		{
			cont++;
		}
	}
	enviar_dados_rede( &cont, sizeof(int) );
	for( i = 0; i < numTipos ; i++ )
	{
		if( tipos[i].raca >= 0 )
		{
			//enviar_dados_rede( &tipos[i], sizeof(tipo) );
			//enviar_dados_rede( &tipos[i], 20*sizeof(int) );
			enviar_dados_rede( &tipos[i].arco, sizeof(int) );
			enviar_dados_rede( &tipos[i].ataque, sizeof(int) );
			enviar_dados_rede( &tipos[i].corpo, sizeof(int) );
			enviar_dados_rede( &tipos[i].dano, sizeof(int) );
			enviar_dados_rede( &tipos[i].defesa, sizeof(int) );
			enviar_dados_rede( &tipos[i].dono, sizeof(int) );
			enviar_dados_rede( &tipos[i].lanca, sizeof(int) );
			enviar_dados_rede( &tipos[i].magia, sizeof(int) );
			enviar_dados_rede( &tipos[i].magia2, sizeof(int) );
			enviar_dados_rede( &tipos[i].mana, sizeof(int) );
			enviar_dados_rede( &tipos[i].materiais, sizeof(int) );
			enviar_dados_rede( &tipos[i].materiais2, sizeof(int) );
			enviar_dados_rede( &tipos[i].montaria, sizeof(int) );
			enviar_dados_rede( &tipos[i].movimento, sizeof(int) );
			enviar_dados_rede( &tipos[i].nivelMagico, sizeof(int) );
			enviar_dados_rede( &tipos[i].raca, sizeof(int) );
			enviar_dados_rede( &tipos[i].tipoDano, sizeof(int) );
			enviar_dados_rede( &tipos[i].treino, sizeof(int) );
			enviar_dados_rede( &tipos[i].treino2, sizeof(int) );
			enviar_dados_rede( &tipos[i].vida, sizeof(int) );
			
			enviar_dados_rede( &tipos[i].nome, 20 );
		}
	}
	
	//Pelotões
	cont = 0;
	for( i = 0; i < numPelotoes ; i++ )
	{
		if( unidades[i].tipo >= 0 )
		{
			cont++;
		}
	}
	enviar_dados_rede( &cont, sizeof(int) );
	for( i = 0; i < numPelotoes ; i++ )
	{
		if( unidades[i].tipo >= 0 )
		{
			//enviar_dados_rede( &unidades[i], sizeof(pelotao) );
			//enviar_dados_rede( &unidades[i], 7*sizeof(int) );
			
			enviar_dados_rede( &unidades[i].dono, sizeof(int) );
			enviar_dados_rede( &unidades[i].movimentos, sizeof(int) );
			enviar_dados_rede( &unidades[i].nivelMagico, sizeof(int) );
			enviar_dados_rede( &unidades[i].quantidade, sizeof(int) );
			enviar_dados_rede( &unidades[i].tipo, sizeof(int) );
			enviar_dados_rede( &unidades[i].x, sizeof(int) );
			enviar_dados_rede( &unidades[i].y, sizeof(int) );
			
			enviar_dados_rede( &unidades[i].nome, 20 );
		}
	}
		
	//Cidades
	cont = 0;
	for( i = 0; i < numCidades ; i++ )
	{
		if( cidades[i].raca >= 0 )
		{
			cont++;
		}
	}
	enviar_dados_rede( &cont, sizeof(int) );
	for( i = 0; i < numCidades ; i++ )
	{
		if( cidades[i].raca >= 0 )
		{
			//enviar_dados_rede( &cidades[i], sizeof(cidade) );
			//enviar_dados_rede( &cidades[i], 13*sizeof(int) );
			//enviar_dados_rede( &cidades[i].crescimento, 3*sizeof(float) );
			
			enviar_dados_rede( &cidades[i].completado, sizeof(int) );
			enviar_dados_rede( &cidades[i].dono, sizeof(int) );
			enviar_dados_rede( &cidades[i].emConstr, sizeof(int) );
			enviar_dados_rede( &cidades[i].foco, sizeof(int) );
			enviar_dados_rede( &cidades[i].infTreino, sizeof(int) );
			enviar_dados_rede( &cidades[i].magia, sizeof(int) );
			enviar_dados_rede( &cidades[i].materiais, sizeof(int) );
			enviar_dados_rede( &cidades[i].raca, sizeof(int) );
			enviar_dados_rede( &cidades[i].treinamento, sizeof(int) );
			enviar_dados_rede( &cidades[i].treinando, sizeof(int) );
			enviar_dados_rede( &cidades[i].treinandoQuant, sizeof(int) );
			enviar_dados_rede( &cidades[i].x, sizeof(int) );
			enviar_dados_rede( &cidades[i].y, sizeof(int) );
		
			enviar_dados_rede( &cidades[i].crescimento, sizeof(float) );
			enviar_dados_rede( &cidades[i].maxPopulacao, sizeof(float) );
			enviar_dados_rede( &cidades[i].populacao, sizeof(float) );
			
			enviar_dados_rede( &cidades[i].nome, 25 );
		}
	}
	
	//Jogadores
	enviar_dados_rede( &numJogadoresUsados, sizeof(int) );
	for( i = 0; i < numJogadoresUsados ; i++ )
	{
		//enviar_dados_rede( &jogadores[i], sizeof(jogador) );
		//enviar_dados_rede( &jogadores[i], 7*sizeof(int) );
		
		enviar_dados_rede( &jogadores[i].cor, sizeof(int) );
		enviar_dados_rede( &jogadores[i].populacao, sizeof(int) );
		enviar_dados_rede( &jogadores[i].raca, sizeof(int) );
		enviar_dados_rede( &jogadores[i].telaX, sizeof(int) );
		enviar_dados_rede( &jogadores[i].telaY, sizeof(int) );
		enviar_dados_rede( &jogadores[i].x, sizeof(int) );
		enviar_dados_rede( &jogadores[i].y, sizeof(int) );
		
		enviar_dados_rede( &jogadores[i].materiais, sizeof(Uint32) );
		enviar_dados_rede( &jogadores[i].mana, sizeof(Uint32) );
		
		enviar_dados_rede( &jogadores[i].nome, 20 );
	}
	
	i = 0;
	receber_dados_rede( &i, sizeof(int) );
	if( i == 1 )
	{
		mRede_receber( "Dados do turno enviados" );
	}
	else
	{
		mRede_receber( "Erro! Turno enviado erroneamente!" );
	}
}

//------------------------------------------------------------------------------

void receber_turno()
{
	int i;
	int x;
	int y;
	int cont;
	int num;
	
	mRede_receber( "Recebendo dados do turno..." );        
	
	mRede_receber( "Mapa" );
	//Mapa
	for( y = 0; y < TAM_MAPA_Y; y++ )
	{
		for( x = 0; x < TAM_MAPA_X; x++ )
		{
			//receber_dados_rede( &mapa[x][y], sizeof(territorio) );
			
			receber_dados_rede( &num, sizeof(int) );
			mapa[x][y].vegetacao = num % 10;
			num = num / 10;
			mapa[x][y].temperatura = num % 10;
			num = num / 10;
			mapa[x][y].relevo = num % 10;
			num = num / 10;
			mapa[x][y].agua = num % 10;
			
			receber_dados_rede( &num, sizeof(int) );
			mapa[x][y].y = num % 100;
			num = num / 100;
			mapa[x][y].x = num % 100;
		}
	}
	
	//Turno
	receber_dados_rede( &turno, sizeof(int) );
	
	strcpy( aux, "Turno: ");
	itoa( turno, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	receber_dados_rede( &jogadorAtual, sizeof(int) );
	
	strcpy( aux, "JogadorAtual: ");
	itoa( jogadorAtual, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	//Tipos
	receber_dados_rede( &cont, sizeof(int) );
	
	strcpy( aux, "Tipos: ");
	itoa( cont, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	for( i = 0; i < numTipos; i++ )
	{
		eliminar_tipo( i, 0 );
	}
	for( i = 0; i < cont; i++ )
	{
		//receber_dados_rede( &tipos[i], sizeof(tipo) );
		//receber_dados_rede( &tipos[i], 20*sizeof(int) );
		
		receber_dados_rede( &tipos[i].arco, sizeof(int) );
		receber_dados_rede( &tipos[i].ataque, sizeof(int) );
		receber_dados_rede( &tipos[i].corpo, sizeof(int) );
		receber_dados_rede( &tipos[i].dano, sizeof(int) );
		receber_dados_rede( &tipos[i].defesa, sizeof(int) );
		receber_dados_rede( &tipos[i].dono, sizeof(int) );
		receber_dados_rede( &tipos[i].lanca, sizeof(int) );
		receber_dados_rede( &tipos[i].magia, sizeof(int) );
		receber_dados_rede( &tipos[i].magia2, sizeof(int) );
		receber_dados_rede( &tipos[i].mana, sizeof(int) );
		receber_dados_rede( &tipos[i].materiais, sizeof(int) );
		receber_dados_rede( &tipos[i].materiais2, sizeof(int) );
		receber_dados_rede( &tipos[i].montaria, sizeof(int) );
		receber_dados_rede( &tipos[i].movimento, sizeof(int) );
		receber_dados_rede( &tipos[i].nivelMagico, sizeof(int) );
		receber_dados_rede( &tipos[i].raca, sizeof(int) );
		receber_dados_rede( &tipos[i].tipoDano, sizeof(int) );
		receber_dados_rede( &tipos[i].treino, sizeof(int) );
		receber_dados_rede( &tipos[i].treino2, sizeof(int) );
		receber_dados_rede( &tipos[i].vida, sizeof(int) );
		
		receber_dados_rede( &tipos[i].nome, 20 );
	}
	
	//Pelotões
	receber_dados_rede( &cont, sizeof(int) );
	
	strcpy( aux, "Pelotões: ");
	itoa( cont, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	for( i = 0; i < numPelotoes; i++ )
	{
		eliminar_pelotao( i, 0 );
	}
	for( i = 0; i < cont; i++ )
	{
		//receber_dados_rede( &unidades[i], sizeof(pelotao) );
		//receber_dados_rede( &unidades[i], 7*sizeof(int) );
		
		receber_dados_rede( &unidades[i].dono, sizeof(int) );
		receber_dados_rede( &unidades[i].movimentos, sizeof(int) );
		receber_dados_rede( &unidades[i].nivelMagico, sizeof(int) );
		receber_dados_rede( &unidades[i].quantidade, sizeof(int) );
		receber_dados_rede( &unidades[i].tipo, sizeof(int) );
		receber_dados_rede( &unidades[i].x, sizeof(int) );
		receber_dados_rede( &unidades[i].y, sizeof(int) );
		
		receber_dados_rede( &unidades[i].nome, 20 );
	}
	
	//Cidades
	receber_dados_rede( &cont, sizeof(int) );
	
	strcpy( aux, "Cidades: ");
	itoa( cont, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	for( i = 0; i < numCidades; i++ )
	{
		eliminar_cidade( i );
	}
	for( i = 0; i < cont; i++ )
	{
		//receber_dados_rede( &cidades[i], sizeof(cidade) );
		//receber_dados_rede( &cidades[i], 13*sizeof(int) );
		//receber_dados_rede( &cidades[i].crescimento, 3*sizeof(float) );
		
		receber_dados_rede( &cidades[i].completado, sizeof(int) );
		receber_dados_rede( &cidades[i].dono, sizeof(int) );
		receber_dados_rede( &cidades[i].emConstr, sizeof(int) );
		receber_dados_rede( &cidades[i].foco, sizeof(int) );
		receber_dados_rede( &cidades[i].infTreino, sizeof(int) );
		receber_dados_rede( &cidades[i].magia, sizeof(int) );
		receber_dados_rede( &cidades[i].materiais, sizeof(int) );
		receber_dados_rede( &cidades[i].raca, sizeof(int) );
		receber_dados_rede( &cidades[i].treinamento, sizeof(int) );
		receber_dados_rede( &cidades[i].treinando, sizeof(int) );
		receber_dados_rede( &cidades[i].treinandoQuant, sizeof(int) );
		receber_dados_rede( &cidades[i].x, sizeof(int) );
		receber_dados_rede( &cidades[i].y, sizeof(int) );
		
		receber_dados_rede( &cidades[i].crescimento, sizeof(float) );
		receber_dados_rede( &cidades[i].maxPopulacao, sizeof(float) );
		receber_dados_rede( &cidades[i].populacao, sizeof(float) );
		
		receber_dados_rede( &cidades[i].nome, 25 );
	}
	
	//Jogadores
	receber_dados_rede( &numJogadoresUsados, sizeof(int) );  
		
	strcpy( aux, "Jogadores: ");
	itoa( numJogadoresUsados, aux2, 10);
	strcat( aux, aux2);
	mRede_receber( aux );
	
	for( i = 0; i < numJogadoresUsados; i++ )
	{
		//receber_dados_rede( &jogadores[i], sizeof(jogador) );
		//receber_dados_rede( &jogadores[i], 7*sizeof(int) );
		//receber_dados_rede( &jogadores[i].materiais, 2*sizeof(Uint32) );
		
		receber_dados_rede( &jogadores[i].cor, sizeof(int) );
		receber_dados_rede( &jogadores[i].populacao, sizeof(int) );
		receber_dados_rede( &jogadores[i].raca, sizeof(int) );
		receber_dados_rede( &jogadores[i].telaX, sizeof(int) );
		receber_dados_rede( &jogadores[i].telaY, sizeof(int) );
		receber_dados_rede( &jogadores[i].x, sizeof(int) );
		receber_dados_rede( &jogadores[i].y, sizeof(int) );
		
		receber_dados_rede( &jogadores[i].materiais, sizeof(Uint32) );
		receber_dados_rede( &jogadores[i].mana, sizeof(Uint32) );
		
		receber_dados_rede( &jogadores[i].nome, 20 );
	}
	
	i = 1;
	enviar_dados_rede( &i, sizeof(int) );
	
	mRede_receber( "Dados do turno recebidos" );
	
	SDL_Delay( 1000 );
}

//------------------------------------------------------------------------------

int thread_rede_saida( void *data )
{ 
	//While the program is not over 
	while( var != -1 ) 
	{
		if( novaSaida > 0 )
		{
			enviar_dados_rede( &novaSaida, sizeof(int) );
			
			//Mensagem mTexto
			if( novaSaida == 1 )
			{
				enviar_dados_rede( mTexto[0], mTextoComp );
			}
			
			//Enviar Dados do Turno
			if( novaSaida == 2 )
			{
				enviar_turno();
			}
			
			novaSaida = 0;
		}
		
		SDL_Delay( 100 );
	} 
	
	return 0;
}

//------------------------------------------------------------------------------

int thread_rede_entrada( void *data )
{
	int numready = 0;
	int sinal;
	
	//While the program is not over 
	while( var != -1 )
	{
		sinal = 0;
		
		numready=SDLNet_CheckSockets( sockets, 100 );
		if( numready == -1 )
		{
			mRede_receber( "Erro! Sem respota dos sockets!" );
			mRede_receber( SDLNet_GetError() );
			SDL_Delay( 1000 );
			return -1;
		}
	
			// check to see if the server sent us data
		if( numready && SDLNet_SocketReady( sockConectado ) )
		{
			receber_dados_rede( &sinal, sizeof(int) );
			
			//Mensagem para mTexto
			if( sinal == 1 )
			{
				receber_dados_rede( aux2, mTextoComp );
				mTexto_receber( aux2 );
			}
			
			//Receber Dados do Turno
			if( sinal == 2 )
			{
				receber_turno();
				esperaOnline = 0;
			}
			
			if( sinal == 10 )
			{
				preparar_tipos();
				preparar_pelotoes();
				preparar_cidades();
				calcular_cidades();
				jogadorAtual = 0;
				preparar_mapa();
				colocar_cidades_iniciais();
				
				novaSaida = 2;
			}
		
			SDL_Delay( 100 );
		}
		
	} 
	return 0;
}
