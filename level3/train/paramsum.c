#include <unistd.h>

void	put_num(int i)
{
	char str[] = "0123456789";
	if (i > 9)
		put_num(i / 10);
	write(1, &str[i % 10], 1);
}

int	main(int argc, char **argv)
{
	int i = 0;

	while (i < argc - 1)
		i++;
	putnum(i);
	return (i);
}