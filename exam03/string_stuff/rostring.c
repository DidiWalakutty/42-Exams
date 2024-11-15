#include <unistd.h>

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		int start = 0;
		int end = 0;
		int i = 0;
		while (str[i] && is_space(str[i]))
			i++;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		end = i;
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
		{
			while (str[i])
			{
				if (is_space(str[i]))
				{
					while (is_space(str[i]))
						i++;
					if (str[i])
						write(1, " ", 1);
				}
				else
				{
					write(1, &str[i], 1);
					i++;
				}
			}
			write(1, " ", 1);
		}
		while (start <= end)
		{
			write(1, &str[start], 1);
			start++;
		}
	}
	write(1, "\n", 1);
}