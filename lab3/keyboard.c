#include"keyboard.h"


int hook_id2 = 1;
int bts = 0;


int KBD_subscribe_int(void )
{

	int hook;
	hook = hook_id2;
	if (sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id2) == OK)
		if (sys_irqenable(&hook_id2) == OK)
			return BIT(hook);

	return -1;
}

int KBD_unsubscribe_int()
{
	if(sys_irqrmpolicy(&hook_id2) == OK)
		if (sys_irqdisable(&hook_id2) == OK)
			return 0;

	return 1;
}

int KDB_handler_C()
{
	sys_inb(OUT_BUF, &keyboard);// vai à porta buscar e coloca-o em &keyboard

	if (keyboard == 0xe0) // falta mudar para macro
	{
		bts = 1;
		return 1;
	}

	if (bts == 1)
	{
		if ((keyboard & BIT_SIG_0) == keyboard)
		{
			printf("MAKECODE: 0xe0%x",keyboard);
			printf("\n");
			bts = 0;
		}
		else
		{
			printf("BREAKCODE: 0xe0%x",keyboard);
			printf("\n");
			bts = 0;
		}
	}
	else
	if((keyboard & BIT_SIG_0) == keyboard)
	{
		printf("MAKECODE: 0x%x",keyboard);
		printf("\n");
	}
	else
	{
		printf("BREAKCODE: 0x%x",keyboard);
		printf("\n");
	}

	return 1;
}

int KDB_handler_ASS()
{







}


int KBD_toggle_led(int x)
{
	static int led_status = 0;
	unsigned long status;

	/*if (led_status & BIT(x) == 0){
		led_status = led_status | BIT(x);
	}
	else
		led_status = led_status & ~BIT(x);*/
	printf("%d \n", x);

	if (x == 0){
		if (led_status == 0 || led_status == 2 || led_status == 4 || led_status == 6)
			led_status += 1;
		else
			led_status -= 1;
	}
	else if (x == 1)
	{
		if (led_status == 0 || led_status == 4 || led_status == 5 || led_status == 1)
			led_status += 2;
		else
			led_status -= 2;
	}
	else if (x == 2)
	{
		if (led_status == 0 || led_status == 1 || led_status == 2 || led_status == 3)
			led_status += 4;
		else
			led_status -= 4;
	}

	//led_status ^= BIT(x);
	printf("status: %d\n", led_status);
	while (status != ACK){
	sys_outb(IN_BUF, LEDS_COMM);
	sys_inb(OUT_BUF, &status);

	}

	if(sys_outb(IN_BUF, led_status) != OK)
		return 1;
	sys_inb(OUT_BUF, &status);

	return 0;
}

