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
	unsigned long packet[];
	int counter = 0;
	char MOUSE;

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

						do{
							if (counter == 3)
								counter = 0;

							sys_outb(OUT_BUF,&MOUSE);
							couter++;
						} while(((MOUSE && BIT(3)) == BIT(3)) && counter == 1)  //quando o bit(3) do byte está a 1

						packet[0] = MOUSE;
						packet[1] = MOUSE;
						packet[2] = MOUSE;

						printf("B1 = 0x%x ", packet[0]);
						printf("B2 = 0x%x ", packet[1]);
						printf("B3 = 0x%x ", packet[2]);
						printf("LB = %d", (packet[0] && BIT(0)));
						printf("MB = %d", (packet[0] && BIT(2)));
						printf("RB = %d", (packet[0] && BIT(1)));
						printf("XOV = %d", (packet[0] && BIT(6)));
						printf("YOV = %d", (packet[0] && BIT(7)));
						printf("X = %d", packet[1]);
						printf("Y = %d", packet[2]);

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
