#include "biggest_pal_try.h"

int	is_palindrome(char *str, int start, int end)
{
	while (start < end)
	{
		if (str[start] != str[end])
			return (0);
		start++;
		end--;
	}
	return (1);
}

void	write_str(char *str, int start, int end)
{
	while (start <= end)
	{
		write(1, &str[start], 1);
		start++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		int i = 0;
		int j = 0;
		int len = 0;
		int pal_len = 0;
		int max_len = 0;
		int max_start = 0;

		if (!str)
			return (0);
		while (str[len])
			len++;
		while (i < len)
		{
			j = i;
			while (j < len)
			{
				if (is_palindrome(str, i, j))
				{
					pal_len = j - i + 1;
					if (pal_len > max_len)
					{
						max_len = pal_len;
						max_start = i;
					}
					else if (pal_len == max_len && i > max_start)
						max_start = i;
				}
				j++;
			}
			i++;
		}
		if (max_len > 0)
			write_str(str, max_start, max_start + max_len - 1);
	}
	write(1, "\n", 1);
}