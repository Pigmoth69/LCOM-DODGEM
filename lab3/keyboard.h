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

#define OK 0
#define KBD_IRQ 1
#define OUT_BUF 0x60
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64
#define BIT_SIG_0 0x7F


extern unsigned long keyboard;


#define DELAY_US 20000



int KBD_subscribe_int(void );
int KBD_unsubscribe_int();
int KDB_handler_ASS();
int KDB_handler_C();




#endif /* KEYBOARD_H_ */
