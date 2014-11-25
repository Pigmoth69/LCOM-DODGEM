#ifndef __TIMER_H
#define __TIMER_H



/** @defgroup timer timer
 * @{
 *
 * Functions for using the i8254 timers
 */

/**
 * @brief Configures a timer to generate a square wave
 * 
 * Does not change the LSB (BCD/binary) of the timer's control word.
 * 
 * @param timer Timer to configure. (Ranges from 0 to 2)
 * @param freq Frequency of the square wave to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_set_square(unsigned long timer, unsigned long freq);

/**
 * @brief Subscribes and enables Timer 0 interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int timer_subscribe_int(void );

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_unsubscribe_int();

/**
 * @brief Timer 0 interrupt handler
 *
 * Increments counter
 */
void timer_int_handler();

/**
 * @brief Reads the input timer configuration via read-back command
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @param st    Address of memory position to be filled with the timer config
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_get_conf(unsigned long timer, unsigned char *st);

/**
 * @brief Shows timer configuration
 * 
 * Displays in a human friendly way, the configuration of a timer
 *  as read via the read-back command, by providing the values 
 *  (and meanings) of the different components of a timer configuration 
 *
 * @param conf configuration to display in human friendly way
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_display_conf(unsigned char conf);



/**
 * @brief Tests programming timer in square wave mode
 *
 * Programs Timer 0 to generate square mode with input frequency
 *
 * @param freq Frequency of square wave to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_square(unsigned long freq);

/**
 * @brief Tests Timer 0 interrupt handling
 *
 * Subscribes Timer 0 interrupts and prints a message once
 *  per second for the specified time interval
 *
 * @param time Length of time interval while interrupts are subscribed
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_int(unsigned long time);

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf() followed by timer_display_conf()
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_config(unsigned long timer);

int getCounter();

//***********MAKROS************************MAKROS**********
//*******************************MAKROS********************
//*****MAKROS*********MAKROS*********MAKROS****************
//************MAKROS****************************MAKROS*****
//*******MAKROS************MAKROS**************************

#define TIMER_FREQ  1193182    /**< @brief clock frequency for timer in PC and AT */

#define BIT(n) (0x01<<(n))

#define TIMER0_IRQ	        0    /**< @brief Timer 0 IRQ line */

/* I/O port addresses */

#define TIMER_0			0x40 /**< @brief Timer 0 count register */
#define TIMER_1			0x41 /**< @brief Timer 1 count register */
#define TIMER_2			0x42 /**< @brief Timer 2 count register */
#define TIMER_CTRL		0x43 /**< @brief Control register */

#define SPEAKER_CTRL		0x61 /**< @brief Register for speaker control  */

/* Timer control */

/* Timer selection: bits 7 and 6 */

#define TIMER_SEL0		0x00     /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1		BIT(6)   /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2		BIT(7)   /**< @brief Control Word for Timer 2 */
#define TIMER_RB_CMD		(BIT(7)|BIT(6))  /**< @brief Read Back Command */

/* Register selection: bits 5 and 4 */

#define TIMER_LSB		BIT(4)  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB		BIT(5)  /**< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB		(TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

/* Operating mode: bits 3, 2 and 1 */

#define TIMER_SQR_WAVE		(BIT(2)|BIT(1)) /**< @brief Mode 3: square wave generator */
#define TIMER_RATE_GEN		BIT(2)          /**< @brief Mode 2: rate generator */
#define TIMER_HW_RTRIG      BIT(1)                        /**< @brief Mode 1: HARDWARE RETRIGGERABLE ONE-SHOT */
#define TIMER_INTR          BIT(0)                        /**< @brief Mode 0: INTERRUPT ON TERMINAL COUNT */


/* Counting mode: bit 0 */

#define TIMER_BCD			0x01   /**< @brief Count in BCD */
#define TIMER_BIN			0x00   /**< @brief Count in binary */

/* READ-BACK COMMAND FORMAT */

#define TIMER_RB_COUNT_         BIT(5)
#define TIMER_RB_STATUS_        BIT(4)
#define TIMER_RB_SEL(n)         BIT((n)+1)



#endif /* __TIMER_H */
