#include"test3.h"
#include"keyboard.h"
#include <minix/drivers.h>

static void print_usage(char *argv[]);
static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);


int main(int argc, char **argv) {

	 /* Initialize service */

	  sef_startup();

 // printf("Lab3: \n");

/*
  if ( argc == 1 || argc == 0)
  {
      print_usage(argv);
      return 0;
  } else
  {
      proc_args(argc, argv);
  }*/
	  kbd_test_scan(1);
  return 0;

}

static void print_usage(char *argv[])
{
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"test_scan  <key>\" \n",
	 "\t service run %s -args \"square <freq>\" \n"
	 "\t service run %s -args \"config <timer>\" \n",
	 argv[0], argv[0],argv[0]);

}

static int proc_args(int argc, char *argv[])
{


  if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
	  if( argc != 3 )
	  {
		  printf("test_scan: wrong no of arguments for test of kbd_test_scan \n");
		  return 1;
	  }
	  kbd_test_scan(parse_ulong(argv[2],10));
	  return 0;
  }/*
  else if (strncmp(argv[1], "square", strlen("square")) == 0)
  {
	  if( argc != 3 )
	  {
		  printf("square: wrong no of arguments for test of timer_test_square() ");
		  return 1;
	  }
	  timer_test_square(parse_ulong(argv[2],10));

  }
  else if (strncmp(argv[1], "config", strlen("config")) == 0)
  {
	  if( argc != 3 )
	  {
		  printf("config: wrong no of arguments for timer_test_config() \n");
		  return 1;
	  }
	  timer_test_config(parse_ulong(argv[2],10));
	  return 0;
  }
  else
  {
	  printf("Function not valid! \n");
	  print_usage(argv);
	  return 1;
  }*/
  return 1;

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

