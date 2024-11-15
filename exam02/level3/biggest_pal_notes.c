#include "biggest_pal.h"
#include <stdio.h>

int	is_palindrome(char *str, int start, int end)
{
	while (start < end)
	{
		if (str[start] != str[end])
			return (0);	// returns 0 if it's not the same.
		start++;
		end--;
	}
	// if letters are palin, we return 1.
	// if start == end, we return true, since it's just checking 1 char.
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
		int max_len = 0;	// current len of longest found palindrome.
		int max_start = 0;	// curent starting index of found palindrome.

		while (str[len])
			len++;
		while (i < len)
		{
			j = i;
			// loop j to fully iterate through each starting index of the string.
			// it'll go into this loop even when the string only has 1 letter.
			while (j < len)
			{
				// check if i up to j is a palindrome.
				if (is_palindrome(str, i, j))
				{
					// if it is a palindrome, we set a new pal_len.
					pal_len = j - i + 1;
					if (pal_len > max_len)	// if pal_len > max_len we have a new/longer palindrome.
					{
						max_len = pal_len;
						max_start = i;		// max_start is the starting index of the current palindrome.
					}
					// if len is the same, but i > max_start, we update max_start to current index.
					// this way we make sure we get the last found palindrome!
					else if (pal_len == max_len && i > max_start)
						max_start = i;
				}
				j++;
			}
			i++;
		}
		// max_len will be 1 even if no palindrome was found
		// and print the last letter even if no palindrome was found
		if (max_len > 0)
			write_str(str, max_start, max_start + max_len - 1);
	}
	write(1, "\n", 1);
}