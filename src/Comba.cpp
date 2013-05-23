#include "AAA.h"

//Heroes of Might and Magic
int combate( int atacante, int defensor )
{
	int cid;
	
	float dife;
	
	float atac;
	float atacDano;
	float atacVida;
	float atacQuant;
	float defe;
	float defeDano;
	float defeVida;
	float defeQuant;
	
	atacVida = tipos[unidades[atacante].tipo].vida;
	defeVida = tipos[unidades[defensor].tipo].vida;
	
	atacQuant = unidades[atacante].quantidade;
	defeQuant = unidades[defensor].quantidade;
	
	atac = tipos[unidades[atacante].tipo].ataque;
	//Defesa do defensor
	if( tipos[unidades[defensor].tipo].lanca > 0 && tipos[unidades[atacante].tipo].montaria > 0 && tipos[unidades[defensor].tipo].montaria == 0 )
	{
		defe = tipos[unidades[defensor].tipo].defesa * ( tipos[unidades[defensor].tipo].lanca + tipos[unidades[atacante].tipo].montaria );
	}
	else
	{
		defe = tipos[unidades[defensor].tipo].defesa;
	}
	cid = procurar_cid_xy( unidades[defensor].x, unidades[defensor].y );
	if( cid >= 0 && tipos[unidades[defensor].tipo].montaria == 0 )//Bonus de defesa da cidade para não montados
	{
		defe = defe * racas[tipos[unidades[defensor].tipo].raca].cidDefesa;
	}
	
	dife = atac - defe;
	
	//Dano do atacante
	if( dife > -10 )
	{
		atacDano = ( ( dife*10 + 100 ) * tipos[unidades[atacante].tipo].dano ) / 100;
		
		if( tipos[unidades[defensor].tipo].arco > 0 && tipos[unidades[atacante].tipo].arco == 0 )//Defesor é de alcance e está contra corpo-a-corpo
		{
		atacDano = atacDano * tipos[unidades[defensor].tipo].arco * 2;
		}
		
		if( tipos[unidades[defensor].tipo].montaria > 0 && tipos[unidades[atacante].tipo].lanca > 0 )
		{
		atacDano = atacDano * ( tipos[unidades[defensor].tipo].montaria + tipos[unidades[atacante].tipo].lanca );
		}
	}
	else
	{
		atacDano = tipos[unidades[atacante].tipo].dano / ((dife*-1)+1);
	}
	
	//Dano do defensor
	if( tipos[unidades[defensor].tipo].arco < tipos[unidades[atacante].tipo].arco )//Defesor tem menos alcance
	{
		defeDano = 0;
	}
	else
	{
		defeDano = tipos[unidades[defensor].tipo].dano;
		
		if( tipos[unidades[atacante].tipo].montaria > 0 && tipos[unidades[defensor].tipo].lanca > 0 )
		{
			defeDano = defeDano * ( tipos[unidades[atacante].tipo].montaria + tipos[unidades[defensor].tipo].lanca );
		}
	}
	
	defeQuant = ( ( defeQuant * defeVida ) - ( atacDano * atacQuant ) ) / defeVida;
	if( defeQuant < 0 )
	defeQuant = 0;
	
	atacQuant = ( ( atacQuant * atacVida ) - ( defeDano * (defeQuant*3+unidades[defensor].quantidade-defeQuant)/4 ) ) / atacVida;
	
	if( defeQuant < 0 ) defeQuant = 0;
	if( atacQuant < 0 ) atacQuant = 0;
	
	itoa( unidades[atacante].quantidade-(int)atacQuant, aux2, 10);
	strcpy( aux, aux2 );
	strcat( aux, "/" );
	itoa( unidades[defensor].quantidade-(int)defeQuant, aux2, 10);
	strcat( aux, aux2 );
	escrever( (unidades[atacante].x+unidades[defensor].x)*35+20-telaX, (unidades[atacante].y+unidades[defensor].y)*35+20-telaY, aux, fonte20, corVermelha );
	SDL_Flip( tela );
	SDL_Delay( 1000 );
	
	unidades[atacante].quantidade = (int)atacQuant;
	unidades[defensor].quantidade = (int)defeQuant;
	
	if( atacQuant <= 0 )
	{
		eliminar_pelotao( atacante );
		/*preencher_fundo();
		strcpy( aux, "É a vez de " );
		strcat( aux, "1" );
		escrever( 400, 400, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 1000 );*/
	}
	if( defeQuant <= 0 ) 
	{
		eliminar_pelotao( defensor );
			/*preencher_fundo();
		strcpy( aux, "É a vez de " );
		strcat( aux, "2" );
		escrever( 400, 400, aux, fonte20, corVermelha );
		SDL_Flip( tela );
		SDL_Delay( 1000 );*/
	}
	
	if( atacQuant > 0 && defeQuant <= 0 ) return 2;
	if( atacQuant > 0 ) return 1;
	if( atacQuant <= 0 ) return 0;
}
