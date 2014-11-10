#include <minix/sysutil.h>
#include <minix/drivers.h>
#include "i8042.h"

#define DELAY_US 20000
#define KBC_CMD_PORT 0x64
#define KBC_CMD 0xD4
#define KBC_READ_PORT 0x60
#define STREAM_ENABLE 0xF4
#define STREAM_DISABLE 0xF5
#define FE_RESPONSE 0xFE
#define ACK 0xFA
#define DISABLE_MOUSE 0xA7
#define ENABLE_MOUSE 0xA8
#define CHECK_MOUSE_INTERFACE 0xA9
#define READ_CMD_BYTE 0x20

#define SET_STREAM_MODE 0xEA

int hook_id;


int send_mouse_cmd(unsigned char cmd) {
	unsigned long status;

	do {
		if (sys_outb(KBC_CMD_PORT, KBC_CMD) != OK)
			return 1;
		if (sys_outb(KBC_READ_PORT, cmd) != OK)
			return 1;

		tickdelay(micros_to_ticks(DELAY_US));

		if (sys_inb(KBC_READ_PORT, &status) != OK)
			return 1;

	} while (status != ACK);

	return 0;
}

int MOUSE_subscribe_int()
{
	int hook;
	hook = hook_id;
	if (sys_irqsetpolicy(MOUSE_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id) == OK)
		if (sys_irqenable(&hook_id) == OK)
			return 0;

	return -1;

}

int MOUSE_unsubscribe_int()
{
	if(sys_irqrmpolicy(&hook_id) == OK)
		if (sys_irqdisable(&hook_id) == OK)
			return 0;
}


