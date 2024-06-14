#include <unistd.h>

int ft_atoi(char *str)
{
	int i = 0;
	int n = 0;

	if (str[i] == '-')
		return (0);
	while (str[i] != '\0')
	{
		n = n * 10;
		n = n + str[i] - '0';
		i++;
	}
	return (n);
}

void	print_hex(int num)
{
	char str[] = "0123456789abcdef";
	if (num >= 16)
		print_hex(num / 16);
	write(1, &str[num % 16], 1);
}

int	main(int argc, char **argv)
{
	int i = 0;

	if (argc == 2)
	{
		print_hex(ft_atoi(argv[1]));
	}
	write(1, "\n", 1);
}