#include "AAA.h"

//------------------------------------------------------------------------------

void passar_turno()
{
	int i = 0;
	int treinando = 0;
	
	calcular_cidades();
	
	//Renovar movimentos
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		unidades[i].movimentos = tipos[unidades[i].tipo].movimento;
	}
	
	for( i = 0; i < numCidades; i++ )
	{
		calcular_cidade( i );
		
		//Recolher materiais
		if( cidades[i].raca >= 0 && cidades[i].emConstr == 0 )
		{
			jogadores[cidades[i].dono].materiais = jogadores[cidades[i].dono].materiais + cidades[i].materiais;
		}
		
		//Aumentar População
		if( cidades[i].emConstr == 0  )
		{
			if( cidades[i].populacao < cidades[i].maxPopulacao && cidades[i].maxPopulacao < (cidades[i].populacao * (100 + cidades[i].crescimento))/100 )
			{
				cidades[i].populacao = cidades[i].maxPopulacao;
			}
			else
			{
				cidades[i].populacao = (cidades[i].populacao * (100 + cidades[i].crescimento))/100;
			}
		}
		
		//Decrescer tempo de construção das cidades
		if( cidades[i].emConstr > 0 )
		{
			cidades[i].emConstr--;
		}
	}
	
	//Aumentar mana
	for( i = 0; i < numJogadoresUsados; i++ )
	{
		jogadores[i].mana += 100;
	}
	
	calcular_cidades();
	
	jogadorAtual = 0;
	turno++;
}

//------------------------------------------------------------------------------

void passar_jogada( int tipo ) //tipo 0: nunca manda o turno     tipo 1: manda o turno caso online
{
	int i = 0;
	int treinando = 0;
	
	if( tipo == 1 && online > 0 )
	{
		novaSaida = 2;
		menu_espera_jogada();
	}
	
	jogadores[jogadorAtual].telaX = telaX;
	jogadores[jogadorAtual].telaY = telaY;
	
	for( i = 0; i < numCidades; i++ )
	{
		//Treinar Pelotões
		if( cidades[i].treinando >= 0 && cidades[i].emConstr == 0 && cidades[i].dono == jogadorAtual )
		{
			cidades[i].completado = cidades[i].completado + cidades[i].treinamento;
			if( cidades[i].completado >= tipos[cidades[i].treinando].treino )
			{
				criar_pelotao( cidades[i].x, cidades[i].y, cidades[i].treinando, cidades[i].dono, cidades[i].treinandoQuant, tipos[cidades[i].treinando].movimento );
				
				cidades[i].populacao = cidades[i].populacao - cidades[i].treinandoQuant;
				
				if( cidades[i].infTreino )
				{
					treinando = cidades[i].treinando;
					cidades[i].treinando = -1;
					mudar_treinando( i, treinando, 1 );
				}
				else
				{
					cidades[i].treinando = -1;
				}
				cidades[i].completado = 0;
				
				if( cidades[i].populacao <= 0 )//Não deixar cidade ficar com 0 de população
				{
					cidades[i].populacao = 0.1;
				}
				/*if( cidades[i].populacao < 1 )//Eliminar cidades vazias
				{
				eliminar_cidade( i );
				}*/
			}
		}
		calcular_cidade( i );
	}
	
	jogadorAtual++;
	if( jogadorAtual == numJogadoresUsados )
	{
		passar_turno();
	}
	
	preencher_fundo();
	strcpy( aux, "É a vez de " );
	strcat( aux, jogadores[jogadorAtual].nome );
	escrever( 400, 400, aux, fonte20, corVermelha );
	SDL_Flip( tela );
	SDL_Delay( 1000 );
	telaX = jogadores[jogadorAtual].telaX;
	telaY = jogadores[jogadorAtual].telaY;
	
	selecaoX = -1;
	selecaoY = -1;
	selecaoC = -1;
	selecaoP = -1;
	for( i = 0; i < 6; i++ )
	{
		selecaoPs[i] = -1;
	}
}

//------------------------------------------------------------------------------

int tela_mapa()
{
	int x = 0;
	int y = 0;
	int i = 0;
	
	//magias_efeitos_terreno( int x, int y, int tipo, int intensidade, int area, int homogenio = 0 )
	//magias_efeitos_terreno( 10, 10, 3, -6, 10, 0 );
	
	//magias_efeitos_dano( 0, 0, 100, 100, 1, 4, 1, 0 );
	
	//ordenar_tipos();
	
	calcular_tipos();
	
	var = 0;
	while( var == 0 )
	{
		while( SDL_PollEvent( &evento ) )
		{
			if( evento.type == SDL_QUIT )
			{
				var = -1;
			}
		
			if( evento.type == SDL_MOUSEBUTTONUP )
			{
				selecionar_terr();
				
				//Ver informações da cidade
				if( botao( 750+105, 20+20, 0, 1 ) && selecaoC >= 0 && jogadorAtual == cidades[selecaoC].dono )
				{
					var = 1;
				}
				
				//Ver informações do pelotão
				i = 0;
				while( i < 6 && selecaoPs[i] >= 0 )
				{
					if( botao( 750+220, 170+i*90+40, 1, 1 ) && jogadorAtual == unidades[selecaoPs[i]].dono )
					{
						selecaoP = selecaoPs[i];
						var = 2;
					}
					i++;
				}
				
				//Selecionar outro pelotão da lista de pelotões da posição selecionada
				i = 0;
				while( i < 6 && selecaoPs[i] >= 0 )
				{
					if( botao( 750, 170+i*90, 3, 1 ) )
					{
						selecaoP = selecaoPs[i];
					}
					i++;
				}
				
				//Editor de tipos
				if( botao( 680, 724, 11, 1 ) )
				{
					var = 3;
				}
				
				//Ativar / Desativar ícones
				if( botao( 500, 734, 25, 1 ) )
				{
					if( infoUnits )
					{
						infoUnits = 0;
						infoCores = 0;
					}
					else
					{
						infoUnits = 1;
						infoCores = 1;
					}
				}
				
				//Passar jogada
				if( botao( 4, 724, 6, 1 ) )
				{
					passar_jogada( 1 );
				}
			}
			
			if( evento.type == SDL_KEYDOWN )
			{
				if( selecaoP >= 0 && unidades[selecaoP].movimentos > 0 && jogadorAtual == unidades[selecaoP].dono )
				{
					mover_pelotao();
				}
				
				atalhos( 1 );
			}
		}
		
		Uint8 *keystates = SDL_GetKeyState( NULL );
		if( keystates[ SDLK_UP ] && telaY > 0 )
		telaY = telaY - velocidadeTela;
		if( keystates[ SDLK_DOWN ] && telaY < TAM_MAPA_Y * 70 - TAM_TELA_Y )
		telaY = telaY + velocidadeTela;
		if( keystates[ SDLK_LEFT ] && telaX > 0 )
		telaX = telaX - velocidadeTela;
		if( keystates[ SDLK_RIGHT ] && telaX < TAM_MAPA_X * 70 - TAM_TELA_X )
		telaX = telaX + velocidadeTela;
		
		if( telaY > TAM_MAPA_Y * 70 - TAM_TELA_Y )
		telaY = TAM_MAPA_Y * 70 - TAM_TELA_Y;        
		if( telaX > TAM_MAPA_X * 70 - TAM_TELA_X )
		telaX = TAM_MAPA_X * 70 - TAM_TELA_X;
		if( telaY < 0 )
		telaY = 0;      
		if( telaX < 0 )
		telaX = 0;
		
		desenhar_mapa();
		desenhar_cidades();
		desenhar_pelotoes();
		desenhar_selecao();
		desenhar_bordas();
		desenhar_infos_terr( 320, 725, selecaoX, selecaoY );
		desenhar_infos_jogador( 150, 725, jogadores[jogadorAtual] );
		botao( 4, 724, 6, 0 );//Apulheta
		botao( 680, 724, 11, 0 );//Editor de Tipos
		if( infoUnits )
		{
		botao( 500, 734, 25, 0 );//Interrogação
		}
		else
		{
		botao( 500, 734, 26, 0 );//Interrogação com X
		}
		
		strcpy( aux, "Turno: " );
		itoa( turno, aux2, 10);
		strcat( aux, aux2);
		escrever( 50, 735, aux );
		
		if( selecaoC >= 0 )
		{
		desenhar_infos_cid( cidades[selecaoC] );
		}
		
		i = 0;
		while( i < 6 && selecaoPs[i] >= 0 )
		{ 
		desenhar_infos_unit( 750, 170+90*i, selecaoPs[i] );
		if( selecaoP == selecaoPs[i] )
		{
			aplicar_superficie( 750+5, 170+5+i*90, bordasImagem, tela, &bordasI[23] );
		}
		i++;
		}
		
		
		
		/*if( Mix_PlayingMusic() == 0 ) 
		{ 
		//Play the music 
		if( Mix_PlayMusic( click, -1 ) == -1 ) 
		{ return 1; } 
		}*/
		/*if( Mix_PlayChannel( -1, scratch, 0 ) == -1 ) { return 1; }
		//Resume the music
		if( Mix_PausedMusic() == 1 ) {  Mix_ResumeMusic(); }
		//If the music is playing 
		//Pause the music
		else { Mix_PauseMusic(); }
		Mix_HaltMusic();*/
		
		
		
		
		
		
		
		if( SDL_Flip( tela ) == -1 )
		{
		return 1;    
		}
		controlar_frame();
	}
}

//------------------------------------------------------------------------------

int jogo()
{
	while( var != -1 && var != -3 )
	{
		tela_mapa();
		if( var == 1 )
		{
			dados_cidade( selecaoC );
		}
		else if( var == 2 )
		{
			dados_unidade( selecaoP );
		}
		else if( var == 3 )
		{
			while( var != -2 && var != -1 )
			{
				editor_tipos();
				/*if( var == 1 )
				{
					editor_bonus( editando );
					if( var == -2 )
					{
					var = 0;
					}
				}*/
			}
		}
		else if( var == -2 )
		{
			menu_no_jogo();
		}
		
		if( var == 4 )
		{
			menu_magias( racas[tipos[unidades[selecaoP].tipo].raca].elemento, selecaoP );
		}
	}
}
