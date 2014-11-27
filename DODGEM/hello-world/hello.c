#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Hello ");
    int i = argc;


    if(argc-1 !=0 )
    {
    	for(i = 1; i != argc; i +=1)
    	{
    	printf("%s",argv[i]);
    	printf(" ");
    	}
    }


	return 0;



}
