

int invert_number(int number)
{
	int x=0;

	while(number % 10 != 0)
	{
		x= (x*10)+number%10;
		number = number/10;
	}
	return x;
}




























