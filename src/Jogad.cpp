#include "AAA.h"

//------------------------------------------------------------------------------

void preparar_jogadores()
{
	int i;
	
	for( i = 0; i < numJogadores; i++ )
	{
		jogadores[i].cor = i;
		jogadores[i].raca = 0;
		strcpy(jogadores[i].nome," ");
		jogadores[i].materiais = 1000;
		jogadores[i].mana = 1000;
		jogadores[i].populacao = 10000;
		jogadores[i].x = i*4;
		jogadores[i].y = i*4;
	}
	
	i = 0;
	strcpy(jogadores[i].nome,"Burtuk");
	jogadores[i].raca = 0;
	
	i++;
	strcpy(jogadores[i].nome,"Ilmiol");
	jogadores[i].raca = 1;
	
	i++;
	strcpy(jogadores[i].nome,"Altior");
	jogadores[i].raca = 2;
	
	i++;
	strcpy(jogadores[i].nome,"Caminion");
	jogadores[i].raca = 3;
}

//------------------------------------------------------------------------------

void desenhar_infos_jogador( int x, int y, jogador jog )
{
	strcpy( aux, "Jogador: " );
	strcat( aux, jog.nome );
	escrever( x, y, aux );
	strcpy( aux, "Materiais: " );
	itoa( jog.materiais, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+13, aux );
	strcpy( aux, "Mana: " );
	itoa( jog.mana, aux2, 10);
	strcat( aux, aux2);
	escrever( x, y+26, aux );
}

//------------------------------------------------------------------------------
