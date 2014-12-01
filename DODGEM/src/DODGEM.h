#ifndef DODGEM_H_
#define DODGEM_H_


#include "bitmap.h"

typedef struct{
	Bitmap *MenuImage;
	Bitmap* GameField;
	Bitmap* PlaySquare;
	Bitmap* Enemy1;
	Bitmap* Enemy2;
	Bitmap* Enemy3;
	Bitmap* Enemy4;
	Bitmap* Cursor;

	int irq_set_mouse;
	int irq_set_keyboard;
	int irq_set_time;
}DODGEM;

DODGEM DODGEM_t;


void start_DODGEM(DODGEM  *game);
void exit_DODGEM(DODGEM *game);
//void showMainMenu(DODGEM *game);
#endif
