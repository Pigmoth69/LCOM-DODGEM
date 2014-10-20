/*
 * keyboard.h
 *
 *  Created on: Oct 20, 2014
 *      Author: daniel
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_


#define KBD_IRQ 1
#define OUT_BUF 0x60
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64


int KBD_subscribe_int(void );
int KBD_unsubscribe_int();
int KDB_handler();




#endif /* KEYBOARD_H_ */
