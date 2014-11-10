#include"test4.h"
#include <minix/drivers.h>

static void print_usage(char *argv[]);
static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);

int main(int argc, char *argv[]) {

	/* Initialize service */
	sef_startup();

	printf("Lab4: \n");

	if (argc == 1 || argc == 0) {
		print_usage(argv);
		return 0;
	} else {
		proc_args(argc, argv);
	}
}


static void print_usage(char *argv[]) {
	printf(
			"Usage: one of the following:\n"
					"\t service run %s -args \"test_packet <cnt>\" \n"
					"\t service run %s -args \"test_async_<time>\" \n"
					"\t service run %s -args \"test_config < >\" \n"
					"\t service run %s -args \"int test_gesture <short length> <ushort tolerance>\" \n",
			argv[0], argv[0], argv[0], argv[0]);

}

//falta alterar as cenas

static int proc_args(int argc, char *argv[]) {

	if (strncmp(argv[1], "test_packet", strlen("test_packet")) == 0) {
		if (argc != 3) {
			printf(
					"test_packet: wrong no of arguments for test of test_packet \n");
			return 1;
		}
		test_packet(parse_ulong(argv[2], 10));
		return 0;
	}
	 else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0)
	 {
	 if( argc != 3)
	 {
	 printf("test_async: wrong no of arguments for test of test_async ");
	 return 1;
	 }
	 test_async(parse_ulong(argv[2], 10));

	 }
	else if (strncmp(argv[1], "test_config", strlen("test_config")) == 0)
	 {
	 if( argc != 2 )
	 {
	 printf("test_config: wrong no of arguments for test_config \n");
	 return 1;
	 }
	 test_config();
	 return 0;

	 }/*
	 else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0)
	 	 {
	 	 if( argc < 3)
	 	 {
	 	 printf("test_async: wrong no of arguments for test of test_async ");
	 	 return 1;
	 	 }
	 	 test_async(parse_ulong(argv[2], 10));*/
	 else
	 {
	 printf("Function not valid! \n");
	 print_usage(argv);
	 return 1;
	 }
	return 1;

}


static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
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
