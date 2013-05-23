#include "AAA.h"

//------------------------------------------------------------------------------
/*
     strcpy(racas[i].nome,"?");
     racas[i].tempoCid = 3;
     racas[i].maxPop = 1;
     racas[i].crescimento = 1;
     racas[i].materiais = 1;
     racas[i].magia = 1;
     racas[i].treinamento = 1;
     racas[i].arco = 0;
     racas[i].lanca = 0;
     racas[i].montaria = 0;
     racas[i].ataque = 0;
     racas[i].defesa = 0;
     racas[i].dano = 0;
     racas[i].vida = 0;
     racas[i].movimento = 0;
     racas[i].penaVegetacao = 1;
     racas[i].penaRelevo = 1;
     racas[i].penaNeve = 1;
     racas[i].penaDeserto = 1;
     racas[i].elemento = ?;
*/

void preparar_raca()
{
	int i;
	
	for( i = 0; i < numRacas; i++ )
	{
		strcpy(racas[i].nome,"-Vazia-");
	}
	
	i = 0;
	strcpy(racas[i].nome,"Orc");
	racas[i].tempoCid = 2;
	racas[i].maxPop = 1;
	racas[i].cidDefesa = 1;
	racas[i].crescimento = 1;
	racas[i].materiais = 1;
	racas[i].magia = 0.5;
	racas[i].treinamento = 1.5;
	racas[i].arco = -1;
	racas[i].lanca = 0;
	racas[i].montaria = 0;
	racas[i].ataque = 0;
	racas[i].defesa = 0;
	racas[i].dano = 0;
	racas[i].vida = 2;
	racas[i].movimento = 0;
	racas[i].penaVegetacao = 1;
	racas[i].penaRelevo = 1;
	racas[i].penaNeve = 1;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 3;
	racas[i].crescTempIdeal = 6;
	
	i++;
	strcpy(racas[i].nome,"Elfo");
	racas[i].tempoCid = 3;
	racas[i].maxPop = 1;
	racas[i].cidDefesa = 1.2;
	racas[i].crescimento = 0.8;
	racas[i].materiais = 0.8;
	racas[i].magia = 1.5;
	racas[i].treinamento = 1;
	racas[i].arco = 1;
	racas[i].lanca = 0;
	racas[i].montaria = 0;
	racas[i].ataque = 0;
	racas[i].defesa = 0;
	racas[i].dano = 1;
	racas[i].vida = -2;
	racas[i].movimento = 0;
	racas[i].penaVegetacao = 0;
	racas[i].penaRelevo = 1;
	racas[i].penaNeve = 1;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 4;
	racas[i].crescTempIdeal = 4;
	
	i++;
	strcpy(racas[i].nome,"Morto-Vivo");
	racas[i].tempoCid = 3;
	racas[i].maxPop = 4;
	racas[i].cidDefesa = 1.2;
	racas[i].crescimento = 1.5;
	racas[i].materiais = 1.2;
	racas[i].magia = 1.2;
	racas[i].treinamento = 1;
	racas[i].arco = 0;
	racas[i].lanca = 0;
	racas[i].montaria = 0;
	racas[i].ataque = 0;
	racas[i].defesa = 0;
	racas[i].dano = 0;
	racas[i].vida = -5;
	racas[i].movimento = 1;
	racas[i].penaVegetacao = 1;
	racas[i].penaRelevo = 1;
	racas[i].penaNeve = 1;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 2;
	racas[i].crescTempIdeal = -1;
	
	i++;
	strcpy(racas[i].nome,"Humano");
	racas[i].tempoCid = 3;
	racas[i].maxPop = 1;
	racas[i].cidDefesa = 1.5;
	racas[i].crescimento = 1.2;
	racas[i].materiais = 1;
	racas[i].magia = 1;
	racas[i].treinamento = 1;
	racas[i].arco = 0;
	racas[i].lanca = 0;
	racas[i].montaria = 1;
	racas[i].ataque = 0;
	racas[i].defesa = 0;
	racas[i].dano = 0;
	racas[i].vida = 0;
	racas[i].movimento = 0;
	racas[i].penaVegetacao = 1;
	racas[i].penaRelevo = 1;
	racas[i].penaNeve = 1;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 0;
	racas[i].crescTempIdeal = 4;
	
	i++;
	strcpy(racas[i].nome,"Formigas");
	racas[i].tempoCid = 1;
	racas[i].maxPop = 100;
	racas[i].cidDefesa = 2;
	racas[i].crescimento = 10;
	racas[i].materiais = 0;
	racas[i].magia = 0;
	racas[i].treinamento = 0.5;
	racas[i].arco = -2;
	racas[i].lanca = -2;
	racas[i].montaria = -2;
	racas[i].ataque = 0;
	racas[i].defesa = 0;
	racas[i].dano = 0;
	racas[i].vida = -5;
	racas[i].movimento = 2;
	racas[i].penaVegetacao = 1;
	racas[i].penaRelevo = 1;
	racas[i].penaNeve = 1;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 1;
	racas[i].crescTempIdeal = 6;
	
	i++;
	strcpy(racas[i].nome,"Anões");
	racas[i].tempoCid = 2;
	racas[i].maxPop = 1;
	racas[i].cidDefesa = 2;
	racas[i].crescimento = 1;
	racas[i].materiais = 2;
	racas[i].magia = 0.5;
	racas[i].treinamento = 1;
	racas[i].arco = 0;
	racas[i].lanca = 0;
	racas[i].montaria = -1;
	racas[i].ataque = 0;
	racas[i].defesa = 1;
	racas[i].dano = 0;
	racas[i].vida = 0;
	racas[i].movimento = 0;
	racas[i].penaVegetacao = 1;
	racas[i].penaRelevo = 0;
	racas[i].penaNeve = 0;
	racas[i].penaDeserto = 1;
	racas[i].elemento = 1;
	racas[i].crescTempIdeal = 2;
}

//------------------------------------------------------------------------------
