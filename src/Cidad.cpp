#include "AAA.h"

void preparar_matriz_cidadesI()
{
	int i=0;
	
	//Orc
	cidadesI[ i ].x = 0;
	cidadesI[ i ].y = 0;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
	//Elfo
	cidadesI[ i ].x = 70;
	cidadesI[ i ].y = 0;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
	//Mortos-Vivos
	cidadesI[ i ].x = 70;
	cidadesI[ i ].y = 70;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
	//Humanos
	cidadesI[ i ].x = 0;
	cidadesI[ i ].y = 70;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
	//Formigas
	cidadesI[ i ].x = 140;
	cidadesI[ i ].y = 0;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
	//Anões
	cidadesI[ i ].x = 140;
	cidadesI[ i ].y = 70;
	cidadesI[ i ].w = 70;
	cidadesI[ i ].h = 70;
	i++;
}

//------------------------------------------------------------------------------

void preparar_cidades()
{
	int i;
	
	for( i = 0; i < numCidades; i++ )
	{
		cidades[i].raca = -1;
		cidades[i].treinando = -1;
		cidades[i].infTreino = 0;
		cidades[i].x = -1;
		cidades[i].y = -1;
	}
}

//------------------------------------------------------------------------------

void colocar_cidades_iniciais()
{
	int i = 0;
	
	for( i = 0; i < numJogadoresUsados; i++ )
	{
		criar_cidade( jogadores[i].x, jogadores[i].y, jogadores[i].raca, i, jogadores[i].populacao, 0, 0 );
	}
	
	calcular_cidades();
	
	for( i = 0; i < numJogadoresUsados; i++ )
	{
		jogadores[i].telaX = jogadores[i].x * 70 - TAM_TELA_X/2;
		jogadores[i].telaY = jogadores[i].y * 70 - TAM_TELA_Y/2;
	}
	telaX = jogadores[jogadorAtual].telaX;
	telaY = jogadores[jogadorAtual].telaY;
}

//------------------------------------------------------------------------------

int procurar_cidade( int x, int y )
{
	int i;
	
	for( i = 0; i < numCidades; i++ )
	{
		if( cidades[i].x == x && cidades[i].y == y )
		{
			return i;
		}
	}
	
	return -1;
}

//------------------------------------------------------------------------------

int procurar_cid_xy( int x, int y )
{
	int i;
	
	for( i = 0; i < numCidades; i++ )
	{
		if( cidades[i].x == x && cidades[i].y == y )
		{
			return i;
		}
	}
	
	return -1;
}

//------------------------------------------------------------------------------

void desenhar_cidade( int x, int y, cidade cid )
{
	/*if( cid.raca == 0 )
	aplicar_superficie( x, y, cidadesImagem, tela, &cidadesI[0] );
	if( cid.raca == 1 )
	aplicar_superficie( x, y, cidadesImagem, tela, &cidadesI[1] );
	if( cid.raca == 2 )
	aplicar_superficie( x, y, cidadesImagem, tela, &cidadesI[2] );
	if( cid.raca == 3 )
	aplicar_superficie( x, y, cidadesImagem, tela, &cidadesI[3] );*/
	aplicar_superficie( x, y, cidadesImagem, tela, &cidadesI[cid.raca] );
	
	if( jogadores[cid.dono].cor == 0 && infoCores )
	aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[19] );
	if( jogadores[cid.dono].cor == 1 && infoCores )
	aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[20] );
	if( jogadores[cid.dono].cor == 2 && infoCores )
	aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[21] );
	if( jogadores[cid.dono].cor == 3 && infoCores )
	aplicar_superficie( x+64, y+2, bordasImagem, tela, &bordasI[22] );
	
	if( cid.emConstr > 0 && infoUnits )
	aplicar_superficie( x+59, y+28, bordasImagem, tela, &bordasI[15] );
}

//------------------------------------------------------------------------------

void desenhar_cidades()
{
	int i = 0;
	
	for( i = 0; i < numCidades; i++ )
	{
		if( (cidades[i].x)*70 + 70 - telaX > 0 && (cidades[i].x)*70 - telaX - TAM_TELA_X < 0 &&\
		(cidades[i].y)*70 + 70 - telaY > 0 && (cidades[i].y)*70 - telaY - TAM_TELA_Y < 0 )
		{
			desenhar_cidade( cidades[i].x*70-telaX+POS_TELA_X, cidades[i].y*70-telaY+POS_TELA_Y, cidades[i] );
		}
	}
}

//------------------------------------------------------------------------------

void calcular_cidade( int i )
{
	int cont = 0;
	
	//Magia
	if( racas[cidades[i].raca].elemento == 0 )//Vento
	{
		cidades[i].magia = 10 - mapa[cidades[i].x][cidades[i].y].relevo - mapa[cidades[i].x][cidades[i].y].vegetacao;
	}
	else if( racas[cidades[i].raca].elemento == 1 )//Terra
	{
		cidades[i].magia = 1 + mapa[cidades[i].x][cidades[i].y].relevo*3;
	}
	else if( racas[cidades[i].raca].elemento == 2 )//Água
	{
		cidades[i].magia = 10 - (int)(mapa[cidades[i].x][cidades[i].y].temperatura*2.5);
		if( cidades[i].magia < 0 )
		cidades[i].magia = 0;
	}
	else if( racas[cidades[i].raca].elemento == 3 )//Fogo
	{
		cidades[i].magia = (int)((mapa[cidades[i].x][cidades[i].y].temperatura - 4)*2.5);
		if( cidades[i].magia < 0 )
		cidades[i].magia = 0;
	}
	else if( racas[cidades[i].raca].elemento == 4 )//Natureza
	{
		cidades[i].magia = (int)(mapa[cidades[i].x][cidades[i].y].vegetacao*10/6);
	}
	cidades[i].magia =  cidades[i].magia / 2;
	
	//Materiais
	cidades[i].materiais = (int)(( ( mapa[cidades[i].x][cidades[i].y].relevo )*3 + 0.5 )*(int)cidades[i].populacao/10);
	
	//Treinamento
	if( mapa[cidades[i].x][cidades[i].y].temperatura >= 4 )
	{
		cidades[i].treinamento = 7 + ( mapa[cidades[i].x][cidades[i].y].temperatura )*2;
	}
	if( mapa[cidades[i].x][cidades[i].y].temperatura < 4 )
	{
		cidades[i].treinamento = 15 - mapa[cidades[i].x][cidades[i].y].temperatura*2;
	}
	
	//Crescimento
	if( racas[cidades[i].raca].crescTempIdeal >= 0 )
	{
		if( racas[cidades[i].raca].crescTempIdeal >= mapa[cidades[i].x][cidades[i].y].temperatura )
		{
			cidades[i].crescimento = 10 - (racas[cidades[i].raca].crescTempIdeal - mapa[cidades[i].x][cidades[i].y].temperatura);
		}
		if( racas[cidades[i].raca].crescTempIdeal < mapa[cidades[i].x][cidades[i].y].temperatura )
		{
			cidades[i].crescimento = 10 + (racas[cidades[i].raca].crescTempIdeal - mapa[cidades[i].x][cidades[i].y].temperatura);
		}
	}
	else//Quando for -1 ou seja, cresce mais tanto no deserto quanto na neve
	{
		if( mapa[cidades[i].x][cidades[i].y].temperatura <= 4 )
		{
			cidades[i].crescimento = 10 - mapa[cidades[i].x][cidades[i].y].temperatura;
		}
		if( mapa[cidades[i].x][cidades[i].y].temperatura > 4 )
		{
			cidades[i].crescimento = 2 + mapa[cidades[i].x][cidades[i].y].temperatura;
		}
	}
	
	//cidades[i].crescimento = 9 - mapa[cidades[i].x][cidades[i].y].temperatura;
	//cidades[i].crescimento = mapa[cidades[i].x][cidades[i].y].temperatura + 1;
	
	
	
	cidades[i].crescimento = cidades[i].crescimento * racas[cidades[i].raca].crescimento;
	cidades[i].treinamento = (int)( cidades[i].treinamento * racas[cidades[i].raca].treinamento );
	cidades[i].magia = (int)( cidades[i].magia * racas[cidades[i].raca].magia );
	cidades[i].materiais = (int)( cidades[i].materiais * racas[cidades[i].raca].materiais );
	
	//Máximo de população
	cidades[i].maxPopulacao = espaco_terr( cidades[i].x, cidades[i].y ) * racas[cidades[i].raca].maxPop;
	
	if( cidades[i].maxPopulacao < cidades[i].populacao )
	{
		cidades[i].crescimento = -10;
	}
	if( cidades[i].maxPopulacao == cidades[i].populacao )
	{
		cidades[i].crescimento = 0;
	}
	
	//Focos
	if( cidades[i].foco == 0 )
	{
		cidades[i].magia = cidades[i].magia * 2;
	}
	if( cidades[i].foco == 1 )
	{
		cidades[i].materiais = cidades[i].materiais * 2;
	}
	if( cidades[i].foco == 2 )
	{
		cidades[i].treinamento = cidades[i].treinamento * 2;
	}
	if( cidades[i].foco == 3 )
	{
		cidades[i].crescimento = cidades[i].crescimento * 2;
	}
}

//------------------------------------------------------------------------------

void calcular_cidades()
{
	int i;
	
	for( i = 0; i < numCidades; i++ )
	{
		calcular_cidade( i );
	}
}

//------------------------------------------------------------------------------

int procurar_cidade_vazia()
{
	int i;
	
	for( i = 0; i < numCidades; i++ )
	{
		if( cidades[i].raca == -1 )
		{
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------

void criar_cidade( int x, int y, int raca, int dono, int quant, int tempo, int nome )
{
	int i = 0;
	
	i = procurar_cidade_vazia();
	
	cidades[i].x = x;
	cidades[i].y = y;
	cidades[i].raca = raca;
	cidades[i].dono = dono;
	cidades[i].populacao = quant;
	cidades[i].emConstr = tempo;
	calcular_cidade( i );
	
	if( nome == 1 )
	{
		receber_texto( 19, "Nome da cidade:" );
		strcpy( cidades[i].nome, aux2 );
	}
	else
	{
		strcpy( cidades[i].nome, jogadores[dono].nome );
	}
}

//------------------------------------------------------------------------------

void eliminar_cidade( int N )
{
	cidades[N].raca = -1;
	cidades[N].treinando = -1;
	cidades[N].infTreino = 0;
	cidades[N].x = -1;
	cidades[N].y = -1;
	strcpy( cidades[N].nome, "          " );
	
	selecaoC = -1;
}

//------------------------------------------------------------------------------

int atacar_cidade( int nUnit, int nCid, int quemAtacou )
{
	int popRende;
	int nUnitQuant;
	int CidPop;
	
	CidPop = (int)cidades[nCid].populacao;
	nUnitQuant = unidades[nUnit].quantidade;
	popRende = 4*(unidades[nUnit].quantidade*(tipos[unidades[nUnit].tipo].ataque+tipos[unidades[nUnit].tipo].defesa+tipos[unidades[nUnit].tipo].dano/2+tipos[unidades[nUnit].tipo].vida/5));
	if( cidades[nCid].populacao <= popRende  )
	{
		//Cidade se Rende
		cidades[nCid].dono = jogadorAtual;
		cidades[nCid].treinando = -1;
		cidades[nCid].completado = 0;
		if( cidades[nCid].raca != tipos[unidades[nUnit].tipo].raca )
		{
			cidades[nCid].populacao = cidades[nCid].populacao - cidades[nCid].populacao/4;
		}
		return -2;
	}
	else if( quemAtacou == -1 )
	{
		if( ((cidades[nCid].populacao) - popRende) > popRende*3/4 )
		{
			cidades[nCid].populacao -= popRende;
		}
		else
		{
			cidades[nCid].populacao = popRende * 3 / 4;
		}
		if( tipos[unidades[nUnit].tipo].montaria == 0 && tipos[unidades[nUnit].tipo].arco == 0 )
		{
			unidades[nUnit].quantidade = (int)(( unidades[nUnit].quantidade * tipos[unidades[nUnit].tipo].vida - cidades[nCid].populacao/10 )/tipos[unidades[nUnit].tipo].vida);
		}
		
		itoa( nUnitQuant-unidades[nUnit].quantidade, aux2, 10);
		strcpy( aux, aux2 );
		strcat( aux, "/" );
		itoa( CidPop-(int)cidades[nCid].populacao, aux2, 10);
		strcat( aux, aux2 );
		escrever( (unidades[nUnit].x+cidades[nCid].x)*35+20-telaX, (unidades[nUnit].y+cidades[nCid].y)*35+20-telaY, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 1000 );
		
		if( unidades[nUnit].quantidade <= 0 )
		{
			eliminar_pelotao( nUnit );
		}
	}
	return 0;
}

//------------------------------------------------------------------------------

void desenhar_info_cid_geral( int x, int y, int nCid )
{
	escrever( x, y-40, cidades[nCid].nome , fonte20 );
	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
	desenhar_territorio( x+5, y+5, mapa[cidades[nCid].x][cidades[nCid].y] );
	desenhar_cidade( x+5, y+5, cidades[nCid] );
	desenhar_infos_terr( x-2, y+80, cidades[nCid].x, cidades[nCid].y );
	
	strcpy( aux, "População: ");
	itoa( (int)cidades[nCid].populacao, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+10, aux );
	strcpy( aux, "População máxima: ");
	itoa( (int)cidades[nCid].maxPopulacao, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+30, aux );
}

//------------------------------------------------------------------------------

void desenhar_info_treino( int x, int y, int nCid )
{
	strcpy( aux, "Treinando: ");
	escrever( x+10, y-20, aux );

	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
	desenhar_territorio( x+5, y+5, mapa[cidades[nCid].x][cidades[nCid].y] );
	desenhar_pelotao( x+5, y+5, cidades[nCid].treinando );
	
	strcpy( aux, "Tipo: " );
	strcat( aux, tipos[cidades[nCid].treinando].nome );
	escrever( x+85, y, aux );
	strcpy( aux, "Quantidade: " );
	itoa( cidades[nCid].treinandoQuant, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+20, aux );
	strcpy( aux, "Completado: " );
	itoa( cidades[nCid].completado, aux2, 10);
	strcat( aux, aux2);
	strcat( aux, "/" );
	itoa( tipos[cidades[nCid].treinando].treino, aux2, 10);
	strcat( aux, aux2);
	escrever( x+85, y+40, aux );
	botao( 40, y, 8, 0 );
	if( cidades[nCid].infTreino == 0 )
	{
		botao( 40, y+25, 10, 0 );
	}
	else
	{
		botao( 40, y+25, 9, 0 );
	}
}

//------------------------------------------------------------------------------

void desenhar_focos( int x, int y, int nCid )
{
		strcpy( aux, "Magia: ");
		itoa( cidades[nCid].magia, aux2, 10);
		strcat( aux, aux2);
		escrever( x+10, y+80, aux );
		//aplicar_superficie( x, y+100, bordasImagem, tela, &bordasI[10] );
		botao( x+5, y+105, 2, 0 );
		if( cidades[nCid].foco == 0 )
		{
			aplicar_superficie( x+5, y+105, bordasImagem, tela, &bordasI[24] );
		}
		
		strcpy( aux, "Materiais: ");
		itoa( cidades[nCid].materiais, aux2, 10);
		strcat( aux, aux2);
		escrever( x+120, y+80, aux );
		//aplicar_superficie( x+120, y+100, bordasImagem, tela, &bordasI[10] );
		botao( x+125, y+105, 3, 0 );
		if( cidades[nCid].foco == 1 )
		{
			aplicar_superficie( x+125, y+105, bordasImagem, tela, &bordasI[24] );
		}
		
		strcpy( aux, "Treinamento: ");
		itoa( cidades[nCid].treinamento, aux2, 10);
		strcat( aux, aux2);
		escrever( x-10, y+200, aux );
		//aplicar_superficie( x, y+220, bordasImagem, tela, &bordasI[10] );
		botao( x+5, y+225, 4, 0 );
		if( cidades[nCid].foco == 2 )
		{
			aplicar_superficie( x+5, y+225, bordasImagem, tela, &bordasI[24] );
		}
		
		strcpy( aux, "Crescimento: ");
		itoa( (int)cidades[nCid].crescimento, aux2, 10);
		strcat( aux, aux2);
		escrever( x+120, y+200, aux );
		//aplicar_superficie( x+120, y+220, bordasImagem, tela, &bordasI[10] );
		botao( x+125, y+225, 5, 0 );
		if( cidades[nCid].foco == 3 )
		{
			aplicar_superficie( x+125, y+225, bordasImagem, tela, &bordasI[24] );
		}
}

//------------------------------------------------------------------------------

void desenhar_infos_cid( cidade cid )
{
	int x=750;
	int y=20;
	
	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
	desenhar_territorio( x+5, y+5, mapa[cid.x][cid.y] );
	desenhar_cidade( x+5, y+5, cid );
	escrever( x, y+80, cid.nome, fonte20 );
	strcpy( aux, "População: ");
	itoa( (int)cid.populacao, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+100, aux );
		
	botao( x+105, y+20, 0, 0 );
		
	if( cid.treinando >= 0 )
	{
		aplicar_superficie( x+170, y, bordasImagem, tela, &bordasI[10] );
		desenhar_territorio( x+175, y+5, mapa[cid.x][cid.y] );
		desenhar_pelotao( x+175, y+5, cid.treinando );
	}
}

//------------------------------------------------------------------------------

int mudar_treinando( int nCid, int nTipo, int inf )
{
	int quant = 0;
	/*if( cidades[nCid].completado > 0 )
	{
		Confirmar Mudança
	}*/
	if( inf == 0 )
	{
		quant = receber_numero( 20, "Quantas unidades treinar?" );
	}
	else
	{
		quant = cidades[nCid].treinandoQuant;
	}
	if( quant <= 0 )
	{
		return -1;
	}
	else if( cidades[nCid].populacao < quant )
	{
		strcpy( aux, "Falta População " );
		escrever( 400, 450, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 2000 );
		return -1;
	}
	else if( cidades[nCid].magia < tipos[nTipo].magia )
	{
		strcpy( aux, "Falta Magia " );
		escrever( 400, 450, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 2000 );
		return -1;
	}
	else if( jogadores[cidades[nCid].dono].mana < ( tipos[nTipo].mana * quant ) )
	{
		strcpy( aux, "Falta Mana " );
		escrever( 400, 450, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 2000 );
		return -1;
	}
	else if( jogadores[cidades[nCid].dono].materiais < ( tipos[nTipo].materiais * quant ) )
	{
		strcpy( aux, "Falta Material " );
		escrever( 400, 450, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 2000 );
		return -1;
	}
	else
	{
		jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais - ( tipos[nTipo].materiais * quant );
		if( cidades[nCid].completado == 0 && cidades[nCid].treinando >= 0 )
		{
			jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais + ( tipos[cidades[nCid].treinando].materiais * cidades[nCid].treinandoQuant );
		}
		jogadores[cidades[nCid].dono].mana = jogadores[cidades[nCid].dono].mana - ( tipos[nTipo].mana * quant );
		if( cidades[nCid].completado == 0 && cidades[nCid].treinando >= 0 )
		{
			jogadores[cidades[nCid].dono].mana = jogadores[cidades[nCid].dono].mana + ( tipos[cidades[nCid].treinando].mana * cidades[nCid].treinandoQuant );
		}
	}
	
	cidades[nCid].treinando = nTipo;
	cidades[nCid].treinandoQuant = quant;
	cidades[nCid].completado = 0;
}

//------------------------------------------------------------------------------

void preparar_lista_treino( int inicio, cidade cid, int total )
{
	int i;
	int pos = 0;
	
	for( i = 0; i < 7; i++ )
	{
		listaTreino[i] = -1;
	}
	
	i = inicio;
	if( total == 0 )
	{
		//Preenche lista (verifica raça)
		while( i < numTiposUsados && pos < 7 )
		{
			if( tipos[i].raca == cid.raca && ( tipos[i].dono == -1 || tipos[i].dono == cid.dono ) )
			{
				listaTreino[pos] = i;
				pos++;
			}
			i++;
		}
		
		//Verifica se há mais para baixo
		pos = 0;
		giroB = -1;
		while( i < numTipos && pos == 0)
		{
			if( tipos[i].raca == cid.raca && ( tipos[i].dono == -1 || tipos[i].dono == cid.dono ) )
			{
				giroB = i;
				pos = 1;
			}
			else
			{
				giroB = -1;
			}
			i++;
		}
		//Verifica se há mais para cima
		i = 0;
		pos = 0;
		giroC = -1;
		while( i < numTipos && i < listaTreino[0] && pos == 0)
		{
			if( tipos[i].raca == cid.raca && ( tipos[i].dono == -1 || tipos[i].dono == cid.dono ) )
			{
				giroC = i;
				pos = 1;
			}
			else
			{
				giroC = -1;
			}
			i++;
		}
	}
	else//---------------------------------------------------------------------
	{
		//Preenche lista (unidades gerais)
		while( i < numTipos && pos < 7 )
		{
			if( tipos[i].corpo >= 0 && ( tipos[i].dono == -1 || tipos[i].dono == jogadorAtual ) )
			{
				listaTreino[pos] = i;
				pos++;
			}
			i++;
		}
		
		//Verifica se há mais para baixo
		pos = 0;
		giroB = -1;
		while( i < numTipos && pos == 0 )
		{
			if( tipos[i].corpo >= 0 && ( tipos[i].dono == -1 || tipos[i].dono == jogadorAtual ) )
			{
				giroB = i;
				pos = 1;
			}
			else
			{
				giroB = -1;
			}
			i++;
		}
		//Verifica se há mais para cima
		i = 0;
		pos = 0;
		giroC = -1;
		while( i < numTipos && i < listaTreino[0] && pos == 0 )
		{
			if( tipos[i].corpo >= 0 && ( tipos[i].dono == -1 || tipos[i].dono == jogadorAtual ) )
			{
				giroC = i;
				pos = 1;
			}
			else
			{
				giroC = -1;
			}
			i++;
		}
	}
}

//------------------------------------------------------------------------------

void girar_lista( int sentido )
{
	if( sentido == 0 )
	{
		posLista = giroC;
	}
	else
	{
		posLista = giroB;
	}
}

//------------------------------------------------------------------------------

void desenhar_lista_treino( int x, int y, cidade cid, int total )
{
	int i = 0;
	
	for( i = 0; i < 7; i++ )
	{
		if( listaTreino[i] >= 0 )
		{
			aplicar_superficie( x, y+i*90, bordasImagem, tela, &bordasI[10] );
			if( total == 0 )
			desenhar_territorio( x+5, y+5+i*90, mapa[cid.x][cid.y] );
			desenhar_pelotao( x+5, y+5+i*90, listaTreino[i] );
			strcpy( aux, "Tipo: " );
			strcat( aux, tipos[listaTreino[i]].nome );
			escrever( x+85, y+i*90, aux );
			strcpy( aux, "Magia: " );
			itoa( tipos[listaTreino[i]].magia, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+15+i*90, aux );
			strcpy( aux, "Materiais: " );
			itoa( tipos[listaTreino[i]].materiais, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+30+i*90, aux );
			strcpy( aux, "Treino: " );
			itoa( tipos[listaTreino[i]].treino, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+45+i*90, aux );
		}
	}
	
	if( giroC >= 0 )
	botao( x - 30, y, 12, 0 );
	
	if( giroB >= 0 )
	botao( x - 30, y + 600, 13, 0 );
}

//------------------------------------------------------------------------------

int dados_cidade( int nCid )
{
	int x = 0;
	int y = 0;
	int i = 0;
	
	posLista = 0;
	preparar_lista_treino( posLista, cidades[nCid], 0 );
	calcular_cidade( nCid );
	
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
					receber_texto( 19, "Novo nome para a cidade:" );
					strcpy( cidades[nCid].nome, aux2 );
				}
				//DESTRUIR
				if( botao( 110, 200, 16, 1 ) )
				{
					eliminar_cidade( nCid );
					return -1;
				}
				
				//Mudança de Foco
				x = 70;
				y = 400;
				//Magia
				if( botao( x+5, y+105, 2, 1 ) )
				{
					cidades[nCid].foco = 0;
				}
				//Materiais
				if( botao( x+125, y+105, 3, 1 ) )
				{
					if( cidades[nCid].foco == 0 && ( tipos[cidades[nCid].treinando].magia > cidades[nCid].magia/2 ) )
					{
						//Confirmar Mudança
						if( cidades[nCid].completado == 0 )
						{
							jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais + tipos[cidades[nCid].treinando].materiais;
						}
						cidades[nCid].treinando = -1;
					}
					cidades[nCid].foco = 1;
				}
				//Treinamento
				if( botao( x+5, y+225, 4, 1 ) )
				{
					if( cidades[nCid].foco == 0 && ( tipos[cidades[nCid].treinando].magia > cidades[nCid].magia/2 ) )
					{
						//Confirmar Mudança
						if( cidades[nCid].completado == 0 )
						{
							jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais + tipos[cidades[nCid].treinando].materiais;
						}
						cidades[nCid].treinando = -1;
					}
					cidades[nCid].foco = 2;
				}
				//Crescimento
				if( botao( x+125, y+225, 5, 4 ) )
				{
					if( cidades[nCid].foco == 0 && ( tipos[cidades[nCid].treinando].magia > cidades[nCid].magia/2 ) )
					{
						//Confirmar Mudança
						if( cidades[nCid].completado == 0 )
						{
							jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais + tipos[cidades[nCid].treinando].materiais;
						}
						cidades[nCid].treinando = -1;
					}
					cidades[nCid].foco = 3;
				}
				calcular_cidade( nCid );
						
				//Escolher unidade para treinar
				x = 700;
				y = 50;
				//Girar lista de treino
				if( botao( x - 30, y, 12, 1 ) && giroC >= 0 )
				{
					girar_lista( 0 );
					preparar_lista_treino( posLista, cidades[nCid], 0 );
				}
				if( botao( x - 30, y + 600, 12, 1 ) && giroB >= 0 )
				{
					girar_lista( 1 );
					preparar_lista_treino( posLista, cidades[nCid], 0 );
				}
				
				for( i = 0; i < 7; i++ )
				{
					if( listaTreino[i] >= 0 )
					{
						if( botao( x+5, y+5+i*90, 2, 1 ) )
						{
							mudar_treinando( nCid, listaTreino[i], 0 );
						}
					}
				}
				
				if( cidades[nCid].treinando >= 0 )
				{
					//Cancelar Treino
					if( botao( 40, 300, 8, 1 ) )
					{
						if( cidades[nCid].completado == 0 )
						{
							jogadores[cidades[nCid].dono].materiais = jogadores[cidades[nCid].dono].materiais + ( tipos[cidades[nCid].treinando].materiais * cidades[nCid].treinandoQuant );
							jogadores[cidades[nCid].dono].mana = jogadores[cidades[nCid].dono].mana + ( tipos[cidades[nCid].treinando].mana * cidades[nCid].treinandoQuant );
						}
						
						cidades[nCid].treinando = -1;
					}
					
					//Escolher entre treinar infinitamente ou não
					if( botao( 40, 325, 9, 1 ) )
					{
						if( cidades[nCid].infTreino == 0 )
						{
							cidades[nCid].infTreino = 1;
						}
						else
						{
							cidades[nCid].infTreino = 0;
						}
					}
				}
				
				//Voltar
				if( botao( 980, 724, 7, 5 ) ){var = 1;}
			}
			
			if( evento.type == SDL_KEYDOWN )
			{
				atalhos( 4 );
			}
		}
		
		preencher_fundo();
		
		desenhar_info_cid_geral( 70, 70, nCid );
		botao( 70, 200, 16, 0 );//Mudar nome
		botao( 110, 200, 24, 0 );//Destruir cidade
		
		if( cidades[nCid].treinando >= 0 )
		{
			desenhar_info_treino( 70, 300, nCid );
		}
		desenhar_focos( 70, 400, nCid );
		desenhar_infos_jogador( 400, 30, jogadores[jogadorAtual] );
		if( cidades[nCid].emConstr > 0 )
		{
			strcpy( aux, "Cidade em Construção: " );
			itoa( cidades[nCid].emConstr, aux2, 10);
			strcat( aux, aux2);
			escrever( 50, 450, aux, fonte20, corVermelha );
		}
		
		desenhar_lista_treino( 700, 50, cidades[nCid] );
		botao( 980, 724, 7, 0 );
		
		if( SDL_Flip( tela ) == -1 )
		{
			return 1;
		}
		controlar_frame();
	}
}

//------------------------------------------------------------------------------
