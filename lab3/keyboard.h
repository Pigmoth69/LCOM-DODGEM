/*
 * keyboard.h
 *
 *  Created on: Oct 20, 2014
 *      Author: daniel
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include"test3.h"
#include <minix/sysutil.h>
#include <minix/drivers.h>
#include "i8254.h"
#include "timer.h"

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




extern unsigned long keyboard;


#define DELAY_US 20000



int KBD_subscribe_int(void );
int KBD_unsubscribe_int();
int KDB_handler_ASS();
int KDB_handler_C();
int KBD_toggle_led(int x);

/*
int timer_subscribe_int(void );
int timer_unsubscribe_int();
void timer_int_handler();*/
int wait_a_second();


#endif /* KEYBOARD_H_ */
