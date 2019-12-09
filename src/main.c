#include <genesis.h>

#include "music.h"
#include "states.h"

int main()
{
    mainStates = INTRO;

    SND_startPlay_XGM(intro_mus);

    while(1)
	{
		VDP_waitVSync();
	}
	return 0;
}