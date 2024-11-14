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
	int	i;
	if (argc > 2)
	{
		i = 0;
		while (i < (argc - 1))
			i++;
		put_num(i);
	}
	else
		write(1, "0", 1);
	write(1, "\n", 1);
}