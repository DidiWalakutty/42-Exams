#include <unistd.h>
#include <stdlib.h>

// Helper: strlen
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

// Helper: putstr
void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int compare_abs(char *a, char *b)
{
	int len1 = ft_strlen(a);
	int len2 = ft_strlen(b);

	if (len1 > len2) return (1);
	if (len1 < len2) return (-1);

	for (int i = 0; i < len1; i++)
	{
		if (a[i] > b[i]) return (1);
		if (a[i] < b[i]) return (-1);
	}
	return (0);
}

char *add_strings(char *a, char *b)
{
	int len1 = ft_strlen(a);
	int len2 = ft_strlen(b);
	int max_len = 0;

	if (len1 > len2)
		max_len = len1;
	else
		max_len = len2;

	char *res = malloc(max_len + 2); // for carry + \0
	if (!res)
		return (NULL);
	
	for (int i = 0; i < max_len + 1; i++)
		res[i] = '0';
	res[max_len + 1] = '\0';

	int i = len1 - 1;
	int j = len2 - 1;
	int k = max_len;

	while (k >= 0)
	{
		int digit_a (i >= 0) ? a[i] - '0' : 0;
		int digit_b = (j >= 0) ? b[j] - '0' : 0;

        int sum = digit_a + digit_b + carry;
        res[k] = (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
        k--;
	}

	// If first char is '0', shift string left to remove leading zero
    if (res[0] == '0')
    {
        for (int idx = 0; idx <= max_len; idx++)
            res[idx] = res[idx + 1];
    }

    return res;
}

// Assumes a >= b in absolute value
char *sub_strings(char *a, char *b)
{
    int len1 = ft_strlen(a);
    int len2 = ft_strlen(b);

    char *res = malloc(len1 + 1);
    if (!res)
        return NULL;

    for (int i = 0; i < len1; i++)
        res[i] = '0';
    res[len1] = '\0';

    int i = len1 - 1;
    int j = len2 - 1;
    int k = len1 - 1;
    int borrow = 0;

    while (k >= 0)
    {
        int digit_a = a[i] - '0';
        int digit_b = (j >= 0) ? b[j] - '0' : 0;

        int diff = digit_a - digit_b - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        res[k] = diff + '0';

        i--;
        j--;
        k--;
    }

    // Remove leading zeros by finding first non-zero
    int start = 0;
    while (res[start] == '0' && start < len1 - 1)
        start++;

    // Shift string left if needed
    if (start > 0)
    {
        for (int idx = 0; idx < len1 - start; idx++)
            res[idx] = res[start + idx];
        res[len1 - start] = '\0';
    }

    return res;
}


void	infin_add(char *a, char *b)
{
	int neg1 = (a[0] == '-');
	int neg2 = (b[0] == '-');

	if (neg1)
		a++;
	if (neg2)
		b++;

	char *res = NULL;

	if (neg1 == neg2)
	{
		res = add_strings(a, b);
		if (neg1)
			write(1, "-", 1);
		ft_putstr(res);
		free(rest);
		return (0);
	}
	else
	{
		int cmp = compare_abs(a, b);
		if (cmp == 0)
		{
			write(1, "0", 1);
			return ;
		}
		if (cmp > 0)
		{
			res = sub_strings(a, b);
			if (neg1)
				write(1, "-", 1);
		}
		else
		{
			res = sub_string(b, a);
			if (neg2)
				write(1, "-", 1);
		}
	}
	if (res)
	{
		ft_putstr(res);
		write(1, "\n", 1);
		free(res);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}

	infin_add(argv[1], argv[2]);
	return (0);
}