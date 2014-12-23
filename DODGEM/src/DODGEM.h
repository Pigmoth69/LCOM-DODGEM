#ifndef DODGEM_H_
#define DODGEM_H_


#include "bitmap.h"

typedef struct{
	int xi;
	int xf;
	int yi;
	int yf;
	int direction;
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
	Bitmap* CursorLR;
	Bitmap* CursorLRM;
	Bitmap* CursorMiddle;
	rectangle * PlayOption;
	rectangle * HSOption;
	rectangle * ExitOption;
	rectangle * gameMenuOption;
	rectangle * submitScore;

	rectangle * TL;
	rectangle * TR;
	rectangle * BL;
	rectangle * BR;

	rectangle * MainSquare;

	int FPS;
	int irq_set_mouse;
	int irq_set_keyboard;
	int irq_set_time;
}DODGEM;

extern DODGEM * game;


void StartOptions();
void start_DODGEM();
void start_Objects();
void exit_DODGEM();
int mainMenu(); //return the option chosen
void test123();
int checkMenuOption(); //see if the user clicked any option from menu. 0(None), 1(Play), 2(HS), 3(Exit)
int gameMenu(); //menu de jogo
int highscoreMenu(); // menu de pontuações
int exitMenu(); //sair do jogo
int checkGameOption(); //verificar a opção de jogo escolhida (juntamente com os powers)
int playGame(); //função que permite jogar o jogo
void UpdateObjPosition(); //atualiza a posicao dos objetos


#endif
