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
	int MainOption = mainMenu();


	exit_DODGEM();
	printf("O Utilizador escolheu a opcao %d: ", MainOption);
	if (MainOption == 1)
		printf("PLAY \n");
	else if (MainOption == 2)
		printf("HIGHSCORES \n");
	else if (MainOption == 3)
		printf("EXIT \n");


	return 0;
}
