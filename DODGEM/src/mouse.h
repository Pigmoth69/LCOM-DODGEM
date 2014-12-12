#ifndef MOUSE_H_
#define MOUSE_H_

int MOUSE_subscribe_int();
int MOUSE_unsubscribe_int();
int MOUSE_int_handler();
int MOUSE_send_command();
int show_mouse();
void print_mouse(unsigned char *packets);
int rec_cmd();
void drawMouse(int button, int x, int y);

extern char mouse_char;

#endif
