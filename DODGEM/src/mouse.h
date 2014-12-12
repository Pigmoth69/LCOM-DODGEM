#ifndef MOUSE_H_
#define MOUSE_H_

typedef struct{
	int x;
	int y;
	int button; //0(None), 1(Left), 2(Right)
	int lastButton;
}MOUSE;

extern MOUSE * rato;

int MOUSE_subscribe_int();
int MOUSE_unsubscribe_int();
int MOUSE_int_handler();
int MOUSE_send_command();
int show_mouse();
void print_mouse(unsigned char *packets);
int rec_cmd();
void drawMouse();
void StartMouse();

//Check if the user clicked in an option. 0(Exit), 1(play), 2(highscores)
int checkOption();

extern char mouse_char;

#endif
