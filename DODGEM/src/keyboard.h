/*
 * keyboard.h
 *
 *  Created on: Oct 20, 2014
 *      Author: daniel
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <minix/sysutil.h>
#include <minix/drivers.h>
#include "i8254.h"

//#define OK 0
#define KBD_IRQ 1
#define OUT_BUF 0x60
#define IN_BUF 0x60
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64
#define BIT_SIG_0 0x7F
#define LED 0xED
#define ESC_KEY 0x81
#define LEDS_COMM 0xED
#define RESEND 0xFE
#define LED_ERROR 0xFC
#define ACK 0xFA
#define TWO_BYTES 0xe0
#define PAR_ERR 0x80
#define TO_ERR 0x40
#define ESC_BREAK_CODE 0x81
#define ENTER_KEY 0x009C
#define W_KEY 0x0091
#define S_KEY 0x009F
#define KEY_1 0x0082
#define KEY_2 0x0083
#define KEY_3 0x0084



//extern unsigned long keyboard;


#define DELAY_US 20000

int KBD_subscribe_int(void );
int KBD_unsubscribe_int();
int KBD_handler_C();

int wait_a_second();


int send_cmd();
//int rec_cmd();

#endif /* KEYBOARD_H_ */
