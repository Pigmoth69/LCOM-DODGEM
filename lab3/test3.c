#include"test3.h"
#include "timer.h"

unsigned long keyboard = 0x00;
int counter =0;


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
					{
						return 0;
					}
					else
					{
						KDB_handler_C();
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
	return 0;
}




int kbd_test_leds(unsigned short n, unsigned short *leds)
{
	int x;

	int irq_set = timer_subscribe_int(); //subscreve e inicia as interrupções do timer0

	int ipc_status;
	int r;
	message msg;
	unsigned i = 0;



	for (x=0; x < n; x++)
	{
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
					counter++;
					if (counter == 60) //a cada segundo (60 contagens a 60 de frequencia)
					{
						printf("toggle led %d \n", leds[x]);

						KBD_toggle_led(leds[x]);
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}


		if (timer_unsubscribe_int() != OK)  //termina a subscrição, caso dê erro retorna 1
			return 1;

	}
}

int kbd_test_timed_scan(unsigned short n)
{
    /* To be completed */
}



