#include"keyboard.h"


int hook_id = 1;
int bts = 0;
int counter1 = 0;


int KBD_subscribe_int(void )
{

	int hook;
	hook = hook_id;
	if (sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id) == OK)
		if (sys_irqenable(&hook_id) == OK)
			return BIT(hook);

	return -1;
}

int KBD_unsubscribe_int()
{
	if(sys_irqrmpolicy(&hook_id) == OK)
		if (sys_irqdisable(&hook_id) == OK)
			return 0;

	return 1;
}

int KDB_handler_C()
{
	sys_inb(OUT_BUF, &keyboard);// vai à porta buscar e coloca-o em &keyboard

	if (keyboard == 0xe0)
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
	return 0;
}


int KBD_toggle_led(int x)
{
	static char led_status = 0x00;

	if (led_status && BIT(x) == 0){
		led_status = led_status | BIT(x);
	}
	else
		led_status = led_status & ~BIT(x);


	int status;
	status = LED_ERROR;

	while (status != ACK){
	if (sys_outb(IN_BUF, LEDS_COMM) != OK)
		return 1;

	if (status != ACK)
		continue;

	if (sys_inb(OUT_BUF, (unsigned long *) status) != OK)
		return 1;
	}


	if(sys_outb(IN_BUF, led_status) != OK)
		return 1;


	return 0;
}

int timer_subscribe_int(void )
{
	int hook;
	hook = hook_id;
	if (sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id) == OK)
		if (sys_irqenable(&hook_id) == OK)
			return BIT(hook);

	return -1;
}

int timer_unsubscribe_int()
{
	if(sys_irqrmpolicy(&hook_id) == OK)
		if (sys_irqdisable(&hook_id) == OK)
			return 0;

	return 1;
}

void timer_int_handler()
{
	counter1++;
}
