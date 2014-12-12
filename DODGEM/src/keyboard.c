#include"keyboard.h"
#include "utilities.h"

int hook_id2 = 2;
unsigned long keyboard;

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

int KBD_handler_C()
{
	sys_inb(OUT_BUF, &keyboard);// vai à porta buscar e coloca-o em &keyboard

	keyboard = keyboard << 24;
	keyboard = keyboard >> 24;

	return keyboard;
}

