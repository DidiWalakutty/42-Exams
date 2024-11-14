#include <unistd.h>

int	not_seen(char *str, char c, int len)
{
	int i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (not_seen(argv[1], argv[1][i], i))
				write(1, &argv[1][i], 1);
			i++;
		}
		while (argv[2][j])
		{
			if (not_seen(argv[1], argv[2][j], i) && not_seen(argv[2], argv[2][j], j))
				write(1, &argv[2][j], 1);
			j++;
		}
	}
	write(1, "\n", 1);
}