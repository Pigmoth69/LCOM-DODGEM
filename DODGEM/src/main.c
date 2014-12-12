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
	//test123();
	mainMenu();

	exit_DODGEM();
	return 0;
}
