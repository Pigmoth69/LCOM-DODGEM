#ifndef DODGEM_H_
#define DODGEM_H_


#include "bitmap.h"

typedef struct{
	int xi;
	int xf;
	int yi;
	int yf;
}rectangle;


typedef struct{
	Bitmap *MenuImage;
	Bitmap* GameField;
	Bitmap* PlaySquare;
	Bitmap* Enemy1;
	Bitmap* Enemy2;
	Bitmap* Enemy3;
	Bitmap* Enemy4;
	Bitmap* Cursor;
	Bitmap* CursorLeft;
	Bitmap* CursorRight;
	rectangle * PlayOption;
	rectangle * HSOption;
	rectangle * ExitOption;

	int FPS;
	int irq_set_mouse;
	int irq_set_keyboard;
	int irq_set_time;
}DODGEM;

extern DODGEM * game;


void StartOptions();
void start_DODGEM();
void exit_DODGEM();
void mainMenu();
void test123();
#endif
