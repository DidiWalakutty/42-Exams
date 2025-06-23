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

char	*infin_mult(char *s1, char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);

	char *temp = malloc((len1 + len2 + 1) * sizeof(char));
	if (!temp)	
		return (NULL);
	
	// Fill temp with 0's
	for (int i = 0; i < len1 + len2; i++)
		temp[i] = '0';
	temp[len1 + len2] = '\0';

	// Multiply digit by digit from right to left.
	for (int i = len1 - 1; i >= 0; i--)	 // Outer loop
	{
		int carry = 0;	// Start each i-iteration with carry = 0.
		for (int j = len2 - 1; j >= 0; j--)	 // Inner loop
		{
			// 1. Multiply the current digits from str1 and str2 + convert char digit to actual number.
			// 2. Carry: add the carry from previous digit multiplication -> 9x9 = 81, carry over 8
			// 3. Temp: add what's already in temp at that position.
			int mul = (s1[i] - '0') * (s2[j] - '0') + carry + (temp[i + j + 1] - '0');

			// mul % 10: is last number of mul (81, mul % 10 is 1). Add '0' to make a char 
			temp[i + j + 1] = (mul % 10) + '0';

			// mul / 10: first number (8) and carry it to the next multiplication
			carry = mul / 10;
		}
		// Add any leftover carry to the next left position in temp
		temp[i] += carry;
	}

	// Skip leading zeros in temp to find actual start of the number
	int start = 0;
	while (temp[start] == '0' && start < len1 + len2 - 1)
		start++;

	// Alloc new string
	int result_len = len1 + len2 - start;
	char *final = malloc(result_len + 1);
	if (!final)
	{
		free(temp);
		return (NULL);
	}

	// Copy the trimmed result in the final returning string
	for (int i = 0; i < result_len; i++)
		final[i] = temp[start + i];
	final[result_len] = '\0';

	free(temp);
	return final;
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return 0;
	}
	char *s1 = argv[1];
	char *s2 = argv[2];

	int neg1 = (argv[1][0] == '-');	// Check if inputs are negative (start with '-')
	int neg2 = (argv[2][0] == '-');

	int is_negative = (neg1 + neg2 == 1);	// if sum == 1, we have a negative outcome and write -

	if (neg1)	// Strip the '-' sign from input if present
		s1++;
	if (neg2)
		s2++;

	if (is_zero(s1) || is_zero(s2))
	{
		write(1, "0\n", 2);
		return (0);
	}

	char *result = infin_mult(s1, s2);
	if (is_negative)
		write(1, "-", 1);
	ft_putstr(result);
	write(1, "\n", 1);
	free(result);
	return (0);
}