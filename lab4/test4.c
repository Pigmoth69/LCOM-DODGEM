#include"i8042.h"
#include"i8254.h"

extern unsigned long mouse;
extern char mouse_char;

int test_packet(unsigned short cnt) {

	int x = 0;
	int ipc_status;
	int r;
	char packets[3];
	unsigned long resp;
	message msg;
	int irq_set;
	int contador = 0;

	//fazer funcao para activar stream mode

	if ((irq_set = MOUSE_subscribe_int()) == -1)
			return -1;

		if (sys_outb(KBC_CMD_REG, ENABLE_MOUSE) != OK)
			return -1;

		if (sys_outb(KBC_CMD_REG, KBDCOMMAND) != OK)
			return -1;

		if (sys_outb(OUT_BUF, SEND_PACKET) != OK)
			return -1;

		if (rec_cmd() != ACK) {
			printf("Nenhum ACK recebido");
			return -1;
		}

	while (x < cnt) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					MOUSE_int_handler();

					if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0))
					{
					packets[0] = mouse_char;
					contador++;
					}
					else if (contador == 1)
					{
						packets[1] = mouse_char;
						contador++;
					}
					else if (contador == 2) {
						packets[2] = mouse_char;
						print_array(packets);
						x++;
						contador = 0;
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

	if (MOUSE_unsubscribe_int() != OK)
		return -1;
	return 0;

}

int test_async(unsigned short idle_time) {

		int counter1=0;
		int i=0;
		int irq_set1;
		int irq_set2;
		int ipc_status;
		int r;
		char packets[3];
		unsigned long resp;
		message msg;
		int contador = 0;

			//fazer funcao para activar stream mode

			if ((irq_set1 = MOUSE_subscribe_int()) == -1)
					return -1;

				/*if (sys_outb(KBC_CMD_REG, ENABLE_MOUSE) != OK)
					return -1;*/

				if (sys_outb(KBC_CMD_REG, KBDCOMMAND) != OK)
					return -1;

				if (sys_outb(OUT_BUF, SEND_PACKET) != OK)
					return -1;

				if (rec_cmd() != ACK) {
					printf("Nenhum ACK recebido");
					return -1;
				}


		if((irq_set2 = timer_subscribe_int()) == -1)
			return -1;


		while(i < idle_time) {
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
						MOUSE_int_handler();
						i=0;
						if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0))
						{
							packets[0] = mouse_char;
							contador++;
						}
						else if (contador == 1)
						{
							packets[1] = mouse_char;
							contador++;
						}
						else if (contador == 2) {
							packets[2] = mouse_char;
							print_array(packets);

							contador = 0;
						}


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
					}

					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}

		if (MOUSE_unsubscribe_int() != OK)
				return -1;
		if(timer_unsubscribe_int()!= OK)
			return -1;

		return 0;
}

int test_config(void) {

		int ipc_status;
		int r;
		char packets[3];
		unsigned long resp;
		message msg;
		int irq_set;
		int x =0;


		if ((irq_set = MOUSE_subscribe_int()) == -1)
			return -1;
		if (sys_outb(KBC_CMD_REG, ENABLE_MOUSE) != OK)
			return -1;
		if (sys_outb(KBC_CMD_REG, KBDCOMMAND) != OK)
			return -1;
		if(sys_outb(KBC_CMD_REG,DISABLE_STREAM) != OK)
			return -1;
		if(sys_outb(KBC_CMD_REG,KBDCOMMAND)!= OK)
			return -1;
		if (sys_outb(OUT_BUF, STATUSREQUEST) != OK)
			return -1;

		if (rec_cmd() != ACK) {
			printf("Nenhum ACK recebido");
			test_config();
		}

		if( sys_inb(OUT_BUF, &mouse) == OK ) {
		printf("Scaling:");
		if (mouse & BIT(4))
		{
		printf(" 2:1\n");
		}
		else
		{
		printf(" 1:1\n");
		}

		printf("Data Reporting:");
		if (mouse & BIT(5))
		{
		printf(" enable\n");
		}
		else
		{
		printf(" disable\n");
		}
		printf("Mode:");
		if (mouse & BIT(6))
		{
		printf(" remote mode is enabled\n");
		}
		else
		{
		printf(" stream mode is enabled\n");
		}
		printf("Byte 1: 0x%X \n", mouse);
		}
		if( sys_inb(OUT_BUF, &mouse) == OK ) {
		printf("Byte 2: 0x%X \n", mouse);
		printf("Resolution: %d\n", mouse<<1);
		}
		if( sys_inb(OUT_BUF, &mouse) == OK ) {
		printf("Byte 3: 0x%X \n", mouse);
		printf("Sample Rate: %d\n", mouse);
		}
		return -1;



}

int test_gesture(short length, unsigned short tolerance) {
	/* To be completed ... */
}
