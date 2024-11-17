#include <unistd.h>

void	write_first_word(char *str, int begin, int end)
{
	while (begin < end)
	{
		write(1, &str[begin], 1);
		begin++;
	}
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc >= 2)
	{
		char *str;
		int begin_word = 0;
		int end_word = 0;
		int i = 0;

		str = argv[1];
		while (is_space(str[i]))
			i++;
		begin_word = i;
		while (str[i] && !is_space(str[i]))
			i++;
		end_word = i;
		while (is_space(str[i]))
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
		write_first_word(str, begin_word, end_word);
	}
	write(1, "\n", 1);
}