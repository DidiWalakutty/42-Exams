int	ft_atoi(const char *str)
{
	int multx = 1;
	int num = 0;
	int i = 0;

	while (str[i] == ' ' || str[i] == '\t')
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
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * multx);
}