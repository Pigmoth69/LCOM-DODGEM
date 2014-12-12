#include "DODGEM.h"
#include "bitmap.h"
#include "utilities.h"
#include "keyboard.h"
#include "video_gr.h"
#include "graphics.h"
#include "mouse.h"
#include "timer.h"

DODGEM * game;

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
	game->Cursor = loadBitmap("/home/lcom/DODGEM/res/images/mouse.bmp");
	game->CursorLeft = loadBitmap("/home/lcom/DODGEM/res/images/mouseLeftButton.bmp");
	game->CursorRight = loadBitmap("/home/lcom/DODGEM/res/images/mouseRightButton.bmp");
	game->irq_set_mouse = MOUSE_send_command();
	game->irq_set_keyboard = KBD_subscribe_int();
	game->irq_set_time = timer_subscribe_int();
	game->FPS = 60;
	StartOptions();
	StartMouse();
}

void StartOptions(){
	game->PlayOption = malloc(sizeof(rectangle));
	game->HSOption = malloc(sizeof(rectangle));
	game->ExitOption = malloc(sizeof(rectangle));

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

void mainMenu()
{
	timer_set_square(0, 60);

	int ipc_status;
	int r;
	message msg;
	unsigned long keyboard = 0x0;


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
					printf("subscreve timer \n");

					if (getCounter() % (60/game->FPS) == 0){
						printf("int \n");
						drawBitmap(game->MenuImage, 0, 0, ALIGN_LEFT);
						drawMouse();
						memcpy(getVideoMem(), getVideoBuffer(), MODE1024_H_RES * MODE1024_V_RES * 2);
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

				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
}

