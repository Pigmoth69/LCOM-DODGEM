#include"timer.h"
#include <minix/drivers.h>
#include"i8254.h"



int main(int argc, char **argv) {

  vt_info_t vt_info;

  /* Initialize service */

  sef_startup();

  /* Get video text mode info */

  vt_info_get(&vt_info);

  /* Display video text mode info */
  vt_info_display(&vt_info);

  video_mem = vt_init(&vt_info);

  printf("lab1: VRAM mapped on virtual address %p\n", video_mem);

  if ( argc == 1 ) {
      print_usage(argv);
      return 0;
  } else {
      proc_args(argc, argv);
  }
  return 0;

}

static void print_usage(char *argv[])
{
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"fill <hex-code> <hex-attr>\" \n"
	 "\t service run %s -args \"blank\" - to blank screen \n"
	 "\t service run %s -args \"char <hex-code> <hex-attr> <line no> <col no>\" \n"
	 "\t service run %s -args \"string <string> <hex-attr> <line no> <col no>\" \n"
	 "\t service run %s -args \"int <decimal number> <hex-attr> <line no> <col no>\" \n"
	 "\t service run %s -args \"frame <width> <height> <hex-attr> <line no> <col no>\" \n",
	 argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);

}

static int proc_args(int argc, char *argv[])
{

  unsigned long ch, row, col, attr, width, height;
  char *str;
  long num;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "blank", strlen("blank")) == 0) {
	  if( argc != 2 ) {
		  printf("video_txt: wrong no of arguments for test of vt_blank() \n");
		  return 1;
	  }
	  printf("video_txt:: vt_blank()\n"); /* Actually, it was already invoked */
	  vt_blank();
	  return 0;
  } else if (strncmp(argv[1], "fill", strlen("fill")) == 0) {
	  if( argc != 4 ) {
		  printf("video_txt: wrong no of arguments for test of vt_fill_char() \n");
		  return 1;
	  }
	  if( (ch = parse_ulong(argv[2], 16)) == ULONG_MAX )
		  return 1;
	  if( (attr = parse_ulong(argv[3], 16)) == ULONG_MAX )
		  return 1;
	  printf("video_txt:: vt_fill(0x%X, 0x%X)\n",
			  (unsigned)ch, (unsigned)attr);
	  vt_fill(ch, attr);
	  return 0;
  } else if (strncmp(argv[1], "char", strlen("char")) == 0) {
	  if( argc != 6 ) {
		  printf("video_txt: wrong no of arguments for test of vt_print_char() \n");
		  return 1;
	  }
	  if( (ch = parse_ulong(argv[2], 16)) == ULONG_MAX )
		  return 1;
	  if( (attr = parse_ulong(argv[3], 16)) == ULONG_MAX )
		  return 1;
	  if( (row = parse_ulong(argv[4], 10)) == ULONG_MAX )
		  return 1;
	  if( (col = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  printf("video_txt:: vt_print_char(0x%X, 0x%X, %lu, %lu)\n",
			  (unsigned)ch, (unsigned)attr, row, col);
	  return vt_print_char(ch, attr, row, col);
  } else if (strncmp(argv[1], "string", strlen("string")) == 0) {
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
	  return vt_print_string(str, attr, row, col);
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
	  return vt_print_int(num, attr, row, col);
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
	  return vt_draw_frame(width, height, attr, row, col);
  } else {
	  printf("video_txt: non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}
