#include <unistd.h>

void	put_num(int number)
{
	char	*str = "0123456789";

	if (number > 9)
		put_num(number / 10);
	write(1, &str[number % 10], 1);
}

int	main(void)
{
	int i = 1;
	while (i <= 100)
	{
		if (i % 15 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			put_num(i);
		write(1, "\n", 1);
		i++;
	}
}