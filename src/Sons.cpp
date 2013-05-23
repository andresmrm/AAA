#include "AAA.h"

//The music that will be played
//Mix_Music *click = NULL;
//Mix_Chunk *click2 = NULL;

int carregar_sons()
{
	click = Mix_LoadMUS( "human2.mid" );
	//if( click == NULL ) { exit(0); }
	
	//click2 = Mix_LoadWAV( "click.ogg" );
	//if( click2 == NULL ) { exit(0); }
}
