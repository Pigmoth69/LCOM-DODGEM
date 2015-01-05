#ifndef UTILITIES_H_
#define UTILITIES_H_


/** @defgroup utilities utilities
* @{
* Functions and data for manipulating utilities and general data variables
*/


#define BIT(n) (0x01 << n)
#define WHITE 0x3f
#define videocard 0x10

#define MODE1024 0x117
#define MODE1024_H_RES 1024
#define MODE1024_V_RES 768
#define FILENAME "/home/DODGEM/scores.txt"
#define ImagesPath "/home/DODGEM/"
#define INVALID '*'

/**
 * @brief turns a char into a int
 *
 * @param n char pretended
 *
 * @return the int correspondent
 */
int char_to_int(char n); // numero


/**@}*/

#endif /* UTILITIES_H_*/
