#include "AAA.h"

void preparar_matriz_unidadesI()
{
	int i=0;
	
	//Orc
	unidadesI[ i ].x = 0;
	unidadesI[ i ].y = 0;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
	//Elfo
	unidadesI[ i ].x = 70;
	unidadesI[ i ].y = 0;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
	//Esqueleto
	unidadesI[ i ].x = 0;
	unidadesI[ i ].y = 70;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
	//Humano
	unidadesI[ i ].x = 70;
	unidadesI[ i ].y = 70;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
	//Formiga
	unidadesI[ i ].x = 140;
	unidadesI[ i ].y = 0;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
	//Anão
	unidadesI[ i ].x = 140;
	unidadesI[ i ].y = 70;
	unidadesI[ i ].w = 70;
	unidadesI[ i ].h = 70;
	i++;
}

//------------------------------------------------------------------------------

void preparar_pelotoes()
{
	int i;
	
	for( i = 0; i < numPelotoes; i++ )
	{
		eliminar_pelotao( i, 0 );
	}
/*	
	strcpy(unidades[0].nome,"Os Peludos");
	unidades[0].quantidade = 400;
	unidades[0].movimentos = tipos[0].movimento;
	unidades[0].dono = 0;
	unidades[0].tipo = 0;
	unidades[0].x = 3;
	unidades[0].y = 3;
	
	strcpy(unidades[1].nome,"Baitola men");
	unidades[1].quantidade = 2000;
	unidades[1].movimentos = tipos[1].movimento;
	unidades[1].dono = 1;
	unidades[1].tipo = 1;
	unidades[1].x = 4;
	unidades[1].y = 4;
	
	strcpy(unidades[2].nome,"Bones");
	unidades[2].quantidade = 100;
	unidades[2].movimentos = tipos[2].movimento;
	unidades[2].dono = 0;
	unidades[2].tipo = 2;
	unidades[2].x = 0;
	unidades[2].y = 0;
	
	strcpy(unidades[3].nome,"Urio");
	unidades[3].quantidade = 1;
	unidades[3].movimentos = tipos[3].movimento;
	unidades[3].dono = 0;
	unidades[3].tipo = 4;
	unidades[3].x = 2;
	unidades[3].y = 5;
	
	strcpy(unidades[4].nome,"Blamir");
	unidades[4].quantidade = 1;
	unidades[4].movimentos = tipos[4].movimento;
	unidades[4].dono = 0;
	unidades[4].tipo = 3;
	unidades[4].x = 7;
	unidades[4].y = 3;
*/
}

//------------------------------------------------------------------------------

void desenhar_pelotao( int x, int y, int nTipo, int nUnit )
{
	/*if( tipos[nTipo].raca == 0 )
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[0] );
	if( tipos[nTipo].raca == 1 )
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[1] );
	if( tipos[nTipo].raca == 2 )
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[2] );
	if( tipos[nTipo].raca == 3 )
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[3] );
	if( tipos[nTipo].raca == 4 )
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[4] );*/
	
	aplicar_superficie( x, y, unidadesImagem, tela, &unidadesI[tipos[nTipo].raca] );
	
	//Ícones
	if( tipos[nTipo].lanca > 0 && infoUnits )
	aplicar_superficie( x+4, y+4, bordasImagem, tela, &bordasI[12] );
	if( tipos[nTipo].arco > 0 && infoUnits )
	aplicar_superficie( x+2, y+27, bordasImagem, tela, &bordasI[13] );
	if( tipos[nTipo].montaria > 0 && infoUnits )
	aplicar_superficie( x+3, y+52, bordasImagem, tela, &bordasI[14] );
	
	if( nUnit >= 0 )
	{
		if( unidades[nUnit].movimentos > 0 && infoUnits )
		aplicar_superficie( x+59, y+59, bordasImagem, tela, &bordasI[18] );
		
		if( jogadores[unidades[nUnit].dono].cor == 0 && infoCores )
		aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[19] );
		if( jogadores[unidades[nUnit].dono].cor == 1 && infoCores )
		aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[20] );
		if( jogadores[unidades[nUnit].dono].cor == 2 && infoCores )
		aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[21] );
		if( jogadores[unidades[nUnit].dono].cor == 3 && infoCores )
		aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[22] );
	}
}

//------------------------------------------------------------------------------

void desenhar_pelotoes()
{
	int i = 0;
	
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		if( (unidades[i].x)*70 + 70 - telaX > 0 && (unidades[i].x)*70 - telaX - TAM_TELA_X < 0 &&\
		(unidades[i].y)*70 + 70 - telaY > 0 && (unidades[i].y)*70 - telaY - TAM_TELA_Y < 0 )
		{
			desenhar_pelotao( unidades[i].x*70-telaX+POS_TELA_X, unidades[i].y*70-telaY+POS_TELA_Y, unidades[i].tipo, i );
		}
	}
}

//------------------------------------------------------------------------------

void desenhar_selecao()
{
	if( selecaoX >= 0 && selecaoY >= 0 )
	{
		if( selecaoX*70 + 70 - telaX > 0 && selecaoX*70 - telaX - TAM_TELA_X < 0 &&\
		selecaoY*70 + 70 - telaY > 0 && selecaoY*70 - telaY - TAM_TELA_Y < 0 )
		{
			aplicar_superficie( selecaoX * 70 - telaX + POS_TELA_X, selecaoY * 70 - telaY + POS_TELA_Y, bordasImagem, tela, &bordasI[23] );
		}
	}
}

//------------------------------------------------------------------------------

void procurar_pelotoes_xy( int x, int y )
{
	int i;
	int cont = 0;
	
	selecaoP = -1;
	
	for( i = 0; i < numPs; i++ )
	{
		selecaoPs[i] = -1;
	}
	
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		if( unidades[i].x == x && unidades[i].y == y )
		{
			selecaoP = i;
			selecaoPs[cont] = i;
			cont++;
		}
	}
}

//------------------------------------------------------------------------------

int procurar_pelotoes_para_juntar( int x, int y, int nTipo, int dono, int nUnit )
{
	int i;
	int escolhido = -1;
	int quant = 0;
	
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		if( unidades[i].x == x && unidades[i].y == y && unidades[i].tipo == nTipo &&\
		unidades[i].dono == dono && unidades[i].quantidade > quant && i != nUnit )
		{
			quant = unidades[i].quantidade;
			escolhido = i;
		}
	}
	
	return escolhido;
}

//------------------------------------------------------------------------------

int procurar_inimigos_xy( int x, int y )
{
	int i;
	int maxDef = -10;
	int maxArco = 10;
	int unit = -1;
	
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		if( unidades[i].x == x && unidades[i].y == y && unidades[i].dono != jogadorAtual &&\
		tipos[unidades[i].tipo].arco <= maxArco )
		{
			if( tipos[unidades[i].tipo].arco < maxArco || tipos[unidades[i].tipo].defesa >= maxDef )
			{
				maxArco = tipos[unidades[i].tipo].arco;
				maxDef = tipos[unidades[i].tipo].defesa;
				unit = i;
			}
		}
	}
	return unit;
}

//------------------------------------------------------------------------------

int procurar_unidade_vazia()
{
	int i;
	
	for( i = 0; i < numPelotoes; i++ )
	{
		if( unidades[i].tipo == -1 )
		{
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------

void ordenar_pelotoes()
{
	/*int i = 0;
	int j = 0;
	int fundo = 0;
	
	i = 0;
	while( i < numPelotoes && fundo < numPelotoes )
	{            
		fundo = i + 1;
		while( unidades[i].tipo == -1 && fundo < numPelotoes )
		{
			while( unidades[fundo].tipo == -1 && fundo < numPelotoes )
			{
				fundo++;
			}
			if( fundo < numPelotoes )
			{
			unidades[i].dono = unidades[fundo].dono;
			unidades[i].movimentos = unidades[fundo].movimentos;
			unidades[i].nivelMagico = unidades[fundo].nivelMagico;
			unidades[i].quantidade = unidades[fundo].quantidade;
			unidades[i].tipo = unidades[fundo].tipo;
			unidades[i].x = unidades[fundo].x;
			unidades[i].y = unidades[fundo].y;
			strcpy( unidades[i].nome, unidades[fundo].nome );
			
			eliminar_pelotao( fundo, 0 );
			}
		}
		i++;
	}
	numPelotoesUsados = i - 1;*/
	numPelotoesUsados = numPelotoes;
	
}

//------------------------------------------------------------------------------

void criar_pelotao( int x, int y, int nTipo, int dono, int quant, int movi )
{
	int i = 0;
	
	i = procurar_unidade_vazia();
	
	unidades[i].x = x;
	unidades[i].y = y;
	unidades[i].tipo = nTipo;
	unidades[i].dono = dono;
	unidades[i].quantidade = quant;
	unidades[i].movimentos = movi;
	strcpy( unidades[i].nome, tipos[nTipo].nome );
	
	ordenar_pelotoes();
}

//------------------------------------------------------------------------------

void eliminar_pelotao( int N, int ordem )
{
	unidades[N].x = -1;
	unidades[N].y = -1;
	unidades[N].tipo = -1;
	strcpy( unidades[N].nome, "          " );
	
	if( ordem )
	ordenar_pelotoes();
}

//------------------------------------------------------------------------------

void separar_pelotao( int nUnit, int quant )
{
	if( quant < unidades[nUnit].quantidade && quant > 0 )
	{
		criar_pelotao( unidades[nUnit].x, unidades[nUnit].y, unidades[nUnit].tipo, unidades[nUnit].dono, quant, unidades[nUnit].movimentos );
		unidades[nUnit].quantidade -= quant;
	}
	
	if( selecaoX > -1 )
	procurar_pelotoes_xy( selecaoX, selecaoY );
}

//------------------------------------------------------------------------------

void juntar_pelotao( int sec, int pri )
{
	if( unidades[sec].tipo == unidades[pri].tipo && unidades[sec].dono == unidades[pri].dono )
	{
		unidades[pri].quantidade += unidades[sec].quantidade;
		
		if( unidades[sec].movimentos < unidades[pri].movimentos )
		unidades[pri].movimentos = unidades[sec].movimentos;
		
		eliminar_pelotao( sec );
	}
	
	if( selecaoX > -1 )
	procurar_pelotoes_xy( selecaoX, selecaoY );
}

//------------------------------------------------------------------------------

void redutor_movi_terr( int nUnit )
{
	int x = unidades[nUnit].x;
	int y = unidades[nUnit].y;
	int r = tipos[unidades[nUnit].tipo].raca;
	
	if( mapa[x][y].vegetacao > 4 && racas[r].penaVegetacao )unidades[nUnit].movimentos--;
	if( mapa[x][y].relevo > 1 && racas[r].penaRelevo )unidades[nUnit].movimentos--;
	if( mapa[x][y].temperatura > 6 && racas[r].penaDeserto )unidades[nUnit].movimentos--;
	if( mapa[x][y].temperatura < 2 && racas[r].penaNeve )unidades[nUnit].movimentos--;
	
	if( unidades[nUnit].movimentos < 0 )unidades[nUnit].movimentos = 0;
}

//------------------------------------------------------------------------------

void mover_pelotao_aux( int x, int y, int nUnit )
{
	int inim;
	int inim2;
	int inimCid;
	int resultadoCid;
	int inimQuant;
	
	//Combate
	inim = procurar_inimigos_xy( unidades[nUnit].x+x, unidades[nUnit].y+y );
	if( inim >= 0 )
	{
		inimQuant = unidades[inim].quantidade;
		
		inim = combate( nUnit, inim );
		
		if( inim == 2 && (inimQuant * 10) <= unidades[nUnit].quantidade )
		{
			unidades[nUnit].movimentos++;
		}
	}
	
	if( unidades[nUnit].tipo >= 0 )
	{
		inim2 = procurar_inimigos_xy( unidades[nUnit].x+x, unidades[nUnit].y+y );
		if( inim2 >= 0 )
		{
			unidades[nUnit].movimentos--;
			if( tipos[unidades[nUnit].tipo].arco == 0 )
			{
				redutor_movi_terr( nUnit );
			}
		}
		else
		{
			//Tomar cidade
			inimCid = procurar_cid_xy( unidades[nUnit].x+x, unidades[nUnit].y+y );
			if( inimCid >= 0 && cidades[inimCid].dono != jogadorAtual )
			{
				resultadoCid = atacar_cidade( nUnit, inimCid, inim );
			}
		
			if( inimCid == -1 || cidades[inimCid].dono == jogadorAtual || resultadoCid < 0 )
			{
				unidades[nUnit].movimentos--;
				
				if( tipos[unidades[nUnit].tipo].arco == 0 || inim == -1 || resultadoCid == -2 )
				{
					unidades[nUnit].x = unidades[nUnit].x + x;
					unidades[nUnit].y = unidades[nUnit].y + y;
					selecaoX = unidades[nUnit].x;
					selecaoY = unidades[nUnit].y;
					redutor_movi_terr( nUnit );
				}
			}
		}
	
	}
		
	procurar_pelotoes_xy( selecaoX, selecaoY );
	selecaoC = procurar_cidade( selecaoX, selecaoY );
}

//------------------------------------------------------------------------------

void mover_pelotao()
{
	//NO
	if( (evento.key.keysym.sym == SDLK_KP7) && unidades[selecaoP].x > 0 && unidades[selecaoP].y > 0 && movDiagonal )
	{
		mover_pelotao_aux( -1, -1, selecaoP );
	}
	//N
	if( evento.key.keysym.sym == SDLK_KP8 && unidades[selecaoP].y > 0 )
	{
		mover_pelotao_aux( 0, -1, selecaoP );
	}
	//NE
	if( evento.key.keysym.sym == SDLK_KP9 && unidades[selecaoP].x < TAM_MAPA_X-1 && unidades[selecaoP].y > 0 && movDiagonal )
	{
		mover_pelotao_aux( 1, -1, selecaoP );
	}
	//O
	if( evento.key.keysym.sym == SDLK_KP4 && unidades[selecaoP].x > 0 )
	{
		mover_pelotao_aux( -1, 0, selecaoP );
	}
	//L
	if( evento.key.keysym.sym == SDLK_KP6 && unidades[selecaoP].x < TAM_MAPA_X-1 )
	{
		mover_pelotao_aux( 1, 0, selecaoP );
	}
	//SO
	if( evento.key.keysym.sym == SDLK_KP1 && unidades[selecaoP].x > 0 && unidades[selecaoP].y < TAM_MAPA_Y-1 && movDiagonal )
	{
		mover_pelotao_aux( -1, 1, selecaoP );
	}
	//S
	if( evento.key.keysym.sym == SDLK_KP2 && unidades[selecaoP].y < TAM_MAPA_Y-1 )
	{
		mover_pelotao_aux( 0, 1, selecaoP );
	}
	//SE
	if( evento.key.keysym.sym == SDLK_KP3 && unidades[selecaoP].x < TAM_MAPA_X-1 && unidades[selecaoP].y < TAM_MAPA_Y-1 && movDiagonal )
	{
		mover_pelotao_aux( 1, 1, selecaoP );
	}
}

//------------------------------------------------------------------------------

void desenhar_info_unit_geral( int x, int y, int nUnit )
{
	escrever( x, y-40, unidades[nUnit].nome , fonte20 );
	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
	desenhar_territorio( x+5, y+5, mapa[unidades[nUnit].x][unidades[nUnit].y] );
	desenhar_pelotao( x+5, y+5, unidades[nUnit].tipo, nUnit );
	desenhar_infos_terr( x-2, y+80, unidades[nUnit].x, unidades[nUnit].y );
	
	strcpy( aux, "Tipo: " );
	strcat( aux, tipos[unidades[nUnit].tipo].nome );
	escrever( x+85, y, aux );
	strcpy( aux, "Quantidade: ");
	itoa( unidades[nUnit].quantidade, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+20, aux );
	strcpy( aux, "Movimentos: ");
	itoa( unidades[nUnit].movimentos, aux2, 10);
	strcat( aux, aux2);
	strcpy( aux2, "/");
	strcat( aux, aux2);
	itoa( tipos[unidades[nUnit].tipo].movimento, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+40, aux );
}

//------------------------------------------------------------------------------

void desenhar_info_tipo( int x, int y, int nTipo )
{
	escrever( x, y-40, tipos[nTipo].nome , fonte20 );
	
	strcpy( aux, "Raça: " );
	strcat( aux, racas[tipos[nTipo].raca].nome );
	escrever( x, y, aux );
	
	strcpy( aux, "Ataque: ");
	itoa( tipos[nTipo].ataque, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+40, aux );
	strcpy( aux, "Defesa: ");
	itoa( tipos[nTipo].defesa, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+60, aux );
	strcpy( aux, "Vida: ");
	itoa( tipos[nTipo].vida, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+80, aux );
	//strcpy( aux, "Tipo de dano: ");
	//strcat( aux, tipos[unidades[nUnit].tipo].nome );
	//strcat( aux, aux2);
	//escrever( x, y+120, aux );
	strcpy( aux, "Dano: ");
	itoa( tipos[nTipo].dano, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+100, aux );
	
	strcpy( aux, "Movimentos: ");
	itoa( tipos[nTipo].movimento, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+140, aux );
	
	strcpy( aux, "Armas de alcançe: ");
	itoa( tipos[nTipo].arco, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+180, aux );
	strcpy( aux, "Lança: ");
	itoa( tipos[nTipo].lanca, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+200, aux );
	strcpy( aux, "Montaria: ");
	itoa( tipos[nTipo].montaria, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+220, aux );
	
	strcpy( aux, "Nível Mágico: ");
	itoa( tipos[nTipo].nivelMagico, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+260, aux );
	//strcpy( aux, "Máximo de mana: ");
	//itoa( tipos[nTipo].maxMana, aux2, 10);
	//strcat( aux, aux2);
	//escrever( x, y+280, aux );
	if( racas[tipos[nTipo].raca].elemento == 0 )strcpy( aux, "Elemento: Ar");
	if( racas[tipos[nTipo].raca].elemento == 1 )strcpy( aux, "Elemento: Terra");
	if( racas[tipos[nTipo].raca].elemento == 2 )strcpy( aux, "Elemento: Gelo");
	if( racas[tipos[nTipo].raca].elemento == 3 )strcpy( aux, "Elemento: Fogo");
	if( racas[tipos[nTipo].raca].elemento == 4 )strcpy( aux, "Elemento: Natureza");
	escrever( x, y+300, aux );
	
	strcpy( aux, "Treinamento: ");
	itoa( tipos[nTipo].treino, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+340, aux );
	strcpy( aux, "Materiais: ");
	itoa( tipos[nTipo].materiais, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+360, aux );
	strcpy( aux, "Magia: ");
	itoa( tipos[nTipo].magia, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+380, aux );
}

//------------------------------------------------------------------------------

void desenhar_infos_unit( int x, int y, int nUnit )
{
	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
	desenhar_territorio( x+5, y+5, mapa[unidades[nUnit].x][unidades[nUnit].y] );
	desenhar_pelotao( x+5, y+5, unidades[nUnit].tipo, nUnit );
	
	strcpy( aux, "Nome: " );
	strcat( aux, unidades[nUnit].nome );
	escrever( x+85, y+3, aux );
	strcpy( aux, "Tipo: " );
	strcat( aux, tipos[unidades[nUnit].tipo].nome );
	escrever( x+85, y+20, aux );
	strcpy( aux, "Quantidade: ");
	itoa( unidades[nUnit].quantidade, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+40, aux );
	strcpy( aux, "Movimentos: ");
	itoa( unidades[nUnit].movimentos, aux2, 10);
	strcat( aux, aux2);
	strcpy( aux2, "/");
	strcat( aux, aux2);
	itoa( tipos[unidades[nUnit].tipo].movimento, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+60, aux );
	
	botao( x+220, y+40, 1, 0 );
}

//------------------------------------------------------------------------------

int dados_unidade( int nUnit )
{
	int x = 0;
	int y = 0;
	int i = 0;
		
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
				//Mudar nome
				if( botao( 70, 200, 16, 1 ) )
				{
				receber_texto( 19, "Nome desse pelotão:" );
				strcpy( unidades[nUnit].nome, aux2 );
				}
				//Criar cidade
				if( botao( 110, 200, 17, 1 ) )
				{
				selecaoC = procurar_cidade( selecaoX, selecaoY );
				
				if( selecaoC == -1 )
				{
					criar_cidade( unidades[nUnit].x, unidades[nUnit].y, tipos[unidades[nUnit].tipo].raca, unidades[nUnit].dono, unidades[nUnit].quantidade, racas[tipos[unidades[selecaoP].tipo].raca].tempoCid, 1 );
				}
				else
				{
					cidades[selecaoC].populacao = cidades[selecaoC].populacao + unidades[nUnit].quantidade;
				}
				eliminar_pelotao( nUnit );
				procurar_pelotoes_xy( selecaoX, selecaoY );
				selecaoC = procurar_cidade( selecaoX, selecaoY );
				return 0;
				}
				//Cortar Árvores
				if( botao( 150, 200, 22, 1 ) )
				{
				cortar_arvores( unidades[nUnit].x, unidades[nUnit].y, nUnit );
				}
				//Queimar Vegetação
				if( botao( 190, 200, 23, 1 ) )
				{
				queimar_vegetacao( unidades[nUnit].x, unidades[nUnit].y, nUnit );
				}
				
				//Separar Pelotão
				if( botao( 230, 200, 31, 1 ) )
				{
				i = receber_numero( 19, "Quantas unidades separar?" );
				if( i < unidades[nUnit].quantidade && i > 0 )
				{
					separar_pelotao( nUnit, i );
					return 0;
				}
				}
				
				//Juntar Pelotão
				if( botao( 270, 200, 32, 1 ) )
				{
				i = procurar_pelotoes_para_juntar( unidades[nUnit].x, unidades[nUnit].y, unidades[nUnit].tipo, unidades[nUnit].dono, nUnit );
				if( i >= 0)
				{
					juntar_pelotao( nUnit, i );
					return 0;
				}
				}
				
				//Magias
				if( botao( 70, 240, 18, 1 ) )
				{
				var = 4;
				}                
		
				//Voltar
				if( botao( 980, 724, 7, 5 ) ){var = 1;}
			}
		
			if( evento.type == SDL_KEYDOWN )
			{
				atalhos( 3 );
			}
		}
		
		preencher_fundo();
		
		desenhar_info_unit_geral( 70, 70, nUnit );
		desenhar_info_tipo( 700, 70, unidades[nUnit].tipo );
		
		botao( 70, 200, 16, 0 );//Mudar nome        
		botao( 110, 200, 17, 0 );//Castelo
		botao( 150, 200, 22, 0 );//Machado e Árvore
		botao( 190, 200, 23, 0 );//Fogueira
		botao( 230, 200, 31, 0 );//Separar
		botao( 270, 200, 32, 0 );//Juntar
		
		botao( 70, 240, 18, 0 );//Magias  
	
		botao( 980, 724, 7, 0 );//X vermelho
		
		if( SDL_Flip( tela ) == -1 )
		{
			return 1;
		}
		controlar_frame();
	}
}

//------------------------------------------------------------------------------
