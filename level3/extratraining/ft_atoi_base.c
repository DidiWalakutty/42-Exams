char	to_lower(char c)
{
	if (c >= 'A' && c <= 'F')
		return (c += 32);
	return (c);
}

int	get_digit(char c, int base)
{
	int max_digit;

	if (base <= 10)
		max_digit = base + '0';
	else
		max_digit = 'f';
	if ((c >= '0' && c <= '9') && (c <= max_digit))
		return (c - '0');
	else if ((c >= 'a' && c <= 'f') && c <= max_digit)
		return (c + 10 - 'a');
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int i = 0;
	int num = 0;
	int result = 0;
	int multx = 1;

	if (str[i] == '-')
	{
		multx = -1;
		i++;
	}
	while ((num = get_digit(to_lower(str[i]), str_base)) >= 0)
	{
		result = result * str_base;
		num = num * multx;
		result = result + num;
	}
	return (result);
}