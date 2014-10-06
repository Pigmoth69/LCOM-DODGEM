#include <minix/syslib.h>
#include <minix/drivers.h>

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
	sys_inb(TIMER_0+timer, &temporario );
	*st = (unsigned char)temporario;
	return 0;
}

int timer_display_conf(unsigned char conf)
{
	
	return 1;
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
	if(timer!=0 || timer !=1 ||timer !=2)
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
