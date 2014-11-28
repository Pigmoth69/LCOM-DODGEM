#include <stdio.h>
#include "graphics.h"
#include "utilities.h"
#include "vbe.h"
#include "bitmap.h"
#include "DODGEM.h"





int main(int argc, char **argv) {
	srand(time(NULL));
	sef_startup();

	/*VESA graphics modes 16bits
	 *
	 * 1024x768 -0x117
	 *
	 *
	 */

	graphicsStart(MODE1024);
	//graphics_fill(WHITE);
	sleep(5);
	graphicsExit();
	return 0;
}
