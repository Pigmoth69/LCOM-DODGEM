#include"i8042.h"
#include "video_gr.h"
#include "utilities.h"

int hook_id4 = 1;
//int bts = 0;

unsigned long mouse;
char mouse_char;

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
	if (sys_irqrmpolicy(&hook_id4) == OK)
		if (sys_irqdisable(&hook_id4) == OK)
			return 0;

	return 1;
}

int MOUSE_int_handler() {

	if (sys_inb(OUT_BUF, &mouse) != OK)
		return -1;
	mouse_char = (char)mouse;
	return 0;
}

//void print_array(unsigned char *packets) {
//
//
//
//
//
//
//	printf(
//			"B1= 0x%X B2= 0x%X B3= 0x%X LB=%d MB=%d RB=%d XOV=%d YOV=%d X=%d Y=%d\n\n",
//			packets[0], packets[1], packets[2], (BIT(0) & packets[0]),
//			(BIT(2) & packets[0]) >> 2, (BIT(1) & packets[0]) >> 1,
//			(BIT(6) & packets[0]) >> 6, (BIT(7) & packets[0]) >> 7,
//			(char)packets[1], (char)packets[2]);
//
//}
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
//int rec_cmd(){
//	unsigned long stat = 0;
//	unsigned long OBF = 0x0001;
//	unsigned long data = 0;
//
//	while( 1 ) {
//		sys_inb(STAT_REG, &stat);
//		if( stat & OBF ) {
//			sys_inb(OUT_BUF, &data);
//			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
//				return data;
//			else
//				return -1;
//		}
//		tickdelay(micros_to_ticks(DELAY_US));
//	}
//}


