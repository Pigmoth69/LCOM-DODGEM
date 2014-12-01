#include <stdio.h>
#include "DODGEM.h"
#include "graphics.h"
#include "utilities.h"
#include "vbe.h"
#include "bitmap.h"

#include <stdbool.h>





int main(int argc, char **argv) {
	srand(time(NULL));
	sef_startup();

	start_DODGEM();

	int x = 0;

	do
	{
		//drawBitmap(game->MenuImage,0,0,ALIGN_LEFT);
		show_mouse(100);
		x++;


	}while(x<200);
	//showMainMenu(game);


	//sleep(5);
	//exit_DODGEM(game);
	vg_exit();
	return 0;
}
