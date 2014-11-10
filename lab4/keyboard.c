#include"i8042.h"

int hook_id = 1;
//int bts = 0;
unsigned long mouse;

int MOUSE_subscribe_int(void) {

	int hook;
	hook = hook_id;
	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE,
			&hook_id) == OK)
		if (sys_irqenable(&hook_id) == OK)
			return BIT(hook);

	return -1;
}

int MOUSE_unsubscribe_int() {
	if (sys_irqrmpolicy(&hook_id) == OK)
		if (sys_irqdisable(&hook_id) == OK)
			return 0;

	return 1;
}

int MOUSE_int_handler() {

	if (sys_inb(OUT_BUF, &mouse) != OK)
		return -1;
	return 0;
}

void print_array(unsigned char *packets) {
	printf(
			"B1= 0x%X\t B2= 0x%X\t B3= 0x%X\t LB=%d\t MB=%d\t RB=%d\t XOV=%d\t YOV=%d\t X=%d Y=%d\n\n",
			packets[0], packets[1], packets[2], (BIT(0) & packets[0]),
			(BIT(2) & packets[0]) >> 2, (BIT(1) & packets[0]) >> 1,
			(BIT(6) & packets[0]) >> 6, (BIT(7) & packets[0]) >> 7,
			packets[1], packets[2]);

}



int send_cmd(unsigned long cmd){
	unsigned long stat = 0;
	unsigned long IBF = 0x0002;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);
		if( (stat & IBF) == 0 ) {
			sys_outb(KBC_CMD_REG, cmd);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

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


