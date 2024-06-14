#include <unistd.h>

int	ft_atoi(char *str)
{
	int i = 0;
	int result = 0;
	int multx = 1;

	if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * multx);
}

void	put_num(int num)
{
	char str[] = "0123456789abcdef";
	if (num > 16)
		put_num(num / 16);
	write(1, &str[num % 16], 1);
}

int	main(int argc, char **argv)
{
	int num = 0;
	if (argc == 2)
	{
		num = ft_atoi(argv[1]);
		put_num(num);
	}
	write(1, "\n", 1);
}