#include <unistd.h>

void	put_num(int num)
{
	char str[] = "0123456789";
	if (num > 9)
		put_num(num / 10);
	write(1, &str[num % 10], 1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	put_num(argc -1);
	write(1, "\n", 1);
	return (0);
}