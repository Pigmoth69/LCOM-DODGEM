#include<stdio.h>

int main(int argc, char* argv[])
{
int x = 1;
int *p;

p=&x;
printf("0x%x",(unsigned)p);
return 0;

}
