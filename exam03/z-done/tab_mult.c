#include <unistd.h>

int	ft_atoi(char *str)
{
	int i = 0;
	int num = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

void	put_num(int num)
{
	char str[] = "0123456789";
	if (num > 9)
		put_num(num / 10);
	write(1, &str[num % 10], 1);	
}

int	main(int argc, char **argv)
{
	int i = 1;
	int num = ft_atoi(argv[1]);
	if (num < 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (i <= 9)
	{
		put_num(i);
		write(1, " x ", 3);
		put_num(num);
		write(1, " = ", 3);
		put_num(i * num);
		write(1, "\n", 1);
		i++;
	}
}