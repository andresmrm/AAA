#include "AAA.h"

//------------------------------------------------------------------------------

void preparar_tipos()
{
	int i;
	
	for( i = 0; i < numTipos; i++ )
	{
		eliminar_tipo( i, 0 );
	}

	i = 0;
	
	strcpy(tipos[i].nome,"Orc povoador");
	tipos[i].dono = 0;
	tipos[i].corpo = 0;
	tipos[i].raca = 0;
	tipos[i].movimento = 20;
	tipos[i].ataque = 2;
	tipos[i].defesa = 0;
	tipos[i].vida = 10;
	tipos[i].dano = 5;
	tipos[i].treino2 = 0;
	tipos[i].materiais2 = 0;
	tipos[i].magia2 = 20;
	tipos[i].lanca = 0;
	tipos[i].montaria = 1;
	tipos[i].arco = 1;
	i++;
	
	strcpy(tipos[i].nome,"Elfo");
	tipos[i].corpo = 1;
	tipos[i].raca = 1;
	tipos[i].movimento = 4;
	tipos[i].ataque = 2;
	tipos[i].defesa = 2;
	tipos[i].vida = 10;
	tipos[i].dano = 5;
	tipos[i].treino2 = 0;
	tipos[i].materiais2 = 0;
	tipos[i].magia2 = 10;
	tipos[i].lanca = 0;
	tipos[i].arco = 0;
	i++;
	
	strcpy(tipos[i].nome,"Esqueleto Ambulant");
	tipos[i].corpo = 2;
	tipos[i].raca = 2;
	tipos[i].movimento = 10;
	tipos[i].ataque = 1;
	tipos[i].defesa = 0;
	tipos[i].vida = 5;
	tipos[i].dano = 4;
	tipos[i].treino2 = 2;
	tipos[i].materiais2 = 0;
	tipos[i].magia2 = 10;
	i++;
	
	strcpy(tipos[i].nome,"Vagante");
	tipos[i].corpo = 2;
	tipos[i].raca = 3;
	tipos[i].movimento = 10;
	tipos[i].ataque = 1;
	tipos[i].defesa = 0;
	tipos[i].vida = 5;
	tipos[i].dano = 4;
	tipos[i].treino2 = 2;
	tipos[i].materiais2 = 0;
	tipos[i].magia2 = 15;
	i++;
	
	strcpy(tipos[i].nome,"Runeiro");
	tipos[i].corpo = 2;
	tipos[i].raca = 5;
	tipos[i].movimento = 10;
	tipos[i].ataque = 1;
	tipos[i].defesa = 0;
	tipos[i].vida = 5;
	tipos[i].dano = 4;
	tipos[i].treino2 = 2;
	tipos[i].materiais2 = 0;
	tipos[i].magia2 = 15;
	i++;
}

//------------------------------------------------------------------------------

int procurar_tipo_vazio()
{
	int i;
	
	for( i = 0; i < numTipos; i++ )
	{
		if( tipos[i].raca == -1 )
		{
			ordenar_tipos();
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------

int procurar_editor_tipos_trava( int nTipo )
{
	int i;
	
	for( i = 0; i < numPelotoesUsados; i++ )
	{
		if( unidades[i].tipo == nTipo )
		{
			return 1;
		}
	}
	
	for( i = 0; i < numCidades; i++ )
	{
		if( cidades[i].treinando == nTipo )
		{
			return 1;
		}
	}
	
	return 0;
}

//------------------------------------------------------------------------------

void ordenar_tipos()
{
	int i = 0;
	int j = 0;
	int fundo = 0;
	
	i = 0;
	while( i < numTipos && fundo < numTipos )
	{
		fundo = i + 1;
		while( tipos[i].raca == -1 && fundo < numTipos )
		{
			while( tipos[fundo].raca == -1 && fundo < numTipos )
			{
				fundo++;
			}
			if( fundo < numTipos )
			{
				tipos[i].corpo = tipos[fundo].corpo;
				tipos[i].raca = tipos[fundo].raca;
				tipos[i].dono = tipos[fundo].dono;
				tipos[i].treino2 = tipos[fundo].treino2;
				tipos[i].materiais2 = tipos[fundo].materiais2;
				tipos[i].magia2 = tipos[fundo].magia2;
				tipos[i].arco = tipos[fundo].arco;
				tipos[i].lanca = tipos[fundo].lanca;
				tipos[i].montaria = tipos[fundo].montaria;
				strcpy( tipos[i].nome, tipos[fundo].nome );
			
				for( j = 0; j < numPelotoesUsados; j++ )
				{
					if( unidades[j].tipo == fundo )
					{
						unidades[j].tipo = i;
					}
				}
				eliminar_tipo( fundo, 0 );
			}
		}
		i++;
	}
	numTiposUsados = i - 1;
	
	calcular_tipos();
}

//------------------------------------------------------------------------------

void eliminar_tipo( int N, int ordem )
{
	int i;
	int numPelotoesUsados0;
	
	tipos[N].corpo = -1;
	tipos[N].raca = -1;
	tipos[N].dono = -1;
	tipos[N].treino2 = 0;
	tipos[N].materiais2 = 0;
	tipos[N].magia2 = 0;
	tipos[N].arco = 0;
	tipos[N].lanca = 0;
	tipos[N].montaria = 0;
	
	strcpy( tipos[N].nome, "                   " );
	
	numPelotoesUsados0 = numPelotoesUsados;
	for( i = 0; i < numPelotoesUsados0; i++ )
	{
		if( unidades[i].tipo == N )
		{
			eliminar_pelotao( i, ordem );
		}
	}
	
	if( ordem )
	{
		ordenar_tipos();
	}
}

//------------------------------------------------------------------------------

void calcular_tipo( int nTipo )
{
	//Atributos
	//Dano
	tipos[nTipo].dano = 5 + tipos[nTipo].arco*2;
	tipos[nTipo].dano += racas[tipos[nTipo].raca].dano;
	
	//Defesa
	tipos[nTipo].defesa = tipos[nTipo].materiais2 + tipos[nTipo].treino2 / 3;
	tipos[nTipo].defesa += racas[tipos[nTipo].raca].defesa;
	
	//Ataque
	tipos[nTipo].ataque = tipos[nTipo].treino2 + tipos[nTipo].materiais2 / 3 - tipos[nTipo].lanca;
	tipos[nTipo].ataque += racas[tipos[nTipo].raca].ataque;
	
	//Vida
	tipos[nTipo].vida = 10 + tipos[nTipo].treino2 / 5;
	tipos[nTipo].vida += racas[tipos[nTipo].raca].vida;
	
	//Movimento
	tipos[nTipo].movimento = 1 + tipos[nTipo].montaria;
	tipos[nTipo].movimento += racas[tipos[nTipo].raca].movimento;
	
	//Nivel Mágico
	tipos[nTipo].nivelMagico = tipos[nTipo].magia2 / 2;
	
	//Bonus Mágico
	if( racas[tipos[nTipo].raca].elemento == 0 )//Ar
	{
		tipos[nTipo].movimento += (int)(tipos[nTipo].magia2 / 2.5);
	}
	else if( racas[tipos[nTipo].raca].elemento == 1 )//Terra
	{
		tipos[nTipo].vida += (tipos[nTipo].magia2)*2;
	}
	else if( racas[tipos[nTipo].raca].elemento == 2 )//Água
	{
		tipos[nTipo].defesa += tipos[nTipo].magia2;
	}
	else if( racas[tipos[nTipo].raca].elemento == 3 )//Fogo
	{
		tipos[nTipo].dano += (tipos[nTipo].magia2)*2;
	}
	else if( racas[tipos[nTipo].raca].elemento == 4 )//Natureza
	{
		tipos[nTipo].ataque += tipos[nTipo].magia2;
	}
	
	//Máximo de Mana
	//tipos[nTipo].maxMana = 0;//tipos[nTipo].nivelMagico * tipos[nTipo].nivelMagico * tipos[nTipo].nivelMagico * tipos[nTipo].nivelMagico * tipos[nTipo].nivelMagico;
	
	/*
	Niv  0 1 2  3   4    5         10
	
	x^3  0 1 8  27  64   125       1000
	x^4  0 1 16 81  256  625       10000
	5^x  1 5 25 125 625  3125      ~= 1milhão
	x^5  0 1 32 243 1024 15625 ... 100000
	*/
	
	//Custos
	//Mana
	tipos[nTipo].mana = tipos[nTipo].magia2 * tipos[nTipo].magia2 * tipos[nTipo].magia2 * tipos[nTipo].magia2;
	
	//Magia
	tipos[nTipo].magia = tipos[nTipo].magia2 * 2;
	
	//Materiais
	tipos[nTipo].materiais = tipos[nTipo].materiais2 + tipos[nTipo].montaria + tipos[nTipo].arco;
	
	//Treino
	tipos[nTipo].treino = tipos[nTipo].treino2*10 + tipos[nTipo].montaria*10 + tipos[nTipo].arco*10;
}

//------------------------------------------------------------------------------

void calcular_tipos()
{
	int i;
	
	for( i = 0; i < numTiposUsados ; i++ )
	{
		if( tipos[i].raca >= 0 )
		{
			calcular_tipo( i );
		}
	}
}

//------------------------------------------------------------------------------

int editor_tipos()
{
	int x = 0;
	int y = 0;
	int i = 0;
	int trava = 0;
	
	posLista = 0;
	preparar_lista_treino( posLista, cidades[0], 1 );
		
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
				
				x = 50;
				y = 50;
				//Girar lista de treino
				if( botao( x - 30, y, 12, 1 ) && giroC >= 0 )
				{
					girar_lista( 0 );
					preparar_lista_treino( posLista, cidades[0], 1 );
				}
				if( botao( x - 30, y + 600, 12, 1 ) && giroB >= 0 )
				{
					girar_lista( 1 );
					preparar_lista_treino( posLista, cidades[0], 1 );
				}
				//Escolher unidade para editar
				for( i = 0; i < 7; i++ )
				{
					if( listaTreino[i] >= 0 )
					{
						if( botao( x+5, y+5+i*90, 2, 1 ) )
						{
							editando = listaTreino[i];
							trava = procurar_editor_tipos_trava( editando );
						}
					}
				}
				
				//Novo tipo
				if( botao( 420, 100, 14, 1 ) )
				{
					editando = procurar_tipo_vazio();
					tipos[editando].raca = jogadores[jogadorAtual].raca;
					tipos[editando].corpo = 0;
					tipos[editando].dono = jogadorAtual;
					ordenar_tipos();
					preparar_lista_treino( posLista, cidades[0], 1 );
					trava = 0;
					receber_texto( 19, "Nome do tipo de unidade:" );
					strcpy( tipos[editando].nome, aux2 );
				}
				
				if( editando >= 0 )
				{
					//Deletar tipo
					if( botao( 460, 100, 15, 1 ) )
					{
						eliminar_tipo( editando );
						editando = -1;
						preparar_lista_treino( posLista, cidades[0], 1 );
					}
					
					//Entrar nome
					if( botao( 420, 140, 16, 1 ) )
					{
						receber_texto( 19, "Nome do tipo de unidade:" );
						strcpy( tipos[editando].nome, aux2 );
					}
					
					if( trava == 0 )
					{
						x = 600;
						y = 400;
						
						//Mudar raça
						if( botao( x - 20, 130 + 20, 12, 1 ) && tipos[editando].raca < numRacasUsadas - 1 )
						{
							tipos[editando].raca++;
						}
						if( botao( x - 20, 130 + 40, 13, 1 ) && tipos[editando].raca > 0 )
						{
							tipos[editando].raca--;
						}
						//------------------------------------------------------
						
						x = 700;
						y = 500;
						
						//Mudar Arco
						if( botao( x - 20, y + 20, 12, 1 ) && tipos[editando].arco < 2 + racas[tipos[editando].raca].arco )
						{
							tipos[editando].arco++;
							tipos[editando].lanca = 0;
						}
						if( botao( x - 20, y + 40, 13, 1 ) && tipos[editando].arco > 0 )
						{
							tipos[editando].arco--;
						}
						//Mudar Lança
						if( botao( x - 20, y + 100, 12, 1 ) && tipos[editando].lanca < 2 + racas[tipos[editando].raca].lanca )
						{
							tipos[editando].lanca++;
							tipos[editando].arco = 0;
						}
						if( botao( x - 20, y + 120, 13, 1 ) && tipos[editando].lanca > 0 )
						{
							tipos[editando].lanca--;
						}
						//Mudar Montaria
						if( botao( x - 20, y + 180, 12, 1 ) && tipos[editando].montaria < 2 + racas[tipos[editando].raca].montaria )
						{
							tipos[editando].montaria++;
						}
						if( botao( x - 20, y + 200, 13, 1 ) && tipos[editando].montaria > 0 )
						{
							tipos[editando].montaria--;
						}
						//------------------------------------------------------
						
						x = 500;
						y = 500;
						
						//Mudar magia
						if( botao( x - 20, y + 20, 12, 1 ) )
						{
							tipos[editando].magia2++;
						}
						if( botao( x - 20, y + 40, 13, 1 ) && tipos[editando].magia2 > 0 )
						{
							tipos[editando].magia2--;
						}
						//Mudar materiais
						if( botao( x - 20, y + 100, 12, 1 ) )
						{
							tipos[editando].materiais2++;
						}
						if( botao( x - 20, y + 120, 13, 1 ) && tipos[editando].materiais2 > 0 )
						{
							tipos[editando].materiais2--;
						}
						//Mudar treino
						if( botao( x - 20, y + 180, 12, 1 ) )
						{
							tipos[editando].treino2++;
						}
						if( botao( x - 20, y + 200, 13, 1 ) && tipos[editando].treino2 > 0 )
						{
							tipos[editando].treino2--;
						}
					}
				}
				
				//Voltar
				if( botao( 980, 724, 7, 1 ) ){var = -2;}
			}
		
			if( evento.type == SDL_KEYDOWN )
			{
				atalhos( 2 );
			}
		}
		
		preencher_fundo();
		
		desenhar_infos_jogador( 400, 5, jogadores[jogadorAtual] );
		desenhar_lista_treino( 50, 50, cidades[0], 1 );
		if( editando >= 0 )
		{
			x = 600;
			y = 130;
			//Imagem do tipo
			aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
			desenhar_pelotao( x+5, y+5, editando );
			botao( x - 20, y + 20, 12, 0 );
			botao( x - 20, y + 40, 13, 0 );
			desenhar_info_tipo( x+100, y-50, editando );
			
			x = 700;
			y = 500;
			//Armas de alcance
			aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+5, 21, 0 );
			strcpy( aux, "Armas de alcance: ");
			itoa( tipos[editando].arco, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y, aux );
			botao( x - 20, y + 20, 12, 0 );
			botao( x - 20, y + 40, 13, 0 );
			//Lança
			aplicar_superficie( x, y+80, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+85, 19, 0 );
			strcpy( aux, "Lança: ");
			itoa( tipos[editando].lanca, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+80, aux );
			botao( x - 20, y + 100, 12, 0 );
			botao( x - 20, y + 120, 13, 0 );
			//Cavalaria
			aplicar_superficie( x, y+160, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+165, 20, 0 );
			strcpy( aux, "Montaria: ");
			itoa( tipos[editando].montaria, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+160, aux );
			botao( x - 20, y + 180, 12, 0 );
			botao( x - 20, y + 200, 13, 0 );
			
			x = 500;
			y = 500;
			//Magia
			aplicar_superficie( x, y, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+5, 2, 0 );
			strcpy( aux, "Magia: ");
			itoa( tipos[editando].magia2, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y, aux );
			botao( x - 20, y + 20, 12, 0 );
			botao( x - 20, y + 40, 13, 0 );
			//Materiais
			aplicar_superficie( x, y+80, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+85, 3, 0 );
			strcpy( aux, "Materiais: ");
			itoa( tipos[editando].materiais2, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+80, aux );
			botao( x - 20, y + 100, 12, 0 );
			botao( x - 20, y + 120, 13, 0 );
			//Treino
			aplicar_superficie( x, y+160, bordasImagem, tela, &bordasI[10] );
			botao( x+5, y+165, 4, 0 );
			strcpy( aux, "Treino: ");
			itoa( tipos[editando].treino2, aux2, 10);
			strcat( aux, aux2);
			escrever( x+85, y+160, aux );
			botao( x - 20, y + 180, 12, 0 );
			botao( x - 20, y + 200, 13, 0 );
			
			calcular_tipo( editando );
		}
		
		x = 420;
		y = 100;
		botao( x, y, 14, 0 );//Manuscrito
		if( editando >= 0 )
		{
			botao( x+40, y, 15, 0 );//Manuscrito com X
			botao( x, y+40, 16, 0 );//Papel escrito
		}
		
		botao( 980, 724, 7, 0 );//X vermelho
		
		if( SDL_Flip( tela ) == -1 )
		{
			return 1;
		}
		controlar_frame();
	}
	editando = -1;
}
