	#include <unistd.h>
	#include <stdlib.h>

	int is_zero(char *str)
	{
		int i = 0;
		while (str[i])
		{
			if (str[i] != '0')
				return (0);
			i++;
		}
		return (1);
	}

	void ft_putstr(char *str)
	{
		int i = 0;
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
	}

	int ft_strlen(char *str)
	{
		int i = 0;
		while (str[i])
			i++;
		return (i);
	}

	char *infin_mult(char *s1, char *s2)
	{
		int len1 = ft_strlen(s1);
		int len2 = ft_strlen(s2);

		char *temp = malloc(len1 + len2 + 1);
		if (!temp)
			return (NULL);
		
		for (int i = 0; i < len1 + len2; i++)
			temp[i] = '0';
		temp[len1 + len2] = '\0';

		for (int i = len1 - 1; i >= 0; i--)
		{
			int carry = 0;
			for (int j = len2 - 1; j >= 0; j--)
			{
				int mult = (s1[i] - '0') * (s2[j] - '0') + carry + (temp[i + j + 1] - '0');
				temp[i + j + 1] = (mult % 10) + '0';
				carry = mult / 10;
			}
			temp[i] += carry;
		}

		int start = 0;
		while (temp[start] == '0' && start < len1 + len2 - 1)
			start++;
		
		int resultlen = len1 + len2 - start;
		char *final = malloc(resultlen + 1);
		if (!final)
		{
			free(temp);
			return (0);
		}

		for (int i = 0; i < resultlen; i++)
			final[i] = temp[start + i];
		final[resultlen] = '\0';

		free(temp);
		return (final);
	}

	int main(int argc, char **argv)
	{
		if (argc != 3)
		{
			write(1, "\n", 1);
			return (0);
		}

		char *s1 = argv[1];
		char *s2 = argv[2];

		int neg1 = (argv[1][0] == '-');
		int neg2 = (argv[2][0] == '-');

		int is_negative = (neg1 + neg2 == 1);

		if (neg1)
			s1++;
		if (neg2)
			s2++;

		if (is_zero(s1) || is_zero(s2))
		{
			write(1, "0\n", 2);
			return (0);
		}

		char *final = infin_mult(s1, s2);
		if (is_negative)
			write(1, "-", 1);
		ft_putstr(final);
		write(1, "\n", 1);
		free(final);
		return (0);
	}