#include"keyboard.h"


int hook_id = 1;
int bts = 0;
int counter1 = 0;
int hook_id2 = 0;


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


	unsigned long status;
	status = LED_ERROR;

	while (status != ACK){
	sys_outb(OUT_BUF, LEDS_COMM);


	sys_inb(OUT_BUF, &status);

	}

	if(sys_outb(IN_BUF, led_status) != OK)
		return 1;

	return 0;
}

int timer_subscribe_int()
{
	int hook;
	hook = hook_id2;
	if (sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id2) == OK)
		if (sys_irqenable(&hook_id2) == OK)
			return BIT(hook);

	printf("erro com o subscribe \n");
	return -1;
}

int timer_unsubscribe_int()
{
	if(sys_irqrmpolicy(&hook_id2) == OK)
		if (sys_irqdisable(&hook_id2) == OK)
			return 0;

	printf("erro com o unsubscribe \n");
	return 1;
}

void timer_int_handler()
{
	counter1++;
}

int wait_a_second()
{
	int irq_set = timer_subscribe_int(); //subscreve e inicia as interrupções do timer0

	int i = 0;
	int ipc_status;
	int r;
	message msg;
	if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
	{
		printf("driver_receive failed with: %d", r);
	}

	if (is_ipc_notify(ipc_status)) { /* received notification */
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE: /* hardware interrupt notification */
			if (msg.NOTIFY_ARG & irq_set)
			{ /* subscribed interrupt */
				timer_int_handler();
				printf("%d \n", counter1);
				while (counter1 % 60 != 0 && i != 60)
				{//do nothing
					printf("g");
					i++;
				}
				printf("h \n");
				printf("%d \n", counter1);
			}
		}
	}

	printf("i \n");
	timer_unsubscribe_int(); //termina a subscrição

	printf("j \n");

	return 0;
}
