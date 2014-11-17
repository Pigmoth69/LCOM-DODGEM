#include "timer.h"
#include "keyboard.h"
#include "vbe.h"

unsigned long keyboard = 0x00;
int bts =0;

static char *video_mem;

void *test_init(unsigned short mode, unsigned short delay) {

	video_mem = vg_init(mode);

	if(video_mem == 0)
	{
		printf("ERRO\n");
		return 0;
	}

	timer_test_int(delay);


	vg_exit();
	printf("Memory 0x%x\n",video_mem);

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

	if(x+size > MODE1024_H_RES||y+size>MODE1024_V_RES)
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
								return 1; //caso seja de 2 bytes passa ao proximo ciclo
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


//tail -f /usr/log/messages

		vg_exit();
		return 0;


}

int test_line(unsigned short xi, unsigned short yi, 
		           unsigned short xf, unsigned short yf, unsigned long color) {
	


		if(xi<0||xf<0||yi<0||yf<0)
		{
			printf("Erro nas coordenadas\n");
			return 1;
		}


		char *PointerRam;
		if((PointerRam=(char*)vg_init(MODE1024))==0)
			{
				printf("ERRO\n");
				return 0;
			}
		float declive;
		if(xf-xi <0 || yf-yi<0)
		{


		}
		else
		{
			if(xf-xi>yf-yi)
			{
				declive = (yf-yi)/(xf-xi);
				int i=0;
				//for(i;i< )



			}
			else
			{

			}
		}











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
							return 1; //caso seja de 2 bytes passa ao proximo ciclo
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


		//tail -f /usr/log/messages

		vg_exit();
		return 0;

	
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	
	/* To be completed */
	
}	

int test_move(unsigned short xi, unsigned short yi, char *xpm[], 
				unsigned short hor, short delta, unsigned short time) {
	
	/* To be completed */
	
}					


