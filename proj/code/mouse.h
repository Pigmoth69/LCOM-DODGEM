#ifndef MOUSE_H_
#define MOUSE_H_

/** @defgroup mouse mouse
* @{
* Functions and data structs for manipulating mouse
*/


extern char mouse_char;

typedef struct{
	int x;
	int y;
	int button; //0(None), 1(Left), 2(Right), 3(Middle), 4(LR), 5(LRM)
	int lastButton;
}MOUSE;

extern MOUSE * rato;
extern char mouse_char;

/**
 * @brief subscribe mouse interrupts
 *
 * @return -1 if failed
 */
int MOUSE_subscribe_int();

/**
 * @brief unsubscribes mouse interrupts
 *
 * @return -1 if failed
 */
int MOUSE_unsubscribe_int();

/**
 * @brief gets a mouse packet
 *
 * @return a packet of the mouse
 */
int MOUSE_int_handler();

/**
 * @brief send a command to the mouse
 *
 * @return irq
 */
int MOUSE_send_command();

/**
 * @brief saves the correct mouse packets
 *
 * @return 1 if all packets are saved, 0 otherwise
 */
int show_mouse();

/**
 * @brief update mouse informations
 *
 * @param packets of the mouse
 */
void print_mouse(unsigned char *packets);

/**
 * @brief reads the out buffer from the KBC
 */
int rec_cmd();

/**
 * @brief draw the mouse 
 *
 */
void drawMouse();

/**
 * @brief draw the game mouse
 */
void drawMouseJogo();

/**
 * @brief allocate mouse memory and starts it's information
 */
void StartMouse();

/**
 * @brief updates the mouse coordinates, so it doesn't get out of the game area
 */
void MouseBorder();





/**@}*/

#endif
