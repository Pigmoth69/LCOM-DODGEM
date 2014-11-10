#include"i8042.h"
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include <stdio.h>
#include "mouse.h"



int test_packet(unsigned short cnt)
{

	int x =0;
	int ipc_status;
	int r;
	message msg;
	int irq_set;

	if(( irq_set = MOUSE_subscribe_int())== -1)
		return -1;

		while(x < cnt) {
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
//.............................................................................................................
						sys_outb(KBDCOMMAND,&MOUSE);







//.............................................................................................................
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}

		if(MOUSE_unsubscribe_int()!= OK)
			return -1;
		return 0;





}	
	
int test_async(unsigned short idle_time) {
    /* To be completed ... */
}
	
int test_config(void) {
    /* To be completed ... */
}	
	
int test_gesture(short length, unsigned short tolerance) {
    /* To be completed ... */
}
