#include "AAA.h"

void preparar_matriz_botoesI()
{
	int i=0;
	
	//Informações da Cidade      i = 0
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 0;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Informações do Pelotão
	botoesI[ i ].x = 40;
	botoesI[ i ].y = 0;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Foco Magia
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 40;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Foco Material
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 40;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Foco Treinamento
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 110;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Foco Crescimento          i = 5
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 110;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Ampulheta
	botoesI[ i ].x = 80;
	botoesI[ i ].y = 0;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//X Vermelho
	botoesI[ i ].x = 120;
	botoesI[ i ].y = 0;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//X Vermelho (pequeno)
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 40;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	//Infinito (pequeno)
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 60;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	//I (pequeno)              i = 10
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 80;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	//Armas indicando botão do editor de tipos
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 0;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Seta para cima (pequena)
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 100;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	//Seta para baixo (pequena)
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 120;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	//Manuscrito
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 40;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Manuscrito com X vermelho        i = 15
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 80;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Papel escrito
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 120;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Castelinho
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 160;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Medalha
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 200;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Lança
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 180;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Ferradura                        i = 20
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 250;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Arco e Flechas
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 250;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	//Machado e Árvore
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 240;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Fogueira na grama
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 280;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	//Fogueira na cidade
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 320;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	// ?                                  i = 25
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 140;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	// ? com X
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 160;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
	// Porta com Portal
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 320;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	// Porta com Paisagem
	botoesI[ i ].x = 0;
	botoesI[ i ].y = 390;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	// Porta Fechada
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 390;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	// Manuscrito (grande)                      i = 30
	botoesI[ i ].x = 70;
	botoesI[ i ].y = 320;
	botoesI[ i ].w = 70;
	botoesI[ i ].h = 70;
	i++;
	// O -> O + O
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 360;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	// O + O -> O
	botoesI[ i ].x = 160;
	botoesI[ i ].y = 400;
	botoesI[ i ].w = 40;
	botoesI[ i ].h = 40;
	i++;
	// Botão vazio (pequeno)
	botoesI[ i ].x = 140;
	botoesI[ i ].y = 180;
	botoesI[ i ].w = 20;
	botoesI[ i ].h = 20;
	i++;
}

//------------------------------------------------------------------------------

int botao( int x, int y, int imagem, int id )
{
	if( id == 0 )
	{
		aplicar_superficie( x, y, botoesImagem, tela, &botoesI[imagem] );
	}
	else
	{
		if( evento.button.x > (( x * SCREEN_WIDTH )/1024) && evento.button.x < botoesI[imagem].w + (( x * SCREEN_WIDTH )/1024) &&\
		evento.button.y > (( y * SCREEN_HEIGHT )/768) && evento.button.y < botoesI[imagem].h + (( y * SCREEN_HEIGHT )/768) )
		{
			return id;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
