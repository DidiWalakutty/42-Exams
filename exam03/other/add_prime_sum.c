#include <unistd.h>

int is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int i = 0;
	int num = 0;
	while (str[i] && is_whitespace(str[i]))
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

int	is_prime(int num)
{
	int i = 2;

	if (num == 1)
		return (0);
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void	put_sum(int num)
{
	char str[] = "0123456789";
	if (num > 9)
		put_sum(num / 10);
	write(1, &str[num % 10], 1);
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int	num = 0;
		int sum = 0;
	
		num = ft_atoi(argv[1]);
		if (num == -1)
		{
			write(1, "0\n", 2);
			return (0);
		}
		while (num >= 0)
		{
			if (is_prime(num) == 1)
				sum += num;
			num--;
		}
		put_sum(sum);
	}
	else
		write(1, "0", 1);
	write(1, "\n", 1);
}