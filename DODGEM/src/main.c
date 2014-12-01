#include <stdio.h>
#include "DODGEM.h"
#include "graphics.h"
#include "utilities.h"
#include "vbe.h"
#include "bitmap.h"

#include <stdbool.h>





int main(int argc, char **argv) {
	bool correr =true;
	srand(time(NULL));
	sef_startup();



	//load DODGEM
	DODGEM *game = malloc(sizeof(DODGEM));
	start_DODGEM(game);



/*
	do
	{


			//graphics_fill(WHITE);
			sleep(5);

	}while(correr);*/
	//showMainMenu(game);

	drawBitmap(game->MenuImage,0,0,ALIGN_LEFT);
	sleep(5);
	//exit_DODGEM(game);
	vg_exit();
	return 0;
}
