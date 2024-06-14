#include <unistd.h>

int	ft_atoi(char *str)
{
	int i = 0;
	int num = 0;
	int multx = 1;
	
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		multx = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * multx);
}

int	is_prime(int num)
{
	int i = 2;
	if (num <= 1)
		return (0);
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void put_sum(int num)
{
	char *str = "0123456789";
	if (num > 9)
		put_sum(num / 10);
	write(1, &str[num % 10], 1);
}

int	main(int argc, char **argv)
{
	int num = 0;
	int sum = 0;

	if (argc == 2)
	{
		num = ft_atoi(argv[1]);
		while (num >= 0)
		{
			if (is_prime(num) == 1)
				sum += num;
			num--;
		}
		put_sum(sum);
	}
	if (argc != 2)
		write(1, "0", 1);
	write(1, "\n", 1);
}