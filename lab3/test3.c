#include"test3.h"

unsigned long keyboard = 0x00;


int kbd_test_scan(unsigned short ass)
{
	int ipc_status;
	int r;
	message msg;
	int irq_set;

	if(( irq_set = KBD_subscribe_int())== -1)
		return -1;

	while(keyboard!= ESC_KEY) {
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
					if( ass == 0)
						KDB_handler_ASS();
					else
						KDB_handler_C();
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
	int x;

	unsigned i;
	i = 0;


	for (x=0; x < n; x++)
	{
		printf("toggle led %d \n", *(leds+ x*sizeof(short)));

		KBD_toggle_led(*(leds + x*sizeof(short)));
		wait_a_second();
	}
	return 0;
}




int kbd_test_timed_scan(unsigned short n)
{
	int counter1=0;
	int i=0;
	int ipc_status;
	int r;
	message msg;
	int irq_set1;
	int irq_set2;

	if(( irq_set1 = KBD_subscribe_int())== -1)
		return -1;
	if((irq_set2 = timer_subscribe_int()) == -1)
		return -1;


	while(keyboard != ESC_KEY) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set1)
				{ /* subscribed interrupt */

						KDB_handler_C();
						i = 0;
				}

				if(msg.NOTIFY_ARG & irq_set2)
				{
					counter1++;
					if(counter1 % 60 == 0)
					{
						i++;
						//printf("%d",i);
						//printf("\n");
					}
					if(i == n)
					{
						keyboard= ESC_KEY;
						printf("O tempo acabou!\n");
					}


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
	if(timer_unsubscribe_int()!= OK)
		return -1;

	return 0;
}

