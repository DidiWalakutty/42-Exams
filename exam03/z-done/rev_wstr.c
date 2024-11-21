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
		int i = 0;
		char *str = argv[1];
		int start = 0;
		int end = 0;
		int flag = 0;
		while (str[i])
			i++;
		while (i >= 0)
		{
			while (str[i] == '\0' || is_space(str[i]))
				i--;
			end = i;
			while (str[i] && !is_space(str[i]))
				i--;
			start = i + 1;
			flag = start;
			while (start <= end)
			{
				write(1, &str[start], 1);
				start ++;
			}
			if (flag != 0)
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}