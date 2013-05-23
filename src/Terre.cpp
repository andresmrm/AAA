#include "AAA.h"

void preparar_matriz_terrenosI()
{
	int i=0;
	
	//Terra
	terrenosI[ i ].x = 0;
	terrenosI[ i ].y = 0;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Grama1
	terrenosI[ i ].x = 70;
	terrenosI[ i ].y = 0;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Grama2
	terrenosI[ i ].x = 140;
	terrenosI[ i ].y = 0;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Grama3
	terrenosI[ i ].x = 210;
	terrenosI[ i ].y = 0;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Neve1
	terrenosI[ i ].x = 0;
	terrenosI[ i ].y = 70;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Neve2
	terrenosI[ i ].x = 70;
	terrenosI[ i ].y = 70;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Neve3
	terrenosI[ i ].x = 140;
	terrenosI[ i ].y = 70;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Neve4
	terrenosI[ i ].x = 210;
	terrenosI[ i ].y = 70;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Deserto1
	terrenosI[ i ].x = 0;
	terrenosI[ i ].y = 140;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Deserto2
	terrenosI[ i ].x = 70;
	terrenosI[ i ].y = 140;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Deserto3
	terrenosI[ i ].x = 140;
	terrenosI[ i ].y = 140;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Deserto4
	terrenosI[ i ].x = 210;
	terrenosI[ i ].y = 140;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Floresta1
	terrenosI[ i ].x = 0;
	terrenosI[ i ].y = 210;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Floresta2
	terrenosI[ i ].x = 70;
	terrenosI[ i ].y = 210;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Floresta3
	terrenosI[ i ].x = 140;
	terrenosI[ i ].y = 210;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Relevo1
	terrenosI[ i ].x = 0;
	terrenosI[ i ].y = 280;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Relevo2
	terrenosI[ i ].x = 70;
	terrenosI[ i ].y = 280;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Relevo3
	terrenosI[ i ].x = 140;
	terrenosI[ i ].y = 280;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Agua1
	terrenosI[ i ].x = 210;
	terrenosI[ i ].y = 210;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
	
	//Agua2
	terrenosI[ i ].x = 210;
	terrenosI[ i ].y = 280;
	terrenosI[ i ].w = 70;
	terrenosI[ i ].h = 70;
	i++;
}

//------------------------------------------------------------------------------

void testar_terrenos()
{
	aplicar_superficie( 70, 0, terrenosImagem, tela, &terrenosI[1] );
	aplicar_superficie( 140, 0, terrenosImagem, tela, &terrenosI[2] );
	aplicar_superficie( 210, 0, terrenosImagem, tela, &terrenosI[3] ); 
	aplicar_superficie( 0, 70, terrenosImagem, tela, &terrenosI[4] );    
	aplicar_superficie( 70, 70, terrenosImagem, tela, &terrenosI[5] );  
	aplicar_superficie( 140, 70, terrenosImagem, tela, &terrenosI[6] );  
	aplicar_superficie( 210, 70, terrenosImagem, tela, &terrenosI[7] );
	aplicar_superficie( 0, 140, terrenosImagem, tela, &terrenosI[8] );
	aplicar_superficie( 70, 140, terrenosImagem, tela, &terrenosI[9] );
	aplicar_superficie( 140, 140, terrenosImagem, tela, &terrenosI[10] );
	aplicar_superficie( 210, 140, terrenosImagem, tela, &terrenosI[11] );
	aplicar_superficie( 0, 210, terrenosImagem, tela, &terrenosI[12] );
	aplicar_superficie( 70, 210, terrenosImagem, tela, &terrenosI[13] );
	aplicar_superficie( 140, 210, terrenosImagem, tela, &terrenosI[14] );
	aplicar_superficie( 0, 280, terrenosImagem, tela, &terrenosI[15] );
	aplicar_superficie( 70, 280, terrenosImagem, tela, &terrenosI[16] );
	aplicar_superficie( 140, 280, terrenosImagem, tela, &terrenosI[17] );
	aplicar_superficie( 210, 210, terrenosImagem, tela, &terrenosI[18] );
	aplicar_superficie( 210, 280, terrenosImagem, tela, &terrenosI[19] );
}

//------------------------------------------------------------------------------

void alisar_mapa()
{
	int i;
	int j;
	int x;
	int y;
	
	for( y = 0; y < TAM_MAPA_Y; y++ )
	{
		for( x = 0; x < TAM_MAPA_X; x++ )
		{
			//Vegetação
			for( j = -1; j < 2; j++ )
			{
				for( i = -1; i < 2; i++ )
				{
					if( mapa[ x + i ][ y + j ].vegetacao > ( mapa[ x ][ y ].vegetacao + 1 ) )
					{
						if( x + i < TAM_MAPA_X && x + i >= 0 && y + j < TAM_MAPA_Y && y + j >= 0 )
						{
							mapa[ x ][ y ].vegetacao++;
						}
					}
				}
			}
			if( mapa[ x ][ y ].vegetacao > 6 )
			{
				mapa[ x ][ y ].vegetacao = 6;
			}
			
			//Relevo
			for( j = -1; j < 2; j++ )
			{
				for( i = -1; i < 2; i++ )
				{
					if( mapa[ x + i ][ y + j ].relevo > ( mapa[ x ][ y ].relevo + 1 ) )
					{
						if( x + i < TAM_MAPA_X && x + i >= 0 && y + j < TAM_MAPA_Y && y + j >= 0 )
						{
							mapa[ x ][ y ].relevo++;
						}
					}
				}
			}
			if( mapa[ x ][ y ].relevo > 3 )
			{
				mapa[ x ][ y ].relevo = 3;
			}
			
			//Deserto
			for( j = -1; j < 2; j++ )
			{
				for( i = -1; i < 2; i++ )
				{
					if( mapa[ x + i ][ y + j ].temperatura > ( mapa[ x ][ y ].temperatura + 1 ) && mapa[ x + i ][ y + j ].temperatura > 4 )
					{
						if( x + i < TAM_MAPA_X && x + i >= 0 && y + j < TAM_MAPA_Y && y + j >= 0 )
						{
							mapa[ x ][ y ].temperatura++;
						}
					}
				}
			}
			if( mapa[ x ][ y ].temperatura > 8 )
			{
				mapa[ x ][ y ].temperatura = 8;
			}
			
			//Neve
			for( j = -1; j < 2; j++ )
			{
				for( i = -1; i < 2; i++ )
				{
					if( mapa[ x + i ][ y + j ].temperatura < ( mapa[ x ][ y ].temperatura - 1 ) && mapa[ x + i ][ y + j ].temperatura < 4 )
					{
						if( x + i < TAM_MAPA_X && x + i >= 0 && y + j < TAM_MAPA_Y && y + j >= 0 )
						{
							mapa[ x ][ y ].temperatura--;
						}
					}
				}
			}
			if( mapa[ x ][ y ].temperatura < 0 )
			{
				mapa[ x ][ y ].temperatura = 0;
			}
			
			//Agua
			for( j = -1; j < 2; j++ )
			{
				for( i = -1; i < 2; i++ )
				{
					if( mapa[ x + i ][ y + j ].agua > ( mapa[ x ][ y ].agua + 1 ) )
					{
						if( x + i < TAM_MAPA_X && x + i >= 0 && y + j < TAM_MAPA_Y && y + j >= 0 )
						{
							mapa[ x ][ y ].agua++;
						}
					}
				}
			}
			if( mapa[ x ][ y ].agua > 2 )
			{
				mapa[ x ][ y ].agua = 2;
			}
		}
	}
}

//------------------------------------------------------------------------------

void manchar_mapa( int quantidade, int tamanho, int variacao, int intensidade, int tipo )
{
	int x = 0;
	int y = 0;
	int q = 0;
	int t = 0;
	int v = 0;
	int cont = 0;
	int x0 = 0;
	int y0 = 0;
	int i = 0;
	int intensidade0 = intensidade;
		
	if( tipo == 2 )
	{
		cont = 4 - intensidade;
	}
	else if( tipo == 3 )
	{
		cont = intensidade - 4;
	}
	else
	{
		cont = intensidade;
	}
	
	for( q = 0; q < quantidade; q++ )
	{
		x = rand() % TAM_MAPA_X;
		y = rand() % TAM_MAPA_Y;
		x0 = x;
		y0 = y;
		
		if( variacao > 0 )
		{
			v = tamanho + rand()%variacao - rand()%variacao;
		}
		else
		{
			v = tamanho;
		}
		
		intensidade = intensidade0;
		
		for( i = 0; i < cont; i++ )
		{
			for( t = 0; t < v; t++ )
			{
				if( tipo == 1 ) //Relevo
				{
					if( mapa[ x ][ y ].relevo < intensidade )
					mapa[ x ][ y ].relevo = intensidade;
				}
				else if( tipo == 2 ) //Neve
				{
					if( mapa[ x ][ y ].temperatura > intensidade )
					mapa[ x ][ y ].temperatura = intensidade;
				}
				else if( tipo == 3 ) //Deserto
				{
					if( mapa[ x ][ y ].temperatura < intensidade )
					mapa[ x ][ y ].temperatura = intensidade;
				}
				else if( tipo == 4 ) //Vegetação
				{
					if( mapa[ x ][ y ].vegetacao < intensidade )
					mapa[ x ][ y ].vegetacao = intensidade;
				}
				else if( tipo == 5 ) //Água
				{
					if( mapa[ x ][ y ].agua < intensidade )
					mapa[ x ][ y ].agua = intensidade;
				}
				
				do
				{
					x = x + rand()%3-1;
				}while( x < 0 || x > TAM_MAPA_X - 1 );
				
				do
				{
					y = y + rand()%3-1;
				}while( y < 0 || y > TAM_MAPA_Y - 1 );
				
			}
			if( tipo == 2 )
			{
				intensidade++;
			}
			else
			{
				intensidade--;
			}
			v = (int)( v * 1.5 );
			x = x0;
			y = y0;
		}
	}
}

//------------------------------------------------------------------------------

void preparar_mapa()
{
	int x = 0;
	int y = 0; 
	
	//Mapa limpo
	for( y = 0; y < TAM_MAPA_Y; y++ )
	{
		for( x = 0; x < TAM_MAPA_X; x++ )
		{
		mapa[x][y].vegetacao = 0;
		mapa[x][y].relevo = 0;
		mapa[x][y].temperatura = 4;
		mapa[x][y].agua = 0;
		mapa[x][y].x = x;
		mapa[x][y].y = y;
		}
	}
	
	/*manchar_mapa(vegetacao[0],vegetacao[1],vegetacao[2],1,0);//Vegetação
	manchar_mapa(relevo[0],relevo[1],relevo[2],1,1);//Relevo
	manchar_mapa(neve[0],neve[1],neve[2],1,3);//Neve
	manchar_mapa(deserto[0],deserto[1],deserto[2],1,2);//Deserto*/
	//manchar_mapa(4,1,25,1,4);//Água
	
	manchar_mapa( vegetacao[0],vegetacao[1],vegetacao[2],6,4 );//Vegetação
	manchar_mapa( relevo[0],relevo[1],relevo[2],3,1 );//Relevo
	manchar_mapa( neve[0],neve[1],neve[2],0,2 );//Neve
	manchar_mapa( deserto[0],deserto[1],deserto[2],8,3 );//Deserto
	
	alisar_mapa();
	alisar_mapa();
	alisar_mapa();
	alisar_mapa();
	alisar_mapa();
	alisar_mapa();
	alisar_mapa();
}

//------------------------------------------------------------------------------

void desenhar_territorio( int x, int y, territorio terr )
{
	//Terra
	if( terr.temperatura <= 4 && terr.temperatura >= 1 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[0] );
	
	//Grama
	if( terr.vegetacao == 1 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[1] );
	if( terr.vegetacao == 2 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[2] );
	if( terr.vegetacao >= 3 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[3] );
	
	//Deserto
	if( terr.temperatura == 5 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[8] );
	if( terr.temperatura == 6 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[9] );
	if( terr.temperatura == 7 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[10] );
	if( terr.temperatura >= 8 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[11] );
	
	//Neve
	if( terr.temperatura <= 0 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[7] );
	if( terr.temperatura == 1 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[6] );
	if( terr.temperatura == 2 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[5] );
	if( terr.temperatura == 3 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[4] );
	
	//Relevo
	if( terr.relevo == 1 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[15] );
	if( terr.relevo == 2 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[16] );
	if( terr.relevo >= 3 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[17] );
	
	//Floresta
	if( terr.vegetacao == 4 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[12] );
	if( terr.vegetacao == 5 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[13] );
	if( terr.vegetacao >= 6 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[14] );
	
	//Agua
	if( terr.agua == 1 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[18] );
	if( terr.agua == 2 )
	aplicar_superficie( x, y, terrenosImagem, tela, &terrenosI[19] );
}

//------------------------------------------------------------------------------

void desenhar_mapa()
{
	int x = 0;
	int y = 0;
	
	for( y = 0; y < TAM_MAPA_Y; y++ )
	{
		for( x = 0; x < TAM_MAPA_X; x++ )
		{
			if( mapa[x][y].x*70 + 70 - telaX > 0 && mapa[x][y].x*70 - telaX - TAM_TELA_X < 0 &&\
				mapa[x][y].y*70 + 70 - telaY > 0 && mapa[x][y].y*70 - telaY - TAM_TELA_Y < 0)
			{
				desenhar_territorio( mapa[x][y].x*70-telaX+POS_TELA_X, mapa[x][y].y*70-telaY+POS_TELA_Y, mapa[x][y] );
			}
		}
	}
}

//------------------------------------------------------------------------------

int espaco_terr( int x, int y )
{
	int cont = 0;
	
	cont = mapa[x][y].relevo;
	if( mapa[x][y].vegetacao >= 4 )
	{
		cont += (mapa[x][y].vegetacao-3);
	}
	
	if( cont >= 6 )
	{
		return 250;
	}
	else if( cont == 5 )
	{
		return 500;
	}
	else if( cont == 4 )
	{
		return 750;
	}
	else if( cont == 3 )
	{
		return 1000;
	}
	else if( cont == 2 )
	{
		return 2000;
	}
	else if( cont == 1 )
	{
		return 5000;
	}
	else if( cont == 0 )
	{
		return 10000;
	}
}

//------------------------------------------------------------------------------

void desenhar_infos_terr( int x, int y, int terrX, int terrY )
{
	aplicar_superficie( x, y, bordasImagem, tela, &bordasI[9] );
	
	if( selecaoX >= 0 && selecaoY >= 0 )
	{
		itoa(mapa[terrX][terrY].vegetacao, aux, 10);
		escrever( x+20, y+3, aux );
		
		itoa(mapa[terrX][terrY].relevo, aux, 10);
		escrever( x+46, y+3, aux );
		
		itoa(mapa[terrX][terrY].temperatura, aux, 10);
		escrever( x+72, y+3, aux );
		
		itoa( espaco_terr( terrX, terrY), aux, 10);
		escrever( x+20, y+19, aux );
	}
}

//------------------------------------------------------------------------------

void selecionar_terr()
{
	if( evento.button.x > POS_TELA_X && evento.button.x < TAM_TELA_X + POS_TELA_X &&\
		evento.button.y > POS_TELA_Y && evento.button.y < TAM_TELA_Y + POS_TELA_Y )
	{
		selecaoX = ( evento.button.x + telaX - POS_TELA_X ) / 70;
		selecaoY = ( evento.button.y + telaY - POS_TELA_Y ) / 70;
		procurar_pelotoes_xy( selecaoX, selecaoY );
		selecaoC = procurar_cidade( selecaoX, selecaoY );
	}
}

//------------------------------------------------------------------------------

void cortar_arvores( int x, int y, int lenhador )
{
	if( mapa[x][y].vegetacao >= 4 && unidades[lenhador].movimentos > 0 && unidades[lenhador].quantidade >= 10 )
	{
		mapa[x][y].vegetacao--;
		if( mapa[x][y].vegetacao == 3 )
		{
		mapa[x][y].vegetacao = 2;
		}
		jogadores[unidades[lenhador].dono].materiais += 200;
		unidades[lenhador].movimentos = 0;
		strcpy( aux, "+200 materiais" );
		escrever( 400, 400, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 1000 );
	}
	
	if( unidades[lenhador].quantidade < 10 )
	{
		strcpy( aux, "Tropas insuficientes nesse pelotão" );
		escrever( 300, 400, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 2000 );
	}
}

//------------------------------------------------------------------------------

void queimar_vegetacao( int x, int y, int queimador )
{
	if( mapa[x][y].vegetacao > 0 && unidades[queimador].movimentos > 0 )
	{
		mapa[x][y].vegetacao = 0;
		unidades[queimador].movimentos = 0;
	}
}
