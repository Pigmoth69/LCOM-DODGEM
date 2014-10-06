#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"
#include "timer.h"


int timer_set_square(unsigned long timer, unsigned long freq) {

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st)
{
	unsigned long temporario;
	temporario = TIMER_RB_CMD | TIMER_RB_COUNT_  |TIMER_RB_SEL(timer) ;
	sys_outb(TIMER_CTRL, temporario);
	sys_inb(TIMER_0+timer, (unsigned long *) st );
	printf("%X",*st);
	printf("\n");
	return 0;
}

int timer_display_conf(unsigned char conf)
{
	if(BIT(7) == (BIT(7) & conf))
	{
		printf("Output: 2 \n");
	}
	else if(BIT(6) == (BIT(6) & conf))
	{
		printf("Null counter: 1 \n");
	}
	else
		printf("Output: 0 \n");



	if((BIT(5)|BIT(4)) == ((BIT(5)|BIT(4))& conf))
	{
		printf("Type of access: LSB followed by MSB \n ");
	}
	else if(BIT(5) == (BIT(5) & conf))
	{
		printf("Type of access: MSB \n ");
	}
	else
		printf("Type of access: LSB\n ");
	
	if(((BIT(3)|BIT(2)|BIT(1)) == ((BIT(3)|BIT(2)|BIT(1)) & conf))|| ((BIT(2)|BIT(1)) == ((BIT(2)|BIT(1)) & conf)))
	{
		printf("Programmed mode: 3 \n");
	}
	else if((BIT(3)|BIT(2))== ((BIT(3)|BIT(2)) & conf))
	{
		printf("Programmed mode: 2 \n");
	}
	else if((BIT(3)| BIT(1))== ((BIT(3)| BIT(1)) & conf))
	{
		printf("Programmed mode: 5 \n");
	}
	else if(BIT(3)== (BIT(3) & conf))
	{
		printf("Programmed mode: 4 \n");
	}
	else if(BIT(2) == (BIT(2) & conf))
	{
		printf("Programmed mode: 2 \n");
	}
	else if(BIT(1) == (BIT(1) & conf))
	{
		printf("Programmed mode: 1 \n");
	}
	else
		printf(" Programmed mode: 0 \n");



	if(BIT(0) == (BIT(0) & conf))
		printf("Counting mode: BCD (4  decades) \n");
	else
		printf("Counting mode: Binary (16 bits) \n");
	return 0;
}

int timer_test_square(unsigned long freq) {
	
	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer)
{
	unsigned char tempo;
	int erro;
	if(timer<0 || timer >2)
	{
		return 1;
	}
	erro = timer_get_conf(timer,&tempo);

	if(erro == 1)
		return 1;


	erro = timer_display_conf(tempo);

	if(erro == 1)
		return 1;

	return 0;
}
