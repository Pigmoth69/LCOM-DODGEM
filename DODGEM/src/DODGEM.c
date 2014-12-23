#include "DODGEM.h"
#include "bitmap.h"
#include "utilities.h"
#include "keyboard.h"
#include "video_gr.h"
#include "graphics.h"
#include "mouse.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

DODGEM * game;

int xpos =500;
int ypos =100;
int direcao1 = 1;
int direcao2 = 1;

void test123(){
	drawBitmap(game->GameField, 0, 0, ALIGN_LEFT);
	//drawBitmap(game->MenuImage, 0, 0, ALIGN_LEFT);
	memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);
	sleep(5);
}

void start_DODGEM()
{
	game = malloc(sizeof(DODGEM));
	graphicsStart(MODE1024);
	game->MenuImage= loadBitmap("/home/lcom/DODGEM/res/images/MenuPrincipal.bmp");
	game->GameField= loadBitmap("/home/lcom/DODGEM/res/images/MenuGame.bmp");
	game->PlaySquare= loadBitmap("/home/lcom/DODGEM/res/images/MainSquare.bmp");
	game->Enemy1= loadBitmap("/home/lcom/DODGEM/res/images/squareBL.bmp");
	game->Enemy2= loadBitmap("/home/lcom/DODGEM/res/images/squareBR.bmp");
	game->Enemy3= loadBitmap("/home/lcom/DODGEM/res/images/squareTL.bmp");
	game->Enemy4= loadBitmap("/home/lcom/DODGEM/res/images/squareTR.bmp");
	game->Cursor = loadBitmap("/home/lcom/DODGEM/res/images/rato20.bmp");
	game->CursorLeft = loadBitmap("/home/lcom/DODGEM/res/images/rato20L.bmp");
	game->CursorRight = loadBitmap("/home/lcom/DODGEM/res/images/rato20R.bmp");
	game->CursorLR = loadBitmap("/home/lcom/DODGEM/res/images/rato20LR.bmp");
	game->CursorLRM = loadBitmap("/home/lcom/DODGEM/res/images/rato20LRM.bmp");
	game->CursorMiddle = loadBitmap("/home/lcom/DODGEM/res/images/rato20M.bmp");
	game->irq_set_mouse = MOUSE_send_command();
	game->irq_set_keyboard = KBD_subscribe_int();
	game->irq_set_time = timer_subscribe_int();
	game->FPS = 60;
	StartOptions();
	start_Objects();
	StartMouse();
}

void StartOptions(){
	game->PlayOption = malloc(sizeof(rectangle));
	game->HSOption = malloc(sizeof(rectangle));
	game->ExitOption = malloc(sizeof(rectangle));
	game->gameMenuOption = malloc(sizeof(rectangle));
	game->submitScore = malloc(sizeof(rectangle));

	game->PlayOption->xi = 340;
	game->PlayOption->xf = 684;
	game->PlayOption->yi = 256;
	game->PlayOption->yf = 334;

	game->HSOption->xi = game->PlayOption->xi;
	game->HSOption->xf = game->PlayOption->xf;
	game->HSOption->yi = 338;
	game->HSOption->yf = 416;

	game->ExitOption->xi = game->PlayOption->xi;
	game->ExitOption->xf = game->PlayOption->xf;
	game->ExitOption->yi = 420;
	game->ExitOption->yf = 496;

	game->gameMenuOption->xi = 55;
	game->gameMenuOption->xf = 175;
	game->gameMenuOption->yi = 55;
	game->gameMenuOption->yf = 95;

	game->submitScore->xi=55;
	game->submitScore->xf=295;
	game->submitScore->yi=685;
	game->submitScore->yf=745;


}

void start_Objects(){
	game->TL = malloc(sizeof(rectangle));
	game->TR = malloc(sizeof(rectangle));
	game->BL = malloc(sizeof(rectangle));
	game->BR = malloc(sizeof(rectangle));

	game->TL->xi = 400;
	game->TL->xf = 480;
	game->TL->yi = 100;
	game->TL->yf = 180;

	game->TR->xi = 750;
	game->TR->xf = 850;
	game->TR->yi = 100;
	game->TR->yf = 160;

	game->BL->xi = 470;
	game->BL->xf = 510;
	game->BL->yi = 490;
	game->BL->yf = 600;

	game->BR->xi = 730;
	game->BR->xf = 900;
	game->BR->yi = 470;
	game->BR->yf = 520;

	game->MainSquare->xi = 615;
	game->MainSquare->xf = 685;
	game->MainSquare->yi = 315;
	game->MainSquare->yf = 385;
}

void exit_DODGEM()
{
	deleteBitmap(game->MenuImage);
	deleteBitmap(game->GameField);
	deleteBitmap(game->PlaySquare);
	deleteBitmap(game->Enemy1);
	deleteBitmap(game->Enemy2);
	deleteBitmap(game->Enemy3);
	deleteBitmap(game->Enemy4);
	deleteBitmap(game->Cursor);
	game->irq_set_mouse = MOUSE_unsubscribe_int();
	game->irq_set_keyboard = KBD_unsubscribe_int();
	game->irq_set_time = timer_unsubscribe_int();
	graphicsExit();
}

int mainMenu()
{
	timer_set_square(0, 60);

	int ipc_status;
	int r;
	message msg;
	unsigned long keyboard = 0x0;
	int firstMove = 0;


	drawBitmap(game->MenuImage, 0, 0, ALIGN_LEFT);
	memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);

	while(keyboard!= ESC_KEY) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & game->irq_set_time)
				{ /* subscribed interrupt */
					timer_int_handler();

					if (getCounter() % (60/game->FPS) == 0){

						//if (firstMove > 2){
							drawBitmap(game->MenuImage, 0, 0, ALIGN_LEFT);
							drawMouse();
							memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);
							int option = 0;
							option = checkMenuOption();
							if (option == 1 || option == 2 || option == 3)
								return option;
						//}
					}
				}
				if (msg.NOTIFY_ARG & game->irq_set_keyboard)
				{ /* subscribed interrupt */
					keyboard = KBD_handler_C();
				}
				if (msg.NOTIFY_ARG & game->irq_set_mouse)
				{ /* subscribed interrupt */
					MOUSE_int_handler();
					show_mouse();
//					if (firstMove < 3)
//						firstMove++;

				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 3;
}

int checkMenuOption(){
	if (rato->x < game->PlayOption->xi || rato->x > game->PlayOption->xf)
		return 0;
	if (rato->y < game->PlayOption->yi || rato->y > game->ExitOption->yf)
		return 0;

	if (rato->y < game->PlayOption->yf)
	{
		if ((rato->button == 1) && (rato->lastButton != 1))
			return 1;
		else
			return 0;
	}
	else if (rato->y > game->HSOption->yi && rato->y < game->HSOption->yf)
	{
		if ((rato->button == 1) && (rato->lastButton != 1))
					return 2;
				else
					return 0;
	}
	else if (rato->y > game->ExitOption->yi && rato->y < game->ExitOption->yf)
	{
		if ((rato->button == 1) && (rato->lastButton != 1))
					return 3;
				else
					return 0;
	}
	else
	{
		return 0;
	}


}

int gameMenu() // esta função tem os menus de jogo todos juntamente com os powerups(talvez) e tem e a chamada à função de jogo!
{
	timer_set_square(0, 60);

	int ipc_status;
	int r;
	message msg;
	unsigned long keyboard = 0x0;
	int firstMove = 0;


	drawBitmap(game->GameField, 0, 0, ALIGN_LEFT);
	memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);

	while(keyboard!= ESC_KEY) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & game->irq_set_time)
				{ /* subscribed interrupt */
					timer_int_handler();

					if (getCounter() % (60/game->FPS) == 0){

						//if (firstMove > 2){
							drawBitmap(game->GameField, 0, 0, ALIGN_LEFT);
							drawMouse();
							//CENAS DE CODIGO
							printf("cenas\n");
							drawSquares();

							//CENAS DE CODIGO

							memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);


							if (checkGameOption() == 1)
								keyboard = ESC_KEY;
							if(checkGameOption() == 2)
							{
								highscoreMenu();
								keyboard = ESC_KEY;
							}


						//}
					}
				}
				if (msg.NOTIFY_ARG & game->irq_set_keyboard)
				{ /* subscribed interrupt */
					keyboard = KBD_handler_C();
				}
				if (msg.NOTIFY_ARG & game->irq_set_mouse)
				{ /* subscribed interrupt */
					MOUSE_int_handler();
					show_mouse();
//					if (firstMove < 3)
//						firstMove++;
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	xpos =350;
	ypos =300;
	printf("gameMenu()\n");
	return 1;
}

int checkGameOption()
{
	if((rato->x > game->gameMenuOption->xi) && (rato->x < game->gameMenuOption->xf)&&
			(rato->y > game->gameMenuOption->yi) && (rato->y < game->gameMenuOption->yf))
	{
		if ((rato->button == 1) && (rato->lastButton != 1))
		{
			printf("MainMenuButton\n");
			return 1;
		}
		else
			return 0;
	}
	else if((rato->x > game->submitScore->xi) && (rato->x < game->submitScore->xf)&&
			(rato->y > game->submitScore->yi) && (rato->y < game->submitScore->yf))
	{
		if ((rato->button == 1) && (rato->lastButton != 1))
		{
			printf("submitScore\n");
			return 2;
		}
		else
			return 0;
	}

}

int highscoreMenu() // esta função chama o menu de highscores
{
	printf("highscoreMenu()\n");
	return 2;
}

int exitMenu()	//esta função faz exit de tudo
{
	printf("exitMenu()\n");
	return 3;
}



int playGame()
{
	timer_set_square(0, 60);

		int ipc_status;
		int r;
		message msg;
		unsigned long keyboard = 0x0;
		int firstMove = 0;


		drawBitmap(game->GameField, 0, 0, ALIGN_LEFT);
		memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);

		while(keyboard!= ESC_KEY) {
			/* Get a request message. */
			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
			{
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & game->irq_set_time)
					{ /* subscribed interrupt */
						timer_int_handler();

						if (getCounter() % (60/game->FPS) == 0){

							//if (firstMove > 2){
								drawBitmap(game->GameField, 0, 0, ALIGN_LEFT);
								drawMouse();
								//printf("cenas\n");
								//drawSquares();

								memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);

								if (checkGameOption() == 1)
									keyboard = ESC_KEY;
								if(checkGameOption() == 2)
								{
									highscoreMenu();
									keyboard = ESC_KEY;
								}


							//}
						}
					}
					if (msg.NOTIFY_ARG & game->irq_set_keyboard)
					{ /* subscribed interrupt */
						keyboard = KBD_handler_C();
					}
					if (msg.NOTIFY_ARG & game->irq_set_mouse)
					{ /* subscribed interrupt */
						MOUSE_int_handler();
						show_mouse();
	//					if (firstMove < 3)
	//						firstMove++;
					}

					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}
		printf("gameMenu()\n");
		return 1;
}

void drawSquares()
{
	/*Area jogo -> x[350, 950]; y[50, 650]*/
	/*squareBL -> x[470, 510]; y[490, 600]*/
	printf("drawSquare()\n");
	int rand(void);
	time_t t;
	srand(time(NULL));
	int x = rand()%1+1;
	if(x==1)
		x=1;
	else
		x=-1;
	int vel1 =  6*x;
	int vel2 = 6*x;

	switch(direcao1)
	{
	case 1:
	{

		if(xpos+40 < 950 && ypos > 50)
		{
			switch(direcao2){
			case 1:
			{
				drawBitmap(game->Enemy1, xpos, ypos, ALIGN_LEFT);
				xpos+=vel1;
				ypos+=vel2;
				if(ypos+110 >= 650)
					direcao2=-1;
				break;

			}
			case -1:
			{
				drawBitmap(game->Enemy1, xpos, ypos, ALIGN_LEFT);
				xpos+=vel1;
				ypos-=vel2;
				break;

			}
			}

		}
		else
		{
			drawBitmap(game->Enemy1, xpos-vel1, ypos-vel2, ALIGN_LEFT);
			direcao2 = 1;
			direcao1 =-1;
			printf("case=-1\n");

		}
		break;
	}
	case -1:
	{
		printf("erro no case-1\n");
		switch(direcao2)
		{
		case 1:
		{
			drawBitmap(game->Enemy1, xpos, ypos, ALIGN_LEFT);
			xpos-=vel1;
			ypos-=vel2;
			if(ypos < 50)
				direcao2=-1;
			break;

		}
		case -1:
		{
			printf("erro no case -1 da segunda\n");
			drawBitmap(game->Enemy1, xpos, ypos, ALIGN_LEFT);
			xpos-=vel1;
			ypos+=vel2;
			if(xpos < 350)
			{
				direcao1 = 1;
				direcao2 = 1;
			}
			break;

		}
		}


	}

	}




}




