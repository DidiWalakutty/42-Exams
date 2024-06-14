char    *ft_strrev(char *str)
{
	int i = 0;
	int len = 0;
	char temp;

	while (str[len])
		len++;
	i = -1;
	while (++i < len--)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
	}
	return (str);
}