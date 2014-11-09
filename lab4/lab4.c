#include"test4.h"
#include <minix/drivers.h>

static void print_usage(char *argv[]);
static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);


int main(int argc, char *argv[]) {

	/* Initialize service */
	sef_startup();


	printf("Lab4: \n");

		if ( argc == 1 || argc == 0)
		{
			print_usage(argv);
			return 0;
		} else
		{
			proc_args(argc, argv);
		}






}





//falta alterara a usage
static void print_usage(char *argv[])
{
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"kbd_test_scan <key>\" \n"
	 "\t service run %s -args \"kbd_test_leds <spaced vector elements>\" \n"
	 "\t service run %s -args \"kbd_test_timed_scan <tempo>\" \n",
	 argv[0], argv[0],argv[0],argv[0]);

}


//falta alterar as cenas

static int proc_args(int argc, char *argv[])
{


  if (strncmp(argv[1], "kbd_test_scan", strlen("kbd_test_scan")) == 0) {
	  if( argc != 3 )
	  {
		  printf("kbd_test_scan: wrong no of arguments for test of kbd_test_scan \n");
		  return 1;
	  }
	  kbd_test_scan(parse_ulong(argv[2],10));
	  return 0;
  }
  else if (strncmp(argv[1], "kbd_test_leds", strlen("kbd_test_leds")) == 0)
  {
	  if( argc < 3)
	  {
		  printf("kbd_test_leds: wrong no of arguments for test of kbd_test_leds ");
		  return 1;
	  }

	  int list[argc - 2];
	  int *lista1;
	  int j;
	  for (j = 0; j < (argc - 2); j++)
	  {
		  list[j] = parse_ulong(argv[2 + j],10);
	  }
	  lista1 = list;

	  kbd_test_leds(argc - 2,(unsigned short*)lista1);

  }
  else if (strncmp(argv[1], "kbd_test_timed_scan", strlen("kbd_test_timed_scan")) == 0)
  {
	  if( argc != 3 )
	  {
		  printf("kbd_test_timed_scan: wrong no of arguments for kbd_test_timed_scan \n");
		  return 1;
	  }
	  kbd_test_timed_scan(parse_ulong(argv[2],10));
	  return 0;
  }
  else
  {
	  printf("Function not valid! \n");
	  print_usage(argv);
	  return 1;
  }

  return 1;

}


//nada a alterar desta função
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
