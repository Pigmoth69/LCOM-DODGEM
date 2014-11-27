#include "sprite.h"
#include "asprite.h"
#include <stdio.h>




Sprite * create_sprite(char *pic[])
{
	//allocate space for the "object"
	Sprite	*sp = (Sprite*) malloc ( sizeof(Sprite));

	if( sp == NULL)
		return NULL;

	// read the sprite pixmap
	sp->map = (char*)read_xpm(pic, &(sp->width), &(sp->height));

	if( sp->map == NULL )
	{
		free(sp);
		return NULL;
	}


	return sp;
}

void destroy_sprite(Sprite *sp, char *base) {
	if( sp == NULL )
		return;

	free(sp->map);
	free(sp);
	sp = NULL; // hopeless: pointer is passed by value
}
