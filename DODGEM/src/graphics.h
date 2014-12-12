#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "DODGEM.h"



void graphicsStart(unsigned short mode);
void graphicsExit();
void graphics_fill(unsigned long color);
void set_pixel(unsigned short x, unsigned short y, unsigned long color);
short *getVideoBuffer();
short *getVideoMem();
void showMainMenu(DODGEM *game);



#endif
