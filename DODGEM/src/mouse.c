#include"i8042.h"
#include "DODGEM.h"
#include "video_gr.h"
#include "graphics.h"
#include "utilities.h"
#include "mouse.h"
#include "bitmap.h"
#include "timer.h"

int hook_id4 = 1;

MOUSE * rato;

unsigned long mouse;
char mouse_char;

static unsigned int xcoord = MODE1024_H_RES/2;
static unsigned int ycoord = MODE1024_V_RES/2;

void StartMouse(){
	rato=malloc(sizeof(MOUSE));
	rato->x = MODE1024_H_RES/2;
	rato->y = MODE1024_V_RES/2;
	rato->button = 0;
	rato->lastButton = 0;
}

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

int MOUSE_send_command(int irq){
	int irq_set;
	if ((irq_set = MOUSE_subscribe_int()) == -1){
		vg_exit();
		return -1;
	}

	if (sys_outb(KBC_CMD_REG, ENABLE_MOUSE) != OK){
		vg_exit();
		return -1;
	}
	if (sys_outb(KBC_CMD_REG, KBDCOMMAND) != OK){
		vg_exit();
		return -1;
	}
	if (sys_outb(OUT_BUF, SEND_PACKET) != OK){
		vg_exit();
		return -1;
	}
	if (rec_cmd() != ACK) {
		return -1;
	}

	return irq_set;
}

char packets[3];
int contador = 0;

int show_mouse() {
	if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0)){
		packets[0] = mouse_char;
		contador++;
		return 0;
	}
	else if (contador == 1){
		packets[1] = mouse_char;
		contador++;
		return 0;
	}
	else if (contador == 2) {
		packets[2] = mouse_char;
		print_mouse(packets);
		contador = 0;
		return 1;
	}
}

void drawMouse() //Esta a imprimir a partir do local do rato para baixo e direiro, é preciso alterar
{
	if (rato->button == 0)
		drawBitmap(game->Cursor, rato->x, rato->y, ALIGN_LEFT);
	else if (rato->button == 1)
		drawBitmap(game->CursorLeft, rato->x, rato->y, ALIGN_LEFT);
	else if (rato->button == 2)
		drawBitmap(game->CursorRight, rato->x, rato->y, ALIGN_LEFT);
}




void print_mouse(unsigned char *packets) {

	xcoord +=(char)packets[1];
	ycoord -= (char)packets[2];

//	if (xcoord + (char)packets[1] < 0)
//		xcoord = 0;
//	else
//		xcoord +=(char)packets[1];
//
//	if (ycoord - (char)packets[2] < 0)
//		ycoord = 0;
//	else
//		ycoord -=(char)packets[2];
//
//	if (xcoord + (char)packets[1] > MODE1024_H_RES)
//		xcoord = (MODE1024_H_RES - 16);
//	else
//		xcoord += (char)packets[1];
//
//	if (ycoord - (char)packets[2] > MODE1024_V_RES)
//		ycoord = (MODE1024_V_RES - 16);
//	else
//		ycoord -= (char)packets[2];

	rato->x = xcoord;
	rato->y = ycoord;

	rato->lastButton = rato->button;

	if((BIT(0) & packets[0]) != 0)
		rato->button = 1;
	else if (((BIT(1) & packets[0]) >> 1) != 0)
		rato->button = 2;
	else
		rato->button = 0;

//	if((BIT(0) & packets[0]) != 0)
//		drawMouse(1,(int)(xcoord),(int)(ycoord));
//	else if (((BIT(1) & packets[0]) >> 1) != 0)
//		drawMouse(2,(int)(xcoord),(int)(ycoord));
//	else
//		drawMouse(0,(int)(xcoord),(int)(ycoord));
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

//int checkOption(){
//	if ()
//}






