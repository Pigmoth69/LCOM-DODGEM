#include <minix/drivers.h>

#include "test5.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {




  //char *video_mem;
 // vt_info_t vt_info;

  /* Initialize service */

  sef_startup();

  if ( argc == 1 ) {
      print_usage(argv);
      return 0;
  } else {   
      proc_args(argc, argv);
  }
  return 0;

}

static void print_usage(char *argv[]) {
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"test_init <mode> <delay>\" \n"
	 "\t service run %s -args \"test_square <x> <y> <size> <color>\" \n"
	 "\t service run %s -args \"test_line <xi> <yi> <xf> <yf>\"\n"
	 "\t service run %s -args \"test_xpm <xi> <yi> <image>\"\n"
	 "\t service run %s -args \"test_line <xi> <yi> <xf> <yf>\"\n"
	 "\t service run %s -args \"test_line <xi> <yi> <xf> <yf>\"\n",
	 argv[0], argv[0], argv[0],argv[0],argv[0],argv[0]);

}

static int proc_args(int argc, char *argv[]) {

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
	  if( argc != 4 ) {
		  printf("test_init: wrong no of arguments for test of test_init \n");
		  return 1;
	  }
	  if(parse_ulong(argv[2], 16) == ULONG_MAX)
	  {
		  printf("Out of range!\n");
		  return -1;
	  }
	  test_init(parse_ulong(argv[2], 16),parse_ulong(argv[3], 10));
	  return 0;
  } else if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
	  if( argc != 6 ) {
		  printf("test_square: wrong no of arguments for test of test_square \n");
		  return 1;
	  }
	  if(parse_ulong(argv[5], 16)==ULONG_MAX)
	  {
		  printf("Out of range!\n");
		  return -1;
	  }
	  test_square(parse_ulong(argv[2], 10),parse_ulong(argv[3], 10),parse_ulong(argv[4], 10),parse_ulong(argv[5], 16));
	  return 0;
  } else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
	  if( argc != 7 ) {
		  printf("test_line: wrong no of arguments for test of test_line \n");
		  return 1;
	  }
	  if(parse_ulong(argv[6], 16)==ULONG_MAX)
	 	  {
	 		  printf("Out of range!\n");
	 		  return -1;
	 	  }
	  test_line(parse_ulong(argv[2], 10),parse_ulong(argv[3], 10),parse_ulong(argv[4], 10),parse_ulong(argv[5], 10),parse_ulong(argv[6], 16));
	  return 0;

  }else if (strncmp(argv[1], "test_xpm", strlen("test_xpm")) == 0) {
	  if( argc != 5 ) {
		  printf("test_xpm: wrong no of arguments for test of test_xpm \n");
		  return 1;
	  }
	  char ** imagem = readImage(argv[4]);
	  if(imagem == NULL)
	  {
		  printf("Invalid image!\n");
		  return 0;
	  }


	  test_xpm(parse_ulong(argv[2], 10),parse_ulong(argv[3], 10),imagem);
	  return 0;











  }else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
	  if( argc != 7 ) {
		  printf("test_line: wrong no of arguments for test of test_line \n");
		  return 1;
	  }
	  if(parse_ulong(argv[6], 16)==ULONG_MAX)
	 	  {
	 		  printf("Out of range!\n");
	 		  return -1;
	 	  }
	  test_line(parse_ulong(argv[2], 10),parse_ulong(argv[3], 10),parse_ulong(argv[4], 10),parse_ulong(argv[5], 10),parse_ulong(argv[6], 16));
	  return 0;
  }else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
	  if( argc != 7 ) {
		  printf("test_line: wrong no of arguments for test of test_line \n");
		  return 1;
	  }
	  if(parse_ulong(argv[6], 16)==ULONG_MAX)
	 	  {
	 		  printf("Out of range!\n");
	 		  return -1;
	 	  }
	  test_line(parse_ulong(argv[2], 10),parse_ulong(argv[3], 10),parse_ulong(argv[4], 10),parse_ulong(argv[5], 10),parse_ulong(argv[6], 16));
	  return 0;
  }else {
	  printf("Non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned long parse_ulong(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == ULONG_MAX )
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return ULONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);
	  return ULONG_MAX;
  }

  /* Successful conversion */
  return val;
}

static long parse_long(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtol(str, &endptr, base);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return LONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_long: no digits were found in %s \n", str);
	  return LONG_MAX;
  }

  /* Successful conversion */
  return val;
}
