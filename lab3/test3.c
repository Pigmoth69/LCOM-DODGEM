


int hook = 0;


int kbd_test_scan(unsigned short ass)
{
	unsigned short keyboard;

	if(int irq_set = timer_subscribe_int()== -1)
		return -1;




	while( i < time) {
			/* Get a request message. */
			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
			{
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				 case HARDWARE: /* hardware interrupt notification */
					 if (msg.NOTIFY_ARG & irq_set)
					 { /* subscribed interrupt */







					 }
					 break;
					default:
						break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */

				}
		}




	if(KBD_unsubscribe_int()!= OK)
		return -1;
	return 0;
}





int kbd_test_leds(unsigned short n, unsigned short *leds)
{
    /* To be completed */
}

int kbd_test_timed_scan(unsigned short n) {
    /* To be completed */
}

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


int KDB_handler()
{



}



