#ifndef __I8042_H
#define __I8042_H

#define BIT(n) (0x01<<n)

#define KBC_IRQ	1


#define OUT_BUF 0x60
#define IN_BUF 0x60
#define KBC_STAT_REG 0x64
#define KBC_CMD_REG 0x64


#define ACK 0xfa
#define RESEND 0xfe
#define ERROR 0xfc

#define	KBD_TOGGLE_LEDS 0xed

#define KBD_LED(n) (1<<n)

#define KBD_WAIT_TIME 20000


#define KBC_OBF BIT(0)
#define KBC_IBF BIT(1)
#define KBC_PAR_ERROR BIT(7)
#define KBC_TO_ERROR BIT(6)

#define TIMER0_HOOK_BIT 0
#define MOUSE_HOOK_BIT 1

#define TIMER0_IRQ 0
#define MOUSE_IRQ 12

#define IS_BREAKCODE(c) (c>>7)


#endif /* __I8042_H */
