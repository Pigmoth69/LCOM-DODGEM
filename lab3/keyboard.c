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

	if (keyboard == TWO_BYTES) // verifica se o endereço da tecla possui 2 bytes
	{
		bts = 1; //coloca a variavel bts a 1 para mais tarde ver se o endereço é de 2 bytes
		return 1; //caso seja de 2 bytes passa ao proximo ciclo
	}

	if (bts == 1) //caso tenha 2 bytes
	{
		if ((keyboard & BIT_SIG_0) == keyboard) //verifica se é makecode ou breakcode (BIT mais significativo a 1 ou 0
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
	if((keyboard & BIT_SIG_0) == keyboard) //verifica se é make ou breakcode (bit mais sig a 0 ou 1)
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


	//printf("status: %d\n", led_status);
	while (status != ACK){
	sys_outb(IN_BUF, LEDS_COMM);
	sys_inb(OUT_BUF, &status);

	}

	if(sys_outb(IN_BUF, led_status) != OK)
		return 1;
	sys_inb(OUT_BUF, &status);

	return 0;
}

