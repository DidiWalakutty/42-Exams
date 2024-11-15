#include <unistd.h>

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int i = 0;
	int num = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			i++;
		else
			return (-1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

void	print_hex(int num)
{
	char str[] = "0123456789abcdef";
	if (num > 16)
		print_hex(num / 16);
	write(1, &str[num % 16], 1);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int num = ft_atoi(argv[1]);
		if (num == -1)
			return (write(1, "\n", 1), 0);
		print_hex(num);
	}
	write(1, "\n", 1);
}