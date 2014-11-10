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
	int firstCicle = 0;

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

					if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0) && (firstCicle == 1))
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

					firstCicle = 1;

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
		int firstCicle = 0;

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
						if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0) && (firstCicle == 1))
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

						firstCicle = 1;


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

	int x = 0;
	int ipc_status;
	int r;
	char packets[3];
	unsigned long resp;
	message msg;
	int irq_set;
	int contador = 0;
	char array[3];
	int i;
	int firstCicle = 0;


//	if(sys_outb(KBC_CMD_REG,ENABLE_MOUSE)!= OK)
//		return -1;
//
//	if(sys_outb(KBC_CMD_REG,KBDCOMMAND)!= OK)
//		return -1;
//
//	if (sys_outb(OUT_BUF, DISABLE_STREAM) != OK)
//		return -1;
//
//	if(sys_outb(KBC_CMD_REG,KBDCOMMAND)!= OK)
//		return -1;
//
//	if (sys_outb(IN_BUF, STATUSREQUEST) != OK)
//		return -1;

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

	while (x != 1) {
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


						if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0) && (firstCicle == 1))
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
							print_config(packets);
							contador++;
							x = 1;
						}

						firstCicle = 1;

					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else {
			x = 1;
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
	int firstCicle = 0;
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

	do {
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

					if (((BIT(3) & mouse_char) == BIT(3)) && (contador == 0) && (firstCicle == 1))
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
									state = 1; //Coloca o estado em Draw
								}
							break;
						case 1:
							if ((BIT(0) & packets[0]) != BIT(0)) //Se o botao direito for largado
								state = 0;
							else
							{
								if ((length > 0 && (char)packets[1] < 0) || (length < 0 && (char)packets[1] > 0))
									state = 0; //caso o movimento seja no sentido oposto ao escolhido
								else
								{
									if ((abs(distance) >= abs(length)) || eixoYY >= tolerance)
									{
										state = 2; //quando a distancia em X ou Y ultrapassa o limite necessario
									}
									else
									{
										distance += (char)packets[1]; //adiciona a distancia total em X o movimento feito pelo rato em X
										eixoYY += abs((char)packets[2]); //adiciona o modulo do movimento de y do rato ao total em Y
										break;
									}
								}

							}

							break;


						}

						contador = 0;
					}

					firstCicle = 1;


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
	} while (state != 2);

	if (MOUSE_unsubscribe_int() != OK)
	{
		return -1;
	}
	return 0;
}
