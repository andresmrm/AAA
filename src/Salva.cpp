#include "AAA.h"

int salvar( char nome[10] )
{
	int i;
	int x;
	int y;
	int cont = 0;
	FILE *arquivo;
	
	if( nome == NULL )
	{
		arquivo = fopen( "1.aaa","wb" );
	}
	else
	{
		arquivo = fopen( nome,"wb" );
	}
	
	if( arquivo == NULL )
	{
		return 0;
	}
	else
	{
		escrever( 400, 400, "Salvando", fonte20, corVermelha );
		SDL_Flip( tela );
		
		fflush(stdin);
		
		//Mapa
		for( y = 0; y < TAM_MAPA_Y; y++ )
		{
			for( x = 0; x < TAM_MAPA_X; x++ )
			{
				fwrite( &mapa[x][y], sizeof(territorio), 1, arquivo );
			}
		}
		
		//Turno
		fwrite( &turno, sizeof(int), 1, arquivo );
		fwrite( &jogadorAtual, sizeof(int), 1, arquivo );
		//Tela
		fwrite( &telaX, sizeof(int), 1, arquivo );
		fwrite( &telaY, sizeof(int), 1, arquivo );
		
		//Tipos
		/*cont = 0;
		for( i = 0; i < numTipos ; i++ )
		{
		if( tipos[i].raca >= 0 )
		{
			cont++;
		}
		}*/
		ordenar_tipos();
		fwrite( &numTiposUsados, sizeof(int), 1, arquivo );
		for( i = 0; i < numTiposUsados ; i++ )
		{
			if( tipos[i].raca >= 0 )
			{
				fwrite( &tipos[i], sizeof(tipo), 1, arquivo );
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
		fwrite( &cont, sizeof(int), 1, arquivo );
		for( i = 0; i < numPelotoes; i++ )
		{
			if( unidades[i].tipo >= 0 )
			{
				fwrite( &unidades[i], sizeof(pelotao), 1, arquivo );
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
		fwrite( &cont, sizeof(int), 1, arquivo );
		for( i = 0; i < numCidades ; i++ )
		{
			if( cidades[i].raca >= 0 )
			{
				fwrite( &cidades[i], sizeof(cidade), 1, arquivo );
			}
		}
		
		//Jogadores
		fwrite( &numJogadoresUsados, sizeof(int), 1, arquivo );
		for( i = 0; i < numJogadoresUsados ; i++ )
		{
			fwrite( &jogadores[i], sizeof(jogador), 1, arquivo );
		}
		
		fclose(arquivo);
	}
}

//------------------------------------------------------------------------------

int carregar( char nome[10] )
{
	int i;
	int x;
	int y;
	int cont = 0;
	FILE *arquivo;
	
	if( nome == NULL )
	{
		arquivo = fopen("1.aaa","rb");
	}
	else
	{
		arquivo = fopen( nome,"rb" );
	}
	
	if( arquivo == NULL )
	{
		return 0;
	}
	else
	{
		escrever( 400, 400, "Carregando", fonte20, corVermelha );
		SDL_Flip( tela );
		
		//Mapa
		for( y = 0; y < TAM_MAPA_Y; y++ )
		{
			for( x = 0; x < TAM_MAPA_X; x++ )
			{
				fread( &mapa[x][y], sizeof(territorio), 1, arquivo );
			}
		}
		
		//Turno
		fread( &turno, sizeof(int), 1, arquivo );
		fread( &jogadorAtual, sizeof(int), 1, arquivo );
		//Tela
		fread( &telaX, sizeof(int), 1, arquivo );
		fread( &telaY, sizeof(int), 1, arquivo );
		
		//Tipos
		fread( &numTiposUsados, sizeof(int), 1, arquivo );
		for( i = 0; i < numTipos; i++ )
		{
			eliminar_tipo( i, 0 );
		}
		for( i = 0; i < numTiposUsados; i++ )
		{
			fread( &tipos[i], sizeof(tipo), 1, arquivo );
		}
		
		//Pelotões
		//fread( &numPelotoesUsados, sizeof(int), 1, arquivo );
		//for( i = 0; i < numPelotoesUsados; i++ )
		fread( &cont, sizeof(int), 1, arquivo );
		for( i = 0; i < numPelotoes; i++ )
		{
			eliminar_pelotao( i, 0 );
		}
		for( i = 0; i < cont; i++ )
		{
			fread( &unidades[i], sizeof(pelotao), 1, arquivo );
		}
		
		//Cidades
		fread( &cont, sizeof(int), 1, arquivo );
		for( i = 0; i < numCidades; i++ )
		{
			eliminar_cidade( i );
		}
		for( i = 0; i < cont; i++ )
		{
			fread( &cidades[i], sizeof(cidade), 1, arquivo );
		}
		
		//Jogadores
		fread( &numJogadoresUsados, sizeof(int), 1, arquivo );  
		for( i = 0; i < numJogadoresUsados; i++ )
		{
			fread( &jogadores[i], sizeof(jogador), 1, arquivo );
		}
		
		fclose(arquivo);
	}
}

//------------------------------------------------------------------------------

int salvar_preferencias()
{
	#define FINALIZA_SPREF strcat( aux, aux2 );strcat( aux, "\n" );fputs( aux, arquivo );
	
	int i = 0;
	FILE *arquivo;
	
	arquivo = fopen( "prefe.txt","w+" );
	
	if( arquivo == NULL )
	{
		return 0;
	}
	else
	{
		//escrever( 400, 400, "Salvando Preferências", fonte20, corVermelha );
		//SDL_Flip( tela );
		
		fflush(stdin);
		
		//Vídeo
		strcpy( aux, "\n/Vídeo\n" );
		fputs( aux, arquivo );
		strcpy( aux, "Comprimento da Tela: " );
		itoa( SCREEN_WIDTH, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Altura da Tela: " );
		itoa( SCREEN_HEIGHT, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cores da Tela: " );
		itoa( SCREEN_BPP, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Tela Cheia: " );
		itoa(telaCheia, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Quadros por Segundo: " );
		itoa( FRAMES_PER_SECOND, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Comprimento da Tela do Mapa: " );
		itoa( TAM_TELA_X, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Altura da Tela do Mapa: " );
		itoa( TAM_TELA_Y, aux2, 10);
		FINALIZA_SPREF
		
		//Fontes
		strcpy( aux, "\n/Fonte\n" );
		strcpy( aux, "Cor do texto R: " );
		itoa( textColor.r, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cor do texto G: " );
		itoa( textColor.g, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cor do texto B: " );
		itoa( textColor.b, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cor do texto2 R: " );
		itoa( corVermelha.r, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cor do texto2 G: " );
		itoa( corVermelha.g, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Cor do texto2 B: " );
		itoa( corVermelha.b, aux2, 10);
		FINALIZA_SPREF
		
		//Jogabilidade
		strcpy( aux, "\n/Jogabilidade\n" );
		fputs( aux, arquivo );
		strcpy( aux, "Velocidade da Tela: " );
		itoa( velocidadeTela, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Pertimitir andar em Diagonal: " );
		itoa( movDiagonal, aux2, 10);
		FINALIZA_SPREF
		
		//Mapa
		strcpy( aux, "\n/Mapa\n" );
		fputs( aux, arquivo );
		strcpy( aux, "Comprimento do Mapa (Max-100): " );
		itoa( TAM_MAPA_X, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Altura do Mapa (Max-100): " );
		itoa( TAM_MAPA_Y, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Quantidade de Florestas: " );
		itoa( vegetacao[0], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Tamanho das Florestas: " );
		itoa( vegetacao[1], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Variação entre as Florestas: " );
		itoa( vegetacao[2], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Quantidade de Cordilheiras: " );
		itoa( relevo[0], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Tamanho das Cordilheiras: " );
		itoa( relevo[1], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Variação entre as Cordilheiras: " );
		itoa( relevo[2], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Quantidade de Áreas com Neve: " );
		itoa( neve[0], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Tamanho das Áreas com Neve: " );
		itoa( neve[1], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Variação entre as Áreas com Neve: " );
		itoa( neve[2], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Quantidade de Desertos: " );
		itoa( deserto[0], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Tamanho dos Desertos: " );
		itoa( deserto[1], aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Variação entre os Desertos: " );
		itoa( deserto[2], aux2, 10);
		FINALIZA_SPREF
		
		//Jogadores
		strcpy( aux, "\n/Jogadores\n" );
		fputs( aux, arquivo );
		strcpy( aux, "Número de Jogadores: " );
		itoa( numJogadoresUsados, aux2, 10);
		FINALIZA_SPREF
		for( i = 0; i < numJogadoresUsados; i++ )
		{
		strcpy( aux, "Nome do Jogador: " );
		strcat( aux, jogadores[i].nome );
		strcat( aux, "\n" );fputs( aux, arquivo );
		strcpy( aux, "Raca do Jogador: " );
		itoa( jogadores[i].raca, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "População do Jogador: " );
		itoa( jogadores[i].populacao, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Materiais do Jogador: " );
		itoa( jogadores[i].materiaisIni, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Mana do Jogador: " );
		itoa( jogadores[i].manaIni, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Posição X: " );
		itoa( jogadores[i].x, aux2, 10);
		FINALIZA_SPREF
		strcpy( aux, "Posição Y: " );
		itoa( jogadores[i].y, aux2, 10);
		FINALIZA_SPREF
		}
			
		//Rede
		strcpy( aux, "\n/Rede\n" );
		fputs( aux, arquivo );
		strcpy( aux, "IP do servidor: " );
		strcat( aux, ipProcuradoNome );
		strcat( aux, "\n" );fputs( aux, arquivo );
		strcpy( aux, "Porta de Rede: " );
		itoa( PortaRede, aux2, 10);
		FINALIZA_SPREF
		
		fclose(arquivo);
	}
}

//------------------------------------------------------------------------------

int carregar_preferencias()
{
	#define BUSCAR_CPREF while(fgetc(arquivo)=='/'){fgets(texto,50,arquivo);}do{c=fgetc(arquivo);}while(c!=':');fgetc(arquivo);fgets(texto,50,arquivo);
	// #define BUSCAR_CPREF do{c=fgetc(arquivo);}while(c!=':');fgets(texto,50,arquivo);
	
	int i;
	char texto[95];
	FILE *arquivo;
	char c = 'a';
	
	arquivo = fopen( "prefe.txt","r" );
	
	if( arquivo == NULL )
	{
		return 0;
	}
	else
	{
		//escrever( 400, 400, "Carregando Preferências", fonte20, corVermelha );
		//SDL_Flip( tela );
		
		//texto[ strlen( texto ) - 1 ] = '\0'; //Purifica texto
		
		//Vídeo
		BUSCAR_CPREF
		SCREEN_WIDTH = atoi( texto );
		BUSCAR_CPREF
		SCREEN_HEIGHT = atoi( texto );
		BUSCAR_CPREF
		SCREEN_BPP = atoi( texto );
		BUSCAR_CPREF
		telaCheia = atoi( texto );
		BUSCAR_CPREF
		FRAMES_PER_SECOND = atoi( texto );
		BUSCAR_CPREF
		TAM_TELA_X = atoi( texto );
		BUSCAR_CPREF
		TAM_TELA_Y = atoi( texto );
		BUSCAR_CPREF
		textColor.r = atoi( texto );
		BUSCAR_CPREF
		textColor.g = atoi( texto );
		BUSCAR_CPREF
		textColor.b = atoi( texto );
		BUSCAR_CPREF
		corVermelha.r = atoi( texto );
		BUSCAR_CPREF
		corVermelha.g = atoi( texto );
		BUSCAR_CPREF
		corVermelha.b = atoi( texto );
		
		//Jogabilidade
		BUSCAR_CPREF
		velocidadeTela = atoi( texto );
		BUSCAR_CPREF
		movDiagonal = atoi( texto );
		
		//Mapa
		BUSCAR_CPREF
		TAM_MAPA_X = atoi( texto );
		BUSCAR_CPREF
		TAM_MAPA_Y = atoi( texto );
		BUSCAR_CPREF
		vegetacao[0] = atoi( texto );
		BUSCAR_CPREF
		vegetacao[1] = atoi( texto );
		BUSCAR_CPREF
		vegetacao[2] = atoi( texto );
		BUSCAR_CPREF
		relevo[0] = atoi( texto );
		BUSCAR_CPREF
		relevo[1] = atoi( texto );
		BUSCAR_CPREF
		relevo[2] = atoi( texto );
		BUSCAR_CPREF
		neve[0] = atoi( texto );
		BUSCAR_CPREF
		neve[1] = atoi( texto );
		BUSCAR_CPREF
		neve[2] = atoi( texto );
		BUSCAR_CPREF
		deserto[0] = atoi( texto );
		BUSCAR_CPREF
		deserto[1] = atoi( texto );
		BUSCAR_CPREF
		deserto[2] = atoi( texto );
		
		//Jogadores
		BUSCAR_CPREF
		numJogadoresUsados = atoi( texto );
		for( i = 0; i < numJogadoresUsados; i++ )
		{
		BUSCAR_CPREF
		texto[ strlen( texto ) - 1 ] = '\0';
		strcpy( jogadores[i].nome, texto );
		BUSCAR_CPREF
		jogadores[i].raca = atoi( texto );
		BUSCAR_CPREF
		jogadores[i].populacao = atoi( texto );
		BUSCAR_CPREF
		jogadores[i].materiaisIni = atoi( texto );
		BUSCAR_CPREF
		jogadores[i].manaIni = atoi( texto );
		BUSCAR_CPREF
		jogadores[i].x = atoi( texto );
		BUSCAR_CPREF
		jogadores[i].y = atoi( texto );
		}
		
		//Rede
		BUSCAR_CPREF
		texto[ strlen( texto ) - 1 ] = '\0';
		strcpy( ipProcuradoNome, texto );
		BUSCAR_CPREF
		PortaRede = atoi( texto );
		
		fclose(arquivo);
	}
}

