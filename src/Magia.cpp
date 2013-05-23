#include "AAA.h"

/*
Elementos:
          0 - Ar
          1 - Terra
          2 - Água
          3 - Fogo
          4 - Natureza
*/

//------------------------------------------------------------------------------

int tela_alvo_magia( int tipo, int nUnit, int distMax )
{
	/*
	tipo (possiveis alvos)
	1 - Jogador
	2 - Terreno
	3 - Unidade ou Cidade
	*/
	
	int x = 0;
	int y = 0;
	int i = 0;
	int incr = 20;
	int dist = -1;
	
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
				
				dist = distancia( unidades[nUnit].x, unidades[nUnit].y, selecaoX, selecaoY );
				
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
		
				//Magia
				if( botao( 940, 724, 18, 1 ) )
				{
					if( distMax >= dist || distMax == -1 )
					{
			
						if( jogAlvoMagia >= 0 && tipo == 1 )//Jogador
						{
							var = 1;
						}
						else if( selecaoX >= 0 && selecaoY >= 0 && tipo == 2 )//Terreno
						{
							var = 1;
						}
						else if( (selecaoP >= 0 || selecaoC >= 0) && tipo == 3 )//Unidade ou Cidade
						{
							var = 1;
						}
					}
				}
				//Voltar
				if( botao( 980, 724, 7, 5 ) )
				{
					var = -2;
				}
			}
		
			if( evento.type == SDL_KEYDOWN )
			{
				atalhos( 12 );
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
		
		x = 25;
		y = 25;
		strcpy( aux, "Escolha o alvo da magia" );
		escrever( x, y, aux, fonte20, corVermelha );
		x = 25;
		y = 50;
		i = 0;
		if( selecaoX >= 0 && selecaoY >= 0 )
		{
			strcpy( aux, "Posição Atual ( " );
			itoa( selecaoX, aux2, 10 );
			strcat( aux, aux2 );
			strcat( aux, " , " );
			itoa( selecaoY, aux2, 10 );
			strcat( aux, aux2 );
			strcat( aux, " )" );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		i++;
		if( dist >= 0 )
		{
			strcpy( aux, "Distância: " );
			itoa( dist, aux2, 10 );
			strcat( aux, aux2 );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		i++;
		if( distMax == -1 )
		{
			strcpy( aux, "Distância Máxima: " );
			strcat( aux, "Livre" );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		else
		{
			strcpy( aux, "Distância Máxima: " );
			itoa( distMax, aux2, 10 );
			strcat( aux, aux2 );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		i++;
		jogAlvoMagia = -1;
		if( selecaoP >= 0 )
		{
			jogAlvoMagia = unidades[selecaoP].dono;
			strcpy( aux, "Jogador: " );
			strcat( aux, jogadores[unidades[selecaoP].dono].nome );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		else if( selecaoC >= 0 )
		{
			jogAlvoMagia = cidades[selecaoC].dono;
			strcpy( aux, "Jogador: " );
			strcat( aux, jogadores[cidades[selecaoC].dono].nome );
			escrever( x, y +i*incr, aux, fonte16, corVermelha );
		}
		
		botao( 940, 724, 18, 0 );//Magia 
		botao( 980, 724, 7, 0 );//X vermelho
		
		if( SDL_Flip( tela ) == -1 )
		{
			return 1;
		}
		controlar_frame();
	}
	
	if( var == -2 )
	{
		return -1;
	}
	
	if( var == 1 )
	{
		return dist;
	}
}

//------------------------------------------------------------------------------

int magias_efeitos_terreno( int x, int y, int tipo, int intensidade, int area, int homogeneo )
{
	int i;
	int j;
	int modif;
	
	for( i = -area; i <= area; i++ )
	{
		for( j = -area; j <= area; j++ )
		{
			if( x + i >= 0 && x + i < TAM_MAPA_X && y + j >= 0 && y + j < TAM_MAPA_Y )
			{
				if( intensidade > 0 )//Efeito positivo
				{
					if( intensidade >= distancia( x+i,y+j , x,y ) )
					{
						modif = intensidade - distancia( x+i,y+j , x,y );
					}
					else //Caso longe demais para ter efeito
					{
						modif = 0;
					}
				}
				else //Efeito negativo
				{
					if( intensidade*-1 >= distancia( x+i,y+j , x,y ) )
					{
						modif = intensidade + distancia( x+i,y+j , x,y );
					}
					else //Caso longe demais para ter efeito
					{
						modif = 0;
					}
				}
			
				if( homogeneo == 1 )
				{
					modif = intensidade;
				}
			
				if( tipo == 1 ) //Montanhas
				{
					mapa[x + i][y + j].relevo += modif;
				}
				else if( tipo == 2 ) //Neve
				{
					mapa[x + i][y + j].temperatura -= modif;
				}
				else if( tipo == 3 ) //Deserto
				{
					mapa[x + i][y + j].temperatura += modif;
				}
				else if( tipo == 4 ) //Floresta
				{
					mapa[x + i][y + j].vegetacao += modif;
				}
				else if( tipo == 5 ) //Temperatura Media
				{
					if( mapa[x + i][y + j].temperatura < 4 )
					{
						mapa[x + i][y + j].temperatura += modif;
						if( mapa[x + i][y + j].temperatura > 4 )mapa[x + i][y + j].temperatura = 4;
					}
					else if( mapa[x + i][y + j].temperatura > 4 )
					{
						mapa[x + i][y + j].temperatura -= modif;
						if( mapa[x + i][y + j].temperatura < 4 )mapa[x + i][y + j].temperatura = 4;
					}
				}
				if( mapa[x + i][y + j].temperatura < 0 )mapa[x + i][y + j].temperatura = 0;
				if( mapa[x + i][y + j].temperatura > 8 )mapa[x + i][y + j].temperatura = 8;
				if( mapa[x + i][y + j].vegetacao < 0 )mapa[x + i][y + j].vegetacao = 0;
				if( mapa[x + i][y + j].vegetacao > 6 )mapa[x + i][y + j].vegetacao = 6;
				if( mapa[x + i][y + j].relevo < 0 )mapa[x + i][y + j].relevo = 0;
				if( mapa[x + i][y + j].relevo > 3 )mapa[x + i][y + j].relevo = 3;
			}
		}
	}
}

//------------------------------------------------------------------------------

int magias_efeitos_teleporte( int x, int y, int nUnit, int tipo, int area )
{
	/*
	Tipo
	0 - Só nUnit
	1 - Todos na posição de nUnit
	*/
	
	int x0 = 0;
	int y0 = 0;
	int cont = 0;
	int xAnt;
	int yAnt;
	
	if( area > 0 )
	{
		do
		{
			do
			{
				x0 = ( rand() % ( area + 1 ) ) - ( rand() % ( area + 1 ) ); // <- CORRIGIR
			}
			while( (x + x0 < 0) || (x + x0 >= TAM_MAPA_X) );
			
			do
			{
				y0 = ( rand() % ( area + 1 ) ) - ( rand() % ( area + 1 ) ); // <- CORRIGIR
			}
			while( (y + y0 < 0) || (y + y0 >= TAM_MAPA_Y) );
		
			procurar_pelotoes_xy( x+x0, y+y0 );
			
			cont++;
			if( cont == 1000 )
			{
				/*preencher_fundo();
				escrever( 400, 400, "FIM", fonte20, corVermelha );
				itoa( x+x0, aux, 10);
				strcat( aux, " , " );
				itoa( y+y0, aux2, 10);
				strcat( aux, aux2 );
				strcat( aux, " P= " );
				itoa( selecaoP, aux2, 10);
				strcat( aux, aux2 );
				escrever( 400, 500, aux, fonte20, corVermelha );
				SDL_Flip( tela );
				SDL_Delay( 1000 );*/
				//exit(0);
				return 0; //Não achou posição válida
			}
			
		}
		while( selecaoP != -1 && ( unidades[selecaoP].dono != unidades[nUnit].dono ) );
	}
	
	if( tipo == 0 )
	{
		unidades[nUnit].x = x + x0;
		unidades[nUnit].y = y + y0;
	}
	else if( tipo == 1 )
	{
		xAnt = unidades[nUnit].x;
		yAnt = unidades[nUnit].y;
		
		procurar_pelotoes_xy( xAnt, yAnt );
		
		while( selecaoP != -1 )
		{
			unidades[selecaoP].x = x + x0;
			unidades[selecaoP].y = y + y0;
			procurar_pelotoes_xy( xAnt, yAnt );
		}
	}
}

//------------------------------------------------------------------------------

void magias_efeitos_materiais( int jogador, int intensidade, float roubo, int jogFeiticeiro )
{
	int matRoubo = -1*intensidade;
	
	if( intensidade > 0 )//Caso o efeito positivo
	{
		jogadores[jogador].materiais += intensidade;
	}
	else
	{
		if( jogadores[jogador].materiais >= (-1*intensidade) ) //Caso negativo mas restaram materiais
		{
			jogadores[jogador].materiais += intensidade;
		}
		else //Caso não não restarão materiais
		{
			matRoubo = jogadores[jogador].materiais;
			jogadores[jogador].materiais = 0;
		}
		
		if( jogFeiticeiro >= 0 )//Caso seja para roubar parte dos materiais
		{
			jogadores[jogFeiticeiro].materiais += (int)(roubo * matRoubo);
		}
	}
}

//------------------------------------------------------------------------------

void magias_efeitos_dano( int x, int y, int intensidade, int area, int modo, int elemento, int unicid, int homogeneo )
{
	/*
	modo ( Calculo de efeito ):
	0 - Porcentagem
	1 - Número absoluto
	2 - Proporcional a vida  -> *NÃO IMPLEMENTADO!!!!!!!*
	
	elemento ( 5 - neutro )
	
	unicid ( Possiveis alvos ):
	0 - Tanto Unidades como Cidades
	1 - Unidades
	2 - Cidades
	*/
	
	int i;
	int j;
	int f;
	int inten;
	int cid = -1;
	int modif;
	long int quant;
	long int alvo;
	
	for( i = 0; i < numPs; i++ )
	{
		selecaoPs[i] = -1;
	}
	
	for( i = -area; i <= area; i++ )
	{
		for( j = -area; j <= area; j++ )
		{
		if( x + i >= 0 && x + i < TAM_MAPA_X &&\
			y + j >= 0 && y + j < TAM_MAPA_Y )
		{
	
			modif = intensidade / ( distancia( x+i,y+j , x,y ) + 1 ) ;
	
			if( homogeneo == 1 )
			{
			modif = intensidade;
			}
	
			if( unicid == 0 || unicid == 1 )
			{
			procurar_pelotoes_xy( x + i, y + j );
			}
			if( unicid == 0 || unicid == 2 )
			{
			cid = procurar_cid_xy( x + i, y + j );
			}
	
			//EFEITO
			//Por porcentagem
			if( modo == 0 )
			{
			if( unicid == 0 || unicid == 1 )
			{
				for( f = 0; f < numPs; f ++ )
				{
				if( selecaoPs[f] >= 0 && racas[tipos[unidades[selecaoPs[f]].tipo].raca].elemento != elemento )//Verifica elemento
				{
					unidades[selecaoPs[f]].quantidade -= (unidades[selecaoPs[f]].quantidade * modif)/100;
	
					if( unidades[selecaoPs[f]].quantidade <= 0 )
					{
						eliminar_pelotao( selecaoPs[f] );
					}
				}
				}
			}
	
			if( unicid == 0 || unicid == 2 )
			{
				if( cid >= 0 && racas[cidades[cid].raca].elemento != elemento )//Verifica elemento
				{
					cidades[cid].populacao -= (cidades[cid].populacao * modif)/100;
	
					if( cidades[cid].populacao <= 0 )
					{
						cidades[cid].populacao = 0.1;
					}
				}
			}
	
			}
			//Por número absoluto
			else if( modo == 1 )
			{
				for( inten = 0; inten < modif; inten++  )
				{
					//Calcula a quantidade total de seres e guarda em "quant"
					quant = 0;
					if( unicid == 0 || unicid == 1 )
					{
						for( f = 0; f < numPs; f ++ )
						{
							if( selecaoPs[f] >= 0 && racas[tipos[unidades[selecaoPs[f]].tipo].raca].elemento != elemento )//Verifica elemento
							{
								quant += unidades[selecaoPs[f]].quantidade;
							}
						}
					}
					if( unicid == 0 || unicid == 2 )
					{
						if( cid >= 0 && racas[cidades[cid].raca].elemento != elemento )//Verifica elemento
						{
							quant += (int)cidades[cid].populacao;
						}
					}
		
					if( quant > 0 )//Sorteia o morto da vez
					{
						alvo = (rand()*rand())%quant;
					}
		
					if( unicid == 0 || unicid == 1 )
					{
						for( f = 0; f < numPs; f ++ )
						{
							if( selecaoPs[f] >= 0 && racas[tipos[unidades[selecaoPs[f]].tipo].raca].elemento != elemento )//Verifica elemento
							{
								quant -= unidades[selecaoPs[f]].quantidade;
			
								if( quant <= alvo && alvo != -1 )
								{
									unidades[selecaoPs[f]].quantidade--;
									alvo = -1;
									if( unidades[selecaoPs[f]].quantidade <= 0 )
									{
										eliminar_pelotao( selecaoPs[f] );
									}
								}
							}
						}
					}
					if( unicid == 0 || unicid == 2 )
					{
						if( cid >= 0 && racas[cidades[cid].raca].elemento != elemento )//Verifica elemento
						{
							quant -= (int)cidades[cid].populacao;
							if( quant <= alvo && alvo != -1 )
							{
								cidades[cid].populacao--;
								alvo = -1;
							}
						}
					}
				}
			}
			//Relacionado a pontos de vida
			else if( modo == 2 )
			{
			}
		}
		}
	}
	
	for( i = 0; i < numPs; i++ )
	{
		selecaoPs[i] = -1;
	}
	selecaoP = -1;
	selecaoC = -1;
}

//------------------------------------------------------------------------------

void preparar_magias()
{
	int i;
	
	for( i = 0; i < numMagias; i++ )
	{
		strcpy(magias[i].nome," ");
		magias[i].id = -1;
		magias[i].elemento = -1;
		magias[i].mana = 0;
		magias[i].alcance = -1;
		magias[i].nivel = -1;
	}
	
	//AR
	i = 0;
	strcpy(magias[i].nome,"Roubar Materias");
	magias[i].id = i;
	magias[i].elemento = 0;
	magias[i].mana = 50;
	magias[i].alcance = -1;
	magias[i].nivel = 3;
	i = 1;
	strcpy(magias[i].nome,"Tempestade de Raios Bola");
	magias[i].id = i;
	magias[i].elemento = 0;
	magias[i].mana = 500;
	magias[i].alcance = -1;
	magias[i].nivel = 5;
	i = 2;
	strcpy(magias[i].nome,"Vento Carregador");
	magias[i].id = i;
	magias[i].elemento = 0;
	magias[i].mana = 100;
	magias[i].alcance = 10;
	magias[i].nivel = 3;
	i = 3;
	strcpy(magias[i].nome,"Tornado");
	magias[i].id = i;
	magias[i].elemento = 0;
	magias[i].mana = 150;
	magias[i].alcance = 8;
	magias[i].nivel = 4;
	
	//TERRA
	i = 100;
	strcpy(magias[i].nome,"Tectonismo Global");
	magias[i].id = i;
	magias[i].elemento = 1;
	magias[i].mana = 1000;
	magias[i].alcance = -1;
	magias[i].nivel = 5;
	i = 101;
	strcpy(magias[i].nome,"Criar Materiais");
	magias[i].id = i;
	magias[i].elemento = 1;
	magias[i].mana = 20;
	magias[i].alcance = -1;
	magias[i].nivel = 2;
	i = 102;
	strcpy(magias[i].nome,"Montanha Subta");
	magias[i].id = i;
	magias[i].elemento = 1;
	magias[i].mana = 100;
	magias[i].alcance = 4;
	magias[i].nivel = 3;
	
	//GELO
	i = 200;
	strcpy(magias[i].nome,"Era Glacial");
	magias[i].id = i;
	magias[i].elemento = 2;
	magias[i].mana = 200;
	magias[i].alcance = -1;
	magias[i].nivel = 5;
	i = 201;
	strcpy(magias[i].nome,"Enxurrada");
	magias[i].id = i;
	magias[i].elemento = 2;
	magias[i].mana = 100;
	magias[i].alcance = 3;
	magias[i].nivel = 2;
	
	//FOGO
	i = 300;
	strcpy(magias[i].nome,"Esquentar Solo");
	magias[i].id = i;
	magias[i].elemento = 3;
	magias[i].mana = 20;
	magias[i].alcance = 0;
	magias[i].nivel = 2;
	i = 301;
	strcpy(magias[i].nome,"Efeito Estufa");
	magias[i].id = i;
	magias[i].elemento = 3;
	magias[i].mana = 200;
	magias[i].alcance = -1;
	magias[i].nivel = 5;
	i = 302;
	strcpy(magias[i].nome,"Raio de Fogo");
	magias[i].id = i;
	magias[i].elemento = 3;
	magias[i].mana = 50;
	magias[i].alcance = -1;
	magias[i].nivel = 4;
	
	//NATUREZA
	i = 400;
	strcpy(magias[i].nome,"Florestar");
	magias[i].id = i;
	magias[i].elemento = 4;
	magias[i].mana = 10;
	magias[i].alcance = 0;
	magias[i].nivel = 1;
	i = 401;
	strcpy(magias[i].nome,"Clima Ameno");
	magias[i].id = i;
	magias[i].elemento = 4;
	magias[i].mana = 20;
	magias[i].alcance = 0;
	magias[i].nivel = 2;
	i = 402;
	strcpy(magias[i].nome,"Mundo Verde");
	magias[i].id = i;
	magias[i].elemento = 4;
	magias[i].mana = 200;
	magias[i].alcance = -1;
	magias[i].nivel = 5;
}

//------------------------------------------------------------------------------

int magias_efeitos( int id, int nUnit )
{
	int xU = unidades[selecaoP].x;
	int yU = unidades[selecaoP].y;
	
	//&& unidades[nUnit].nivelMagico >= magias[id].nivel\
	
	if( id == 0 )//Roubar Materiais
	{
		//Requisitos
		if( tela_alvo_magia( 1, nUnit )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_materiais( jogAlvoMagia, -1000, 0.5, unidades[nUnit].dono );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 1 )//Tempestade de Raios Bola
	{
		//Requisitos
		if( tela_alvo_magia( 2, nUnit )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_dano( selecaoX, selecaoY, 100, 0, 0, 0 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 2 )//Vento Carregador
	{
		//Requisitos
		if( tela_alvo_magia( 2, nUnit, magias[id].alcance )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_teleporte( selecaoX, selecaoY, nUnit, 0, 0 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 3 )//Tornado
	{
		//Requisitos
		if( tela_alvo_magia( 2, nUnit, magias[id].alcance )\
				  && tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
				  && jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		  )
		
		//Efeito
		{
		if( selecaoP >= 0 )magias_efeitos_teleporte( selecaoX, selecaoY, selecaoP, 1, 2 );
		magias_efeitos_terreno( selecaoX, selecaoY, 5, -1, 0, 1 );
		magias_efeitos_dano( selecaoX, selecaoY, 10, 0, 0, 0 );
		
		//Custo
			jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 100 )//Tectonismo Global
	{
		//Requisitos
		if( tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 1, 1, 100, 1 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 101 )//Criar Materiais
	{
		//Requisitos
		if( tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_materiais( unidades[nUnit].dono, 500 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 102 )//Montanha Subta
	{
		//Requisitos
		if( tela_alvo_magia( 2, nUnit, magias[id].alcance )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( selecaoX, selecaoY, 1, 3, 0, 1 );
		magias_efeitos_dano( selecaoX, selecaoY, 10, 0, 0, 1 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 200 )//Era Glacial
	{
		//Requisitos
		if( tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 2, 1, 100, 1 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 201 )//Enxurrada
	{
		//Requisitos
		if( tela_alvo_magia( 2, nUnit, magias[id].alcance )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_dano( selecaoX, selecaoY, 10, 0, 0, 2 );
		magias_efeitos_teleporte( selecaoX, selecaoY, selecaoP, 1, 2 );
	
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 300 )//Esquentar Solo
	{
		//Requisitos
		if( mapa[xU][yU].temperatura < 8 \
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 3, 2, 1, 0 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 301 )//Efeito Estufa
	{
		//Requisitos
		if( tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 3, 1, 100, 1 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 302 )//Raio de Fogo
	{
		//Requisitos
		if( tela_alvo_magia( 3, nUnit, magias[id].alcance )\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_dano( selecaoX, selecaoY, 1, 0, 1, 3 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 400 )//Florestar
	{
		//Requisitos
		if( mapa[xU][yU].vegetacao < 6\
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
		
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 4, 1, 1, 0 );
		
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 401 )//Clima Ameno
	{
		//Requisitos
		if( mapa[xU][yU].temperatura != 4 \
		&& tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
	
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 5, 2, 1, 0 );
	
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
	else if( id == 402 )//Mundo Verde
	{
		//Requisitos
		if( tipos[unidades[nUnit].tipo].nivelMagico >= magias[id].nivel\
		&& jogadores[jogadorAtual].mana >= magias[id].mana && unidades[nUnit].movimentos > 0\
		)
	
		//Efeito
		{
		magias_efeitos_terreno( unidades[nUnit].x, unidades[nUnit].y, 4, 1, 100, 1 );
	
		//Custo
		jogadores[jogadorAtual].mana -= magias[id].mana;unidades[nUnit].movimentos = 0;
		}
	}
}

//------------------------------------------------------------------------------

int procurar_magia( int elemento, int nivel, int idAtual )
{
	int i;
	
	for( i = 0; i < numMagias; i++ )
	{
		if( magias[i].elemento == elemento && magias[i].nivel == nivel && i > idAtual )
		{
			return i;
		}
	}
	
	return -1;
}

//------------------------------------------------------------------------------

void preparar_lista_magias( int elemento )
{
	int i;
	int nivel;
	
	for( nivel = 0; nivel < 5; nivel++ )
	{
		for( i = 0; i < 3; i++ )
		{
		listaMagias[i][nivel] = -1;
		}
	}
	
	for( nivel = 0; nivel < 5; nivel++ )
	{
		i = 0;
		listaMagias[i][nivel] = procurar_magia( elemento, nivel+1, -1 );
		for( i = 1; i < 3 && listaMagias[i-1][nivel] >= 0; i++ )
		{
			listaMagias[i][nivel] = procurar_magia( elemento, nivel+1, listaMagias[i-1][nivel] );
		}
	}
}

//------------------------------------------------------------------------------

void desenhar_lista_magias( int x, int y, int elemento )
{
	int i;
	int nivel;
	
	for( nivel = 0; nivel < 5; nivel++ )
	{
		strcpy( aux, "Nível: " );
		itoa( nivel+1, aux2, 10);
		strcat( aux, aux2);
		escrever( x-60, y+30+nivel*90, aux );
	
		for( i = 0; i < 3; i++ )
		{
			if( listaMagias[i][nivel] >= 0 )
			{
				aplicar_superficie( x+i*300, y+nivel*90, bordasImagem, tela, &bordasI[10] );
				botao( x+5+i*300, y+5+nivel*90, 2, 0 );
				strcpy( aux, "Nome: " );
				strcat( aux, magias[listaMagias[i][nivel]].nome );
				escrever( x+85+i*300, y+nivel*90, aux );
				strcpy( aux, "Mana: " );
				itoa( magias[listaMagias[i][nivel]].mana, aux2, 10);
				strcat( aux, aux2);
				escrever( x+85+i*300, y+15+nivel*90, aux );
			}
	
			/*strcpy( aux, "         Pos:" );
			itoa( listaMagias[i][nivel], aux2, 10);
			strcat( aux, aux2);
			escrever( x+85+i*300, y+15+nivel*90, aux );*/
	
		}
	}
}

//------------------------------------------------------------------------------

int menu_magias( int elemento, int nUnit )
{
	int i;
	int nivel;
	int x = 0;
	int y = 0;
	
	preparar_lista_magias( elemento );
	
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
		
				for( nivel = 0; nivel < 5; nivel++ )
				{
					for( i = 0; i < 3; i++ )
					{
						if( listaMagias[i][nivel] >= 0 )
						{
							if( botao( 100+5+i*300, 100+5+nivel*90, 2, 1 ) )
							{
								var = -2;
								magias_efeitos( listaMagias[i][nivel], nUnit );
							}
						}
					}
				}
			
				//Voltar
				if( botao( 980, 724, 7, 5 ) ){var = -2;}
			}
			
			if( evento.type == SDL_KEYDOWN )
			{
				atalhos( 9 );
			}
		}
		
		preencher_fundo();
		
		desenhar_lista_magias( 100, 100, elemento );
		
		botao( 980, 724, 7, 0 );//X vermelho
		
		if( SDL_Flip( tela ) == -1 )
		{
			return 1;
		}
		controlar_frame();
	}
}

//------------------------------------------------------------------------------
