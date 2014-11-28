#include "graphics.h"
#include "utilities.h"
#include "minix/syslib.h"
#include "bitmap.h"

static short *video_mem;

short * getVideoBuffer()
{
	return video_mem;
}

void graphicsStart(unsigned short mode)
{
	video_mem =(short*)vg_init(mode);
	Bitmap* teste;
	teste= loadBitmap("/home/lcom/DODGEM/res/images/Untitled.bmp");
	drawBitmap(teste,0,0,ALIGN_LEFT);
}

void graphicsExit()
{

	vg_exit();
}

void set_pixel(unsigned short x, unsigned short y, unsigned long color) {
	*(video_mem + x + y * MODE1024_H_RES) = color;
}


void graphics_fill(unsigned long color) {

	int x, y;
	for (y = 0; y < MODE1024_V_RES; y++)
		for(x=0; x < MODE1024_H_RES;x++)
			set_pixel(x,y,color);
}
