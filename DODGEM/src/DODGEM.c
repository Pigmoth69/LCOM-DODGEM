#include "DODGEM.h"
#include "bitmap.h"
#include "utilities.h"
#include "keyboard.h"
#include "video_gr.h"
#include "graphics.h"
#include "mouse.h"



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
	//game->irq_set_mouse = MOUSE_subscribe_int();
	//game->irq_set_keyboard = KBD_subscribe_int();
	//game->irq_set_time =;
}

void exit_DODGEM(DODGEM *game)
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
	graphicsExit();
}
/*
void showMainMenu(DODGEM *game)
{
	drawBitmap(game->MenuImage, 0, 0, ALIGN_LEFT);
}
*/
