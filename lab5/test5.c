#include "timer.h"
#include "keyboard.h"
#include "vbe.h"
#include "pixmap.h"
#include "sprite.h"
#include "asprite.h"


unsigned long keyboard = 0x00;
int bts =0;

static char *video_mem;


int leave_event()
{
	int ipc_status;
	int r;
	message msg;
	int irq_set;

	if(( irq_set = KBD_subscribe_int())== -1)
		return -1;

	while(keyboard != ESC_BREAK_CODE) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set)
				{ /* subscribed interrupt */

					sys_inb(OUT_BUF, &keyboard);// vai à porta buscar e coloca-o em &keyboard
					printf("%x\n", keyboard);
					if (keyboard == TWO_BYTES) // verifica se o endereço da tecla possui 2 bytes
					{
						bts = 1; //coloca a variavel bts a 1 para mais tarde ver se o endereço é de 2 bytes
					}

					if (bts == 1) //caso tenha 2 bytes
					{
						if ((keyboard & BIT_SIG_0) == keyboard) //verifica se é makecode ou breakcode (BIT mais significativo a 1 ou 0
						{
							bts = 0;
						}
						else
						{
							bts = 0;
						}
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(KBD_unsubscribe_int()!= 1)
		return -1;

	return 0;

}

void set_pixel(unsigned short x, unsigned short y, unsigned long color)
{
	char *pointer;

	pointer = video_mem;

	pointer += MODE1024_H_RES*y+x;

	*pointer=(char)color;

}

void line(unsigned short xi, unsigned short yi,unsigned short xf, unsigned short yf, unsigned long color)
{
	double declive;
	int i=0;

		if(xi == xf && xi == yi && xi == yf && xf == yi && xf == yf && yi == yf)
		{
			set_pixel(xi,yi,color);
		}
		else
		{

			if(xf-xi ==0)
			{
	                if(yf-yi>0)
	                {
	                        for(i;i< yf-yi;i++)
	                                set_pixel(xi,yi+i,color);
	                }else
	                {
	                        for(i;i< yi-yf;i++)
	                                set_pixel(xi,yf+i,color);
	                }
	        }
	        else if(yf-yi==0)
	        {
	                if(xf-xi>0)
	                {
	                        for(i;i< xf-xi;i++)
	                                set_pixel(xi+i,yi,color);
	                }else
	                {
	                        for(i;i< xi-xf;i++)
	                                set_pixel(xf+i,yf,color);
	                }
	        }else if((declive = (double)(yf-yi)/(double)(xf-xi))> 0)
	        {
        		int b = yi-declive*xi;

	        	if(xf-xi > 0 && yf-yi > 0)
	        	{
	        		if(xf-xi > yf-yi)
	        		{
	        		for(i; i<xf-xi;i++)
	        			set_pixel(xi+i,(int)(declive*(xi+i)+b),color);
	        		}
	        		else
	        		{
	        			for(i; i<yf-yi;i++)
	        				set_pixel((int)((yi+i-b)/declive),yi+i,color);
	        		}
	        	}
	        	else
	        	{
	        		if(xi-xf > yi-yf)
	        		{
	        			for(i; i<xi-xf;i++)
	        				set_pixel(xf+i,(int)(declive*(xf+i)+b),color);
	        		}
	        		else
	        		{
	        			for(i; i<yi-yf;i++)
	        				set_pixel((int)((yf+i-b)/declive),yf+i,color);
	        		}
	        	}
	        }
	        else		//declive negativo!
	        {
	        	int b = yi-declive*xi;

	        	if(xf-xi > 0 && yf-yi <0)
	        	{
	        		if(abs(xf-xi) > abs(yf-yi))
	        		{
	        			for(i; i < abs(xf-xi);i++)
	        				set_pixel(xf-i,(int)(declive*(xf-i)+b),color);
	        		}else
	        		{
	        			for(i; i < abs(yf-yi);i++)
	        				set_pixel((int)((yf+i-b)/declive),yf+i,color);
	        		}

	        	}else
	        	{
	        		if(abs(xf-xi) > abs(yf-yi))
	        		{
	        			for(i; i < abs(xf-xi);i++)
	        				set_pixel(xi-i,(int)(declive*(xi-i)+b),color);
	        		}else
	        		{
	        			for(i; i < abs(yf-yi);i++)
	        				set_pixel((int)((yi+i-b)/declive),yi+i,color);
	        		}
	        	}
	        }
		}

}

void *test_init(unsigned short mode, unsigned short delay) {

	video_mem = (char *)vg_init(mode);

	if(video_mem == 0)
	{
		printf("ERRO\n");
		return 0;
	}

	timer_test_int(delay);

	vg_exit();
	printf("VIRTUAL ADDRESS: 0x%x\n",video_mem);

}

void vg_fill(unsigned short mode,unsigned long color)
{
	int hres,vres;

	switch(mode){

	case 0x101 :
		hres=MODE640_H_RES;
		vres=MODE640_V_RES;
		break;

	case 0x103 :
		hres=MODE800_H_RES;
		vres=MODE800_V_RES;
		break;

	case 0x105 :
		hres=MODE1024_H_RES;
		vres=MODE1024_V_RES;
		break;
	case 0x107 :
		hres=MODE1280_H_RES;
		vres=MODE1280_V_RES;
		break;

	}

	size_t x, y;
	for(x = 0; x < hres; x++)
	{
		for(y = 0; y < vres; y++)
		{
			set_pixel(x, y, color);
		}
	}
}

int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	
	char *PointerRam;
	if(size==0)
	{
		printf("INVALID SIZE!\n");
		return -1;
	}

	if((PointerRam=(char*)vg_init(MODE1024))==0)
		{
			printf("ERRO\n");
			return 0;
		}

	if(x+size >= MODE1024_H_RES||y+size>=MODE1024_V_RES)
	{
		vg_exit();
		printf("writing ouf of memory\n");
		return 0;
	}


		PointerRam += MODE1024_H_RES*y+x;


	int i=0;
	int c=0;

	for(i;i<size;i++)
	{
		for(c;c<size;c++)
		{
			*PointerRam=(char)color;
			PointerRam++;
		}
		c=0;
		PointerRam+=(MODE1024_H_RES-size);
	}



	if(leave_event() == -1)
	{
		vg_exit();
		printf("Error leaving event!\n");
		return -1;
	}



	//tail -f /usr/log/messages

	vg_exit();
	return 0;

}

int test_line(unsigned short xi, unsigned short yi, 
		           unsigned short xf, unsigned short yf, unsigned long color) {



	if((video_mem=(char*)vg_init(MODE1024))==0)
	{
		vg_exit();
		printf("ERRO vg_init(MODE1024)\n");
		return 0;
	}

	if(xf >= MODE1024_H_RES || yf >= MODE1024_V_RES || yi >= MODE1024_V_RES || xi >= MODE1024_H_RES)
	{
		vg_exit();
		printf("writing ouf of memory\n");
		return 0;
	}

	if((xi==0 && yi==0 && xf==0 && yf==0)| yf<0 || yi<0 || xf<0 || xi<0)
	{
		vg_exit();
		printf("Invalid xi/xf/yi/yf\n");
		return -1;
	}


	line(xi,yi,xf,yf,color);

	if(leave_event() == -1)
	{
		vg_exit();
		printf("Error leaving event!\n");
		return -1;
	}



	//tail -f /usr/log/messages

	vg_exit();
	return 0;
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	
	char *PointerRam;

		if((PointerRam= video_mem = (char*)vg_init(MODE1024))==0)
			{
			printf("ERRO\n");
			return -1;
			}

		Sprite *sp;
		if((sp =create_sprite(xpm,PointerRam))==NULL)
		{
			vg_exit();
			printf("Invalid sprite!\n");
			return 0;
		}



		if(xi+(sp->width) >= MODE1024_H_RES||yi+(sp->height)>=MODE1024_V_RES)
		{
			vg_exit();
			printf("writing ouf of screen bounds\n");
			return 0;
		}


		PointerRam += MODE1024_H_RES*yi+xi;

		int i = 0;
		int x = 0;
		int z = 0;

		for(i; i < (sp->height);i++)
		{
			for(x;x < (sp->width);x++)
			{
				*PointerRam=(sp->map)[z];
				PointerRam++;
				z++;
			}
			x=0;
			PointerRam+=(MODE1024_H_RES-(sp->width));
		}

		if(leave_event() == -1)
		{
			vg_exit();
			printf("Error leaving event!\n");
			return -1;
		}



	//tail -f /usr/log/messages

			vg_exit();
			return 0;
	
}	

int test_move(unsigned short xi, unsigned short yi, char *xpm[], 
				unsigned short hor, short delta, unsigned short time) {
	
	





	if(leave_event() == -1)
			{
				vg_exit();
				printf("Error leaving event!\n");
				return -1;
			}



		//tail -f /usr/log/messages

				vg_exit();
				return 0;

}

int test_controller() {

	/* To be completed */

}






