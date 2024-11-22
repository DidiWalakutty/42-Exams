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
		int i = 0;
		while (str[i] && is_space(str[i]))
			i++;
		while (str[i])
		{
			if (is_space(str[i]))
			{
				while (is_space(str[i]))
					i++;
				write(1, "   ", 3);
			}
			while (str[i] && !is_space(str[i]))
			{
				write(1, &str[i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
}