#include"i8042.h"
#include "DODGEM.h"
#include "video_gr.h"
#include "graphics.h"
#include "utilities.h"
#include "mouse.h"

int hook_id4 = 1;
//int bts = 0;

unsigned long mouse;
char mouse_char;

static unsigned int xcoord = MODE1024_H_RES/2;
static unsigned int ycoord = MODE1024_V_RES/2;

int MOUSE_subscribe_int() {

	int hook;
	hook = hook_id4;
	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE,
			&hook_id4) == OK)
		if (sys_irqenable(&hook_id4) == OK)
			return BIT(hook);

	return -1;
}

int MOUSE_unsubscribe_int() {
	if (sys_irqdisable(&hook_id4) == OK)
		if (sys_irqrmpolicy(&hook_id4) == OK)
			return 0;

	return 1;
}

int MOUSE_int_handler() {

	if (sys_inb(OUT_BUF, &mouse) != OK)
		return -1;
	mouse_char = (char)mouse;
	return 0;
}



int show_mouse(unsigned short cnt) {

	int x = 0;
	int ipc_status;
	int r;
	char packets[3];
	unsigned long resp;
	message msg;
	int irq_set;
	int contador = 0;

	//fazer funcao para activar stream mode


	if ((irq_set = MOUSE_subscribe_int()) == -1)
	{
		printf("cenas1");
		vg_exit();
		return -1;
	}

		if (sys_outb(KBC_CMD_REG, ENABLE_MOUSE) != OK)
		{
			printf("cenas2");
			vg_exit();
					return -1;
		}

		if (sys_outb(KBC_CMD_REG, KBDCOMMAND) != OK)
			{
			printf("cenas3");
			vg_exit();
					return -1;
			}

		if (sys_outb(OUT_BUF, SEND_PACKET) != OK)
			{
			printf("cenas4");
			vg_exit();
					return -1;
			}

		if (rec_cmd() != ACK) {
			printf("Nenhum ACK recebido");
			return -1;
		}


	while (x < cnt) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					MOUSE_int_handler();


					if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0))
					{
					packets[0] = mouse_char;
					contador++;
					}
					else if (contador == 1)
					{
						packets[1] = mouse_char;
						contador++;
					}
					else if (contador == 2) {
						packets[2] = mouse_char;
						drawBitmap(game->MenuImage,0,0,ALIGN_LEFT);
						print_mouse(packets);
						contador=0;

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

	if (MOUSE_unsubscribe_int() != OK)
		return;
}

void drawMouse(int button, int x, int y) //Esta a imprimir a partir do local do rato para baixo e direiro, é preciso alterar
{
	if (button == 0)
		drawBitmap(game->Cursor, x, y, ALIGN_LEFT);
	else if (button == 1)
		drawBitmap(game->CursorLeft, x, y, ALIGN_LEFT);
	else if (button == 2)
		drawBitmap(game->CursorRight, x, y, ALIGN_LEFT);
}


void print_mouse(unsigned char *packets) {

	if((BIT(0) & packets[0]) != 0)
		drawMouse(1,(int)(xcoord+(char)packets[1]),(int)(ycoord+(char)packets[2]));
	else if (((BIT(1) & packets[0]) >> 1) != 0)
		drawMouse(2,(int)(xcoord+(char)packets[1]),(int)(ycoord+(char)packets[2]));
	else
		drawMouse(0,(int)(xcoord+(char)packets[1]),(int)(ycoord+(char)packets[2]));

//	if((BIT(0) & packets[0]) != 0)
//		set_pixel((int)(xcoord+(char)packets[1]),(int)(ycoord+(char)packets[2]),0x02);
//	else
//		set_pixel((int)(xcoord+(char)packets[1]),(int)(ycoord+(char)packets[2]),0x3f);


	xcoord +=(char)packets[1];
	ycoord -=(char)packets[2];

	if (xcoord < 0)
		xcoord = 300;
	if (ycoord < 0)
		ycoord = 300;
	if (xcoord > MODE1024_H_RES)
		xcoord = (MODE1024_H_RES - 16);
	if (ycoord > MODE1024_V_RES)
		ycoord = (MODE1024_V_RES - 16);
}


/*
	printf(

			"B1= 0x%X B2= 0x%X B3= 0x%X LB=%d MB=%d RB=%d XOV=%d YOV=%d X=%d Y=%d\n\n",

			packets[0],
			 packets[1],
			  packets[2],
			   (BIT(0) & packets[0]),

			(BIT(2) & packets[0]) >> 2,
			(BIT(1) & packets[0]) >> 1,

			(BIT(6) & packets[0]) >> 6,
			 (BIT(7) & packets[0]) >> 7,

			(char)packets[1],
			(char)packets[2]);*/



//
//void print_config(unsigned char *packets)
//{
//	unsigned char byte1 = packets[1];
//	unsigned char byte2 = packets[2];
//	unsigned char byte3 = packets[3];
//
//	if(byte1 & BIT(6))
//		printf("Remote (polled) mode\n");
//	else
//		printf("Stream mode \n");
//
//	if(byte1 & BIT(5))
//		printf("Data reporting enabled\n");
//	else
//		printf("Reporting disable \n");
//
//	if(byte1 & BIT(4))
//		printf("Scaling is 2:1\n");
//	else
//		printf("Scaling is 1:1\n");
//
//	if(byte1 &BIT(2))
//		printf("Left button is currently pressed\n");
//	else
//		printf("Left button is currently released\n");
//
//	if(byte1 &BIT(1))
//		printf("Middle button is currently pressed\n");
//	else
//		printf("Middle button is currently released\n");
//
//	if(byte1 &BIT(0))
//		printf(" Right button is currently pressed\n");
//	else
//		printf(" Right button is currently released\n");
//
//
//	printf("Resolution: %d",byte2);
//	printf("\n");
//	printf("Sample Rate: %d",byte3);
//	printf("\n");
//
//}
//int send_cmd(unsigned long cmd){
//	unsigned long stat = 0;
//	unsigned long IBF = 0x0002;
//
//	while( 1 ) {
//		sys_inb(STAT_REG, &stat);
//		if( (stat & IBF) == 0 ) {
//			sys_outb(KBC_CMD_REG, cmd);
//			return 0;
//		}
//		tickdelay(micros_to_ticks(DELAY_US));
//	}
//}
//
//

int rec_cmd(){
	unsigned long stat = 0;
	unsigned long OBF = 0x0001;
	unsigned long data = 0;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);
		if( stat & OBF ) {
			sys_inb(OUT_BUF, &data);
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}


