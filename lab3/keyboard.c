#include"keyboard.h"

int hook_id = 1;
int bts = 0;


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
		printf("MAKECODE: 0xe0%x",keyboard);
		printf("\n");
		bts = 0;
	}
	else
	if((keyboard & 0x7F) == keyboard)
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
