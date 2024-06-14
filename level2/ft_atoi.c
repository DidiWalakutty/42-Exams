int	ft_atoi(const char *str)
{
	int multx = 1;
	int result = 0;
	int i = 0;
	
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-')
	{
		multx = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * multx);
}

#include <stdio.h>

int	main()
{
	char *str = "963852";

	printf("%i", ft_atoi(str));
}