#include <stdlib.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	int i = 0;
	int j = 0;

	if (!s || !accept)
		return (0);
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break;
			j++;
		}
		if (accept[j] == '\0')
			break;
		i++;
	}
	return (i);
}