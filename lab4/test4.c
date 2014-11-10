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
	int contador=0;


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

	while (contador < 3) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					printf("msg.notify\n");

					MOUSE_int_handler();

					if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0))
					{
						packets[0] = mouse_char;
						contador++;
						printf("contador=1\n");
					}
					else if (contador == 1)
					{
						packets[1] = mouse_char;
						contador++;
						printf("contador=2\n");
					}
					else if (contador == 2) {
						printf("contador=3\n");
						packets[2] = mouse_char;
						print_config(packets);
						contador++;
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



int test_gesture(short length, unsigned short tolerance) {
	int x = 0;
	int ipc_status;
	int r;
	char packets[3];
	unsigned long resp;
	message msg;
	int irq_set;
	int contador = 0;
	int distance = 0;
	int eixoYY = 0;
	int state = 0; //coloca o estado no inicio
	//quando state == 0, encontra-se no estado inicial
	//quando state == 1, encontra-se no estado draw
	//quando state == 2, encontra-se no estado final

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

	while (state != 2) {
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
						print_array(packets); //imprime as confs do rato

						switch(state){
						case 0: //caso se encontre no estado inicial
							if ((BIT(0) & packets[0]) == BIT(0)) //se o botao esquerdo for pressionado
								{
									distance = 0; //da reset na distancia
									eixoYY = 0; //da reset na altura
									state = 1;
								}
							break;
						case 1:
							if ((BIT(0) & packets[0]) != BIT(0))
								state = 0;
							else
							{
								if ((length > 0 && (char)packets[1] < 0) || (length < 0 && (char)packets[1] > 0))
									state = 0;
								else
								{
									if ((abs(distance) >= abs(length)) || eixoYY >= tolerance)
									{
										state = 2;
									}
									else
									{
										distance += (char)packets[1];
										eixoYY += abs((char)packets[2]);
										break;
									}
								}

							}

							break;


						}

						contador = 0;
					}


					//					LB=(BIT(0) & packets[0])
					//					X=(char)packets[1]
					//					Y=(char)packets[2]

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
	{
		return -1;
	}
	return 0;
}


//typedef enum {INIT, DRAW, COMP} state_t;
//typedef enum {LDOW, LUP, MOVE} ev_type_t;
//void check_hor_line(event_t *evt) {
//	static state_t st = INIT; // initial state; keep state
//	switch (st) {
//	case INIT:
//		if( evt->type == LDOWN )
//			state = DRAW;
//		break;
//	case DRAW:
//		if( evt->type == MOVE ) {
//			[...] // need to check if HOR_LINE event occurs
//		} else if( evt->type == LUP )
//			state = INIT;
//		break;
//	default:
//		break;
//	}
//}
