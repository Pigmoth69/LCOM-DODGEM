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
	 "\t service run %s -args \"test_line <xi> <yi> <xf> <yf>\"\n",
	 argv[0], argv[0], argv[0]);

}

static int proc_args(int argc, char *argv[]) {

	unsigned long mode,color;
	int size,delay;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "test_int", strlen("test_int")) == 0) {
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

  }/* else if (strncmp(argv[1], "string", strlen("string")) == 0) {
	  if( argc != 6 ) {
		  printf("video_txt: wrong no of arguments for test of vt_print_string() \n");
		  return 1;
	  }
	  str = argv[2];
	  if( (attr = parse_ulong(argv[3], 16)) == ULONG_MAX )
		  return 1;	
	  if( (row = parse_ulong(argv[4], 10)) == ULONG_MAX )
		  return 1;
	  if( (col = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  printf("video_txt:: vt_print_string(%s, 0x%X, %lu, %lu)\n",
			  str, (unsigned)attr, row, col);
	  return; //vt_print_string(str, attr, row, col);
  } else if (strncmp(argv[1], "int", strlen("int")) == 0) {
	  if( argc != 6 ) {
		  printf("video_txt: wrong no of arguments for test of vt_print_int() \n");
		  return 1;
	  }
	  if( (num = parse_long(argv[2], 10)) == LONG_MAX )
		  return 1;
	  if( (attr = parse_ulong(argv[3], 16)) == ULONG_MAX )
		  return 1;		  
	  if( (row = parse_ulong(argv[4], 10)) == ULONG_MAX )
		  return 1;		  
	  if( (col = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  printf("video_txt:: vt_print_int(%lu, 0x%X, %lu, %lu)\n",
		 num, (unsigned)attr, row, col);
	  return; //vt_print_int(num, attr, row, col);
  } else if (strncmp(argv[1], "frame", strlen("frame")) == 0) {
	  if( argc != 7 ) {
		  printf("video_txt: wrong no of arguments for test of vt_draw_frame() \n");
		  return 1;
	  }
	  if( (width = parse_ulong(argv[2], 10)) == LONG_MAX )
		  return 1;
	  if( (height = parse_ulong(argv[3], 10)) == LONG_MAX )
		  return 1;
	  if( (attr = parse_ulong(argv[4], 16)) == ULONG_MAX )
		  return 1;
	  if( (row = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  if( (col = parse_ulong(argv[6], 10)) == ULONG_MAX )
		  return 1;
	  printf("video_txt:: draw_frame(%lu, %lu, 0x%X, %lu, %lu)\n",
		 width, height, (unsigned)attr, row, col);
	  return; //vt_draw_frame(width, height, attr, row, col);
  } */else {
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
